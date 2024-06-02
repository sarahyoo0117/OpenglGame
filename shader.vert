#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec2 TexCoord;

uniform float scale;
uniform mat4 cameraMatrix;

void main()
{
   gl_Position = cameraMatrix * vec4(aPos.x * scale, aPos.y * scale, aPos.z * scale, 1.0);
   TexCoord = aTexCoord;
}