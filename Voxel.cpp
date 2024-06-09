#include "Voxel.h"

Voxel::Voxel(glm::vec3 position, BlockType blockType) : position(position), type(blockType) 
{
	this->blockFaceVertices = new std::map<BlockFaces, FaceVertices>{
		{ BlockFaces::FRONT, transformedVertices(RawFaceVertices[BlockFaces::FRONT]) },
		{ BlockFaces::BACK, transformedVertices(RawFaceVertices[BlockFaces::BACK]) },
		{ BlockFaces::LEFT, transformedVertices(RawFaceVertices[BlockFaces::LEFT]) },
		{ BlockFaces::RIGHT, transformedVertices(RawFaceVertices[BlockFaces::RIGHT]) },
		{ BlockFaces::TOP, transformedVertices(RawFaceVertices[BlockFaces::TOP]) },
		{ BlockFaces::BOTTOM, transformedVertices(RawFaceVertices[BlockFaces::BOTTOM]) }
	};
}

FaceVertices Voxel::transformedVertices (FaceVertices vertices)
{
	FaceVertices transformedVertices;

	int i = 0;
	for (const auto& vertex : vertices)
	{
		Vertex transformedVertex;
		transformedVertex.Position = vertex.Position * this->position;
		transformedVertex.TexCoords = vertex.TexCoords;
		transformedVertices[i] = transformedVertex;
		i++;
	}

	return transformedVertices;
}

FaceVertices Voxel::getFaceVertices(BlockFaces face)
{
	return (*this->blockFaceVertices)[face];
}