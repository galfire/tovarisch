#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 texCoord;
  
out vec2 TexCoord;

void main()
{
    vec4 pos4 = vec4(pos, 1.0f);
    gl_Position = pos4;

    TexCoord = texCoord;
}
