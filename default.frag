#version 330 core

out vec4 FragColor;

in vec2 TexCoord;

uniform sampler2D block0;

void main()
{
   FragColor = texture(block0, TexCoord);
}