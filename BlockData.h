#ifndef BLOCK_DATA_H
#define BLOCK_DATA_H

#include <vector>
#include <map>
#include <array>

enum class BlockType 
{
	EMPTY,
	DIRT,
	GRASS
};

enum class BlockFaces 
{
	FRONT,
	BACK,
	LEFT,
	RIGHT,
	TOP,
	BOTTOM
};

using FaceVertices = std::array<Vertex, 6>;
using FacePosCoords = std::array<glm::vec3, 6>;

inline std::map<BlockFaces, FacePosCoords> FacePositionCoordinates = {
	{BlockFaces::FRONT, {
		glm::vec3(-0.5f, -0.5f, 0.5f),	
		glm::vec3(0.5f, -0.5f, 0.5),	
		glm::vec3(0.5f, 0.5f, 0.5f),	
		glm::vec3(0.5f, 0.5f, 0.5f),	
		glm::vec3(-0.5f, 0.5f, 0.5f),	
		glm::vec3(-0.5f, -0.5f, 0.5f),
	}},
	{BlockFaces::BACK, {
		glm::vec3(-0.5f, -0.5f, -0.5f),	
		glm::vec3(0.5f, 0.5f, -0.5f),	
		glm::vec3(0.5f, -0.5f, -0.5f),	
		glm::vec3(0.5f, 0.5f, -0.5f),	
		glm::vec3(-0.5f, -0.5f, -0.5f),	
		glm::vec3(-0.5f, 0.5f, -0.5f),	
	}},
	{BlockFaces::LEFT, {
		glm::vec3(-0.5f, 0.5f, 0.5f),	
		glm::vec3(-0.5f, 0.5f, -0.5f),	
		glm::vec3(-0.5f, -0.5f, -0.5f),	
		glm::vec3(-0.5f, -0.5f, -0.5f),	
		glm::vec3(-0.5f, -0.5f, 0.5f),	
		glm::vec3(-0.5f, 0.5f, 0.5f),	
	}},
	{BlockFaces::RIGHT, {
		glm::vec3(0.5f, 0.5f, 0.5f),		
		glm::vec3(0.5f, -0.5f, -0.5f),	
		glm::vec3(0.5f, 0.5f, -0.5f),	
		glm::vec3(0.5f, -0.5f, -0.5f),	
		glm::vec3(0.5f, 0.5f, 0.5f),		
		glm::vec3(0.5f, -0.5f, 0.5f),	
	}},
	{BlockFaces::TOP, {
		glm::vec3(-0.5f, 0.5f, -0.5f),	
		glm::vec3(0.5f, 0.5f, 0.5f),		
		glm::vec3(0.5f, 0.5f, -0.5f),	
		glm::vec3(0.5f, 0.5f, 0.5f),		
		glm::vec3(-0.5f, 0.5f, -0.5f),	
		glm::vec3(-0.5f, 0.5f, 0.5f),	
	}},
	{BlockFaces::BOTTOM, {
		glm::vec3(-0.5f, -0.5f, -0.5f),	
		glm::vec3(0.5f, -0.5f, -0.5f),	
		glm::vec3(0.5f, -0.5f,  0.5f),	
		glm::vec3(0.5f, -0.5f, 0.5f),	
		glm::vec3(-0.5f, -0.5f, 0.5f),	
		glm::vec3(-0.5f, -0.5f, -0.5f),	
	}}
};


#endif