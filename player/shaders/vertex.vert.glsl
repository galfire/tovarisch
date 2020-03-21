#version 300 es

layout (location = 0) in vec3 aPos;
  
out vec4 vertexColor; // specify a color output to the fragment shader

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

void main()
{
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    gl_Position = mvp * vec4(aPos, 1.0);

    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}