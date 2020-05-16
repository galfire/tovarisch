#version 330 core
  
layout(location = 0) out vec4 diffuseColour;

uniform vec3 colour;

void main()
{
    diffuseColour = vec4(colour, 1);
}
