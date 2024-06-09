#ifndef VOXEL_CLASS_H
#define VOXEL_CLASS_H

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <map>
#include <string>
#include <vector>
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "BlockData.h"


class Voxel
{
private:
	std::map<BlockFaces, FaceVertices>* blockFaceVertices;

	FaceVertices transformedVertices(FaceVertices vertices);

public:
	glm::vec3 position;
	BlockType type;

	Voxel(glm::vec3 position, BlockType blockType = BlockType::EMPTY);
	FaceVertices getFaceVertices(BlockFaces face);
};

#endif