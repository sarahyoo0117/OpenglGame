#include "Texture.h"

Texture::Texture(const char* imagePath, GLuint slot, GLenum texType, GLenum internalFormat, GLenum imageFormat, GLenum pixelType)
{
	this->type = texType;
	this->unit = slot;

	glGenTextures(1, &ID);
	glActiveTexture(slot);
	glBindTexture(texType, ID);

	glTexParameteri(texType, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(texType, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(texType, GL_TEXTURE_WRAP_T, GL_REPEAT);

	int imgWidth, imgHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load(imagePath, &imgWidth, &imgHeight, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, imgWidth, imgHeight, 0, imageFormat, pixelType, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	//deletes the image data since it is in Opengl texture object now
	stbi_image_free(data);
	glBindTexture(texType, 0);
}

void Texture::setTextureUnit(Shader& shader, const char* uniformName)
{
	shader.Activate();
	glUniform1i(glGetUniformLocation(shader.ID, uniformName), this->unit);
}

void Texture::Activate()
{
	glActiveTexture(this->unit);
}

void Texture::Bind()
{
	glActiveTexture(GL_TEXTURE0 + this->unit);
	glBindTexture(this->type, this->ID);
}

void Texture::Unbind()
{
	glBindTexture(this->type, 0);
}

void Texture::Delete()
{
	glDeleteTextures(1, &ID);
}