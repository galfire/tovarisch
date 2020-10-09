#version 330 core
  
layout(location = 0) out vec3 gPosition;
layout(location = 1) out vec3 gNormal;
layout(location = 2) out vec4 gAlbedo;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D albedoTexture;
uniform sampler2D normalTexture;

void main()
{
    gPosition = Position;
    gNormal = normalize(Normal);
    gAlbedo.rgb = texture(albedoTexture, TexCoord).rgb;
    gAlbedo.a = 1.0f + texture(normalTexture, TexCoord).a;
}
