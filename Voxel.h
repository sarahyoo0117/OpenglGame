#ifndef VOXEL_CLASS_H
#define VOXEL_CLASS_H

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <unordered_map>
#include <string>
#include <vector>
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "BlockData.h"

class Voxel
{
private:
	VAO VAO;
	BlockType type;
	glm::vec3 position;
public:
	Voxel(glm::vec3 position, BlockType blockType = BlockType::EMPTY);
	void Draw(Shader& shader, std::vector<Vertex>& vertices, std::vector<Texture>& textures);
};

#endif