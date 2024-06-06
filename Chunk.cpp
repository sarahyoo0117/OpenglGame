#include "Chunk.h"

Chunk::Chunk(Shader& shader) : ShaderProgram(shader) {
	Vertex vertices[] =
	{  //positions							//texture coords
	   // Back
	  Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	  // Front
	 Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	 Vertex{glm::vec3(0.5f, -0.5f, 0.5),	glm::vec2(1.0f, 0.0f)},
	 Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	 Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	 Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 1.0f)},
	 Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	 // Left
	Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	// Right
	Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	// Bottom
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, -0.5f,  0.5f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 1.0f)},
	// Top
	Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	};

	Texture textures[] =
	{
		Texture("Dirt_Block.png", "block", 0, GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	std::vector<Vertex> vertexVectors(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<Texture> textureVectors(textures, textures + sizeof(textures) / sizeof(Texture));
	this->Block = new Mesh(vertexVectors, textureVectors);
}

void Chunk::GenerateChunk(int width, int length, int height) {
	Shader shaderProgram("default.vert", "default.frag");

	for (int x = 0; x < width; x++) 
	{
		for (int z = 0; z < length; z++) 
		{
			for (int y = 0; y < height; y++) 
			{
				glm::mat4 model = glm::mat4(1.0f);
				glm::vec3 position = glm::vec3(1.0f * x, 1.0f * y, 1.0f * z);
				Block->Draw(this->ShaderProgram, model, position);
			}
		}
	}
}
