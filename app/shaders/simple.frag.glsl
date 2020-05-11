#version 330 core
  
layout(location = 0) out vec4 diffuseColor;

in vec4 fragColour;
in vec2 oTexCoord;

uniform sampler2D textureSampler;

void main()
{
    diffuseColor = texture(textureSampler, oTexCoord);
}
