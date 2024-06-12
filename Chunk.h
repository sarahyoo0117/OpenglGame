#pragma once
#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include <list>
#include "Texture.h"
#include "Voxel.h"
#include "BlockData.h"
#include "TextureData.h"
#include "PerlinNoise/PerlinNoise.hpp"

class Chunk
{
private:
	VAO VAO;
	int WIDTH;
	int HEIGHT;
	int DEPTH;
	double** heightMap;
	std::vector<Vertex> chunkVertices;
	std::vector<std::vector<std::vector<Voxel*>>> chunkBlocks;

	double** generateChunk();
	std::vector<Vertex> convertVerticesToVector(FaceVertices faceVertices);
	void integrateFace(Voxel* block, BlockFaces face);
	void generateBlocks();
	void buildChunk();

public:
	Chunk(int width, int height, int depth);
	void render();
};

#endif