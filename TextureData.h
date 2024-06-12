#ifndef TEXTURE_DATA_H
#define TEXTURE_DATA_H

#include <map>
#include "Texture.h"
#include "BlockData.h"

using FaceTexCoords = std::array<glm::vec2, 6>;

inline std::map<BlockType, std::map<BlockFaces, glm::vec2>> TextureCoordinates =
{
	{BlockType::DIRT, {
		{BlockFaces::FRONT,  glm::vec2(2.0f, 15.0f)},
		{BlockFaces::BACK,   glm::vec2(2.0f, 15.0f)},
		{BlockFaces::LEFT,	 glm::vec2(2.0f, 15.0f)},
		{BlockFaces::RIGHT,	 glm::vec2(2.0f, 15.0f)},
		{BlockFaces::TOP,	 glm::vec2(2.0f, 15.0f)},
		{BlockFaces::BOTTOM, glm::vec2(2.0f, 15.0f)},
	}},
	{BlockType::GRASS, {
		{BlockFaces::FRONT,	 glm::vec2(3.0f, 15.0f)},
		{BlockFaces::BACK,   glm::vec2(3.0f, 15.0f)},
		{BlockFaces::LEFT,   glm::vec2(3.0f, 15.0f)},
		{BlockFaces::RIGHT,  glm::vec2(3.0f, 15.0f)},
		{BlockFaces::TOP,    glm::vec2(8.0f, 13.0f)},
		{BlockFaces::BOTTOM, glm::vec2(2.0f, 15.0f)},
	}}
};

inline std::map<BlockFaces, FaceTexCoords> GetUVsFromTexCoords(std::map<BlockFaces, glm::vec2> texCoords)
{
	std::map<BlockFaces, FaceTexCoords> updatedTexCoords;

	for (const auto& coord : texCoords)
	{
		switch (coord.first)
		{
		case BlockFaces::FRONT:
			updatedTexCoords[coord.first] = 
			{
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
				glm::vec2(coord.second.x / 16, coord.second.y / 16)
			};
			break;
		case BlockFaces::BACK:
			updatedTexCoords[coord.first] = 
			{
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16)
			};
			break;
		case BlockFaces::LEFT:
			updatedTexCoords[coord.first] =
			{
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
			};
			break;
		case BlockFaces::RIGHT:
			updatedTexCoords[coord.first] =
			{
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1)/ 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
			};
			break;
		case BlockFaces::TOP:
			updatedTexCoords[coord.first] =
			{
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
			};
			break;
		case BlockFaces::BOTTOM:
			updatedTexCoords[coord.first] =
			{
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1) / 16, (coord.second.y + 1) / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2((coord.second.x + 1) / 16, coord.second.y / 16),
				glm::vec2(coord.second.x / 16, coord.second.y / 16),
				glm::vec2(coord.second.x / 16, (coord.second.y + 1) / 16),
			};
			break;
		}
	}

	return updatedTexCoords;
}


#endif