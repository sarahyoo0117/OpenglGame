#include "Voxel.h"

Voxel::Voxel(glm::vec3 position, BlockType blockType)
{
	this->position = position;
	this->type = blockType;
}

void Voxel::Draw(Shader& shader, std::vector<Vertex>& vertices, std::vector<Texture>& textures)
{
	this->VAO.Bind();
	
	VBO VBO(vertices);

	this->VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	this->VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	VBO.Unbind();

	shader.Activate();


	int blockNum = 0;
	for (int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string name = textures[i].name;
		if (name == "block")
		{
			num = std::to_string(blockNum++);
		}
		textures[i].setTextureUnit(shader, (name + num).c_str(), i);
		textures[i].Bind();
	}

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, position);
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(model));
	glUniform1f(glGetUniformLocation(shader.ID, "scale"), 1.0);

	glDrawArrays(GL_TRIANGLES, 0, vertices.size());
}

