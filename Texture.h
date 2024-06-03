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
	const char* name;
	GLenum type;
	GLuint unit;

	Texture(const char* imagePath, const char* texName, GLuint slot, GLenum texType, GLenum internalFormat, GLenum imageFormat, GLenum piexlType);
	void setTextureUnit(Shader& shader, const char* uniformName, GLuint unit);
	void Activate();
	void Bind();
	void Unbind();
	void Delete();
};

#endif