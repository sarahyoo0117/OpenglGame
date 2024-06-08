#pragma once
#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include <vector>
#include <list>
#include "Texture.h"
#include "Voxel.h"
#include "BlockData.h"
#include "PerlinNoise/PerlinNoise.hpp"

class Chunk
{
private:
	int WIDTH;
	int HEIGHT;
	int DEPTH;
	double** heightMap;
	std::vector<Vertex> chunkVertices;
	std::vector<std::vector<std::vector<Voxel>>> chunkBlocks;

	std::vector<Texture> textures; //TODO
public:
	Chunk(int width, int height, int depth, std::vector<Texture>& textures);
	double** generateChunk();
	void integrateFace(Shader& shader, Voxel& block, BlockFaces face);
	void generateBlocks(Shader& shader);
};

#endif