#include "Texture.h"

Texture::Texture(const char* imagePath, const char* texName, GLuint slot, GLenum texType, GLenum internalFormat, GLenum imageFormat, GLenum pixelType)
{
	this->name = texName;
	this->type = texType;
	this->unit = slot;

	glGenTextures(1, &ID);
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	int imgWidth, imgHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath, &imgWidth, &imgHeight, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(texType, 0, internalFormat, imgWidth, imgHeight, 0, imageFormat, pixelType, data);
		glGenerateMipmap(texType);
		glEnable(texType);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//deletes the image data since it is in Opengl texture object now
	stbi_image_free(data); 
	glBindTexture(texType, 0);
}

void Texture::setTextureUnit(Shader& shader, const char* uniformName, GLuint unit)
{
	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, uniformName), unit);
}

void Texture::Activate()
{
	glActiveTexture(unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(type, ID);
}

void Texture::Unbind()
{
	glBindTexture(type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}