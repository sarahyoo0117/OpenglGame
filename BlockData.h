#ifndef BLOCK_DATA_H
#define BLOCK_DATA_H

#include <vector>
#include <map>
#include <array>
#include "Texture.h"

enum class BlockType 
{
	DIRT,
	EMPTY
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

inline std::map<BlockFaces, FaceVertices> BlockFaceVertices = {
	{BlockFaces::FRONT, {
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5),		glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	}},
	{BlockFaces::BACK, {
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	}},
	{BlockFaces::LEFT, {
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	}},
	{BlockFaces::RIGHT, {
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	}},
	{BlockFaces::TOP, {
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, 0.5f, 0.5f),		glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	}},
	{BlockFaces::BOTTOM, {
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
		Vertex{glm::vec3(0.5f, -0.5f,  0.5f),	glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
		Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	}}
};

inline std::vector<Vertex> convertVertexToVector(BlockFaces face)
{
	const auto& faceVertices = BlockFaceVertices[face];
	return std::vector<Vertex>(faceVertices.begin(), faceVertices.end());
}

#endif