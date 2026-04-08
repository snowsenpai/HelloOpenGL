#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;
out vec3 vertexColor;

void main()
{
   vec4 pos = vec4(aPos, 1.0);
   pos.y = -pos.y;
   gl_Position = vec4(aPos.x, pos.y, aPos.z, 1.0);
   vertexColor = aColor;
}