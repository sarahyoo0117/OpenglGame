#version 330 core

in vec3 vertexColor;
out vec4 FragColor;

//uniform vec4 ourColor; //when using vertices

void main()
{
	//FragColor = ourColor;
	FragColor = vec4(vertexColor, 1.0);
}