#version 300 es

precision mediump float;
  
layout(location = 0) out vec4 Colour;

in vec2 TexCoord;

uniform sampler2D Texture;

void main()
{
    Colour = texture(Texture, TexCoord);
}
