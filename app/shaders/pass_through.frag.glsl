#version 330 core
  
layout(location = 0) out vec4 Colour;

in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
    vec3 colour = texture(Texture, TexCoord).rgb;
    Colour.rgb = colour;
    Colour.a = 1.0;
}
