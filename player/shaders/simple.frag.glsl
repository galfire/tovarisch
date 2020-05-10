#version 300 es

precision mediump float;

out vec4 FragColor;
  
in vec4 fragColour;

void main()
{
    FragColor = fragColour;
}
