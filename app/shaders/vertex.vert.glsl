#version 330 core

layout (location = 0) in vec3 pos;
  
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec4 vertexColor;

void main()
{
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;

    gl_Position = mvp * vec4(pos, 1.0);

    vertexColor = vec4(0.5, 0.0, 0.0, 1.0);
}
