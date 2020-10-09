#version 330 core
  
layout(location = 0) out vec4 Colour;

in vec3 Position;
in vec3 Normal;
in vec2 TexCoord;

uniform sampler2D albedoTexture;

void main()
{
    Colour.rgb = texture(albedoTexture, TexCoord).rgb;
    Colour.a = 1.0f;
}
