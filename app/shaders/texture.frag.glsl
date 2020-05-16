#version 330 core
  
layout(location = 0) out vec4 diffuseColour;

in vec2 oTexCoord;

uniform sampler2D texture;

void main()
{
    diffuseColour = texture(texture, oTexCoord);
}
