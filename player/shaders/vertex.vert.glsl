#version 300 es

layout (location = 0) in vec3 pos;
layout (location = 3) in vec2 texCoord;
  
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

out vec2 oTexCoord;

void main()
{
    vec4 pos4 = vec4(pos, 1.0f);

    mat4 mvp = projectionMatrix * viewMatrix * modelMatrix;
    vec4 transformedPos = mvp * pos4;
    gl_Position = transformedPos;

    oTexCoord = texCoord;
}
