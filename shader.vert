#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; //when using verticesWithColors

out vec3 vertexColor;

uniform float scale;

void main()
{
   gl_Position = vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
   vertexColor = aColor;
}