#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 normal;
layout (location = 3) in vec2 texCoord;
  
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec3 Position;
out vec3 Normal;
out vec2 TexCoord;

void main()
{
    vec4 pos4 = vec4(pos, 1.0f);

    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    vec4 transformedPos = mvp * pos4;
    gl_Position = transformedPos;

    Position = transformedPos.xyz;
    Normal = normal;
    TexCoord = texCoord;
}
