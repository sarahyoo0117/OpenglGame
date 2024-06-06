#pragma once
#ifndef CHUNK_CLASS_H
#define CHUNK_CLASS_H

#include "Mesh.h"

class Chunk
{
public:
	Chunk(Shader& shader);
	void GenerateChunk(int width, int length, int height);
private:
	Mesh* Block;
	Shader& ShaderProgram;
};

#endif