#version 300 es

precision mediump float;
  
layout(location = 0) out vec4 diffuseColour;

uniform vec3 colour;

void main()
{
    diffuseColour = vec4(colour, 1);
}
