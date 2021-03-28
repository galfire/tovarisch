#version 300 es

layout (location = 0) in vec3 position;
 
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 TexCoord;

void main()
{
    TexCoord = position;
    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    gl_Position = mvp * vec4(position, 1.0);
}
