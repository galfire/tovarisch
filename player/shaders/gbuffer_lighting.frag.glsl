#version 300 es

precision mediump float;
  
layout(location = 0) out vec4 gColour;

in vec2 TexCoord;

uniform sampler2D gPosition;
uniform sampler2D gNormal;
uniform sampler2D gAlbedo;

void main()
{
    vec3 Position = texture(gPosition, TexCoord).rgb;
    vec3 Normal = texture(gNormal, TexCoord).rgb;
    vec3 Albedo = texture(gAlbedo, TexCoord).rgb;

    gColour.rgb = (Albedo * 0.5) + (Position * 0.1) + (Normal * 0.5);
    gColour.a = 1.0;
}
