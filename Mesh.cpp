#include "Mesh.h"

Mesh::Mesh(std::vector<Vertex>& vertices, std::vector<Texture>& textures)
{
	this->vertices = vertices;
	this->textures = textures;
	this->VAO.Bind();

	VBO VBO(vertices);
	
	VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	VAO.Unbind();
	VBO.Unbind();
}

void Mesh::Draw(Shader& shader, glm::mat4 model, glm::vec3 position)
{
	shader.Activate();
	VAO.Bind();
	
	int blockNum = 0;
	for (int i = 0; i < this->textures.size(); i++)
	{
		std::string num;
		std::string name = this->textures[i].name;
		if (name == "block")
		{
			num = std::to_string(blockNum++);
		}
		textures[i].setTextureUnit(shader, (name + num).c_str(), i);
		textures[i].Bind();
	}

	model = glm::translate(model, position);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1f(glGetUniformLocation(shader.ID, "scale"), 1.0);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size()); //TODO:36 --> vertices.size()
}