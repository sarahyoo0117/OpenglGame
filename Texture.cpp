#include "Texture.h"

Texture::Texture(const char* imagePath, GLenum texType, GLenum texSlot, GLenum internalFormat, GLenum format, GLenum pixelType)
{
	type = texType;
	slot = texSlot;

	glGenTextures(1, &ID);
	glActiveTexture(texSlot);
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
		glTexImage2D(texType, 0, internalFormat, imgWidth, imgHeight, 0, format, pixelType, data);
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

void Texture::LinkToShader(Shader& shader, const char* uniformName, GLuint unit)
{
	shader.Activate();
	GLuint texUni = glGetUniformLocation(shader.ID, uniformName);
	glUniform1i(texUni, unit);
}

void Texture::Activate()
{
	glActiveTexture(slot);
}

void Texture::Bind()
{
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