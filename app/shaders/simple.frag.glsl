#version 330 core
  
layout(location = 0) out vec4 diffuseColor;

in vec4 fragColour;

void main()
{
    diffuseColor = fragColour;
}
