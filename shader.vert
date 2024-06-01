#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor; 
layout (location = 2) in vec2 aTexCoord;

out vec3 vertexColor;
out vec2 TexCoord;

uniform float scale;
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	//**we read the multiplication from right to left
   gl_Position = projection * view * model * vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
   vertexColor = aColor;
   TexCoord = aTexCoord;
}