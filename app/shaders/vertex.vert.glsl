#version 330 core

layout (location = 0) in vec3 pos;
  
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 colour;

out vec4 fragColour;

void main()
{
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    vec4 pos4 = vec4(pos, 1.0f);
    vec4 transformedPos = mvp * pos4;

    fragColour = vec4(colour, 1.0f);

    gl_Position = transformedPos;
}
