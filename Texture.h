#pragma once
#ifndef TEXTURE_CLASS_H
#define TEXTURE_CLASS_H

#include <glad/glad.h>
#include "Shader.h"
#include "stb/stb_image.h"

class Texture
{
public:
	GLuint ID;
	GLenum type;
	GLenum slot;

	Texture(const char* imagePath, GLenum texType, GLenum texSlot, GLenum internalFormat, GLenum format, GLenum piexlType);
	void LinkToShader(Shader& shader, const char* uniformName, GLuint unit);
	void Activate();
	void Bind();
	void Unbind();
	void Delete();
};

#endif