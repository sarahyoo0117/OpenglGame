#include "Voxel.h"

Voxel::Voxel(glm::vec3 position, BlockType blockType) : position(position), type(blockType) 
{
	this->blockFaceVertices = new std::map<BlockFaces, FaceVertices>{
		{ BlockFaces::FRONT, 
			transformedVertices(FacePositionCoordinates[BlockFaces::FRONT], 
				GetUVsFromTexCoords(TextureCoordinates[blockType])[BlockFaces::FRONT])
		},
		{ BlockFaces::BACK, 
			transformedVertices(FacePositionCoordinates[BlockFaces::BACK], 
				GetUVsFromTexCoords(TextureCoordinates[blockType])[BlockFaces::BACK])
		},
		{ BlockFaces::LEFT, 
			transformedVertices(FacePositionCoordinates[BlockFaces::LEFT],
				GetUVsFromTexCoords(TextureCoordinates[blockType])[BlockFaces::LEFT])
		},
		{ BlockFaces::RIGHT,
			transformedVertices(FacePositionCoordinates[BlockFaces::RIGHT], 
				GetUVsFromTexCoords(TextureCoordinates[blockType])[BlockFaces::RIGHT])
		},
		{ BlockFaces::TOP, 
			transformedVertices(FacePositionCoordinates[BlockFaces::TOP], 
				GetUVsFromTexCoords(TextureCoordinates[blockType])[BlockFaces::TOP])
		},
		{ BlockFaces::BOTTOM, 
			transformedVertices(FacePositionCoordinates[BlockFaces::BOTTOM],
				GetUVsFromTexCoords(TextureCoordinates[blockType])[BlockFaces::BOTTOM])
		}
	};
}

FaceVertices Voxel::transformedVertices (FacePosCoords posCoords, FaceTexCoords texCoords)
{
	FaceVertices transformedVertices;

	for (int i = 0; i < transformedVertices.size(); i ++)
	{
		Vertex transformedVertex;
		transformedVertex.Position = posCoords[i] + this->position;
		transformedVertex.TexCoords = texCoords[i];
		transformedVertices[i] = transformedVertex;
	}

	return transformedVertices;
}

FaceVertices Voxel::getFaceVertices(BlockFaces face)
{
	return (*this->blockFaceVertices)[face];
}