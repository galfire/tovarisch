#version 300 es

layout (location = 0) in vec3 aPos;
  
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
uniform vec3 colour;

out vec4 fragColour;

void main()
{
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    gl_Position = mvp * vec4(aPos, 1.0);

    fragColour = vec4(colour, 1.0f);
}
