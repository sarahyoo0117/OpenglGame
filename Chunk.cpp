#include "Chunk.h"

Chunk::Chunk(int width, int height, int depth) 
	: WIDTH(width), HEIGHT(height), DEPTH(depth)
{
	this->heightMap = generateChunk();
	this->chunkBlocks.resize(width, std::vector<std::vector<Voxel*>>(depth, std::vector<Voxel*>(height, nullptr)));
	generateBlocks();
	buildChunk();
}

double** Chunk::generateChunk() { 
	siv::PerlinNoise::seed_type seed = 123456u;
	siv::PerlinNoise perlin{ seed };

	//allocate memory for height map
	double** heightMap = new double* [WIDTH];

	for (int i = 0; i < WIDTH; ++i) {
		heightMap[i] = new double[DEPTH];
	}

	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < HEIGHT; z++)
		{
			heightMap[x][z] = perlin.octave2D_01(x, z, 4) * 10; //TODO::fix perlin noise
		}
	}
	return heightMap;
}

std::vector<Vertex> Chunk::convertVerticesToVector(FaceVertices faceVertices)
{
	return std::vector<Vertex>(faceVertices.begin(), faceVertices.end());
}

void Chunk::integrateFace(Voxel* block, BlockFaces face)
{
	std::vector<Vertex> faceVertices = convertVerticesToVector(block->getFaceVertices(face));
	this->chunkVertices.insert(chunkVertices.begin(), faceVertices.begin(), faceVertices.end()); 
}

void Chunk::generateBlocks()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < HEIGHT; z++)
		{
			int columnHeight = (int)(heightMap[x][z]);
			for (int y = 0; y < DEPTH; y++)
			{
				BlockType type = BlockType::EMPTY;
				if (y == columnHeight)
				{
					type = BlockType::GRASS;
				}
				else if (y < columnHeight)
				{
					type = BlockType::DIRT;
				}

				delete chunkBlocks[x][y][z];
				chunkBlocks[x][y][z] = new Voxel(glm::vec3(x, y, z), type);
			}
		}
	}
}

void Chunk::buildChunk()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < HEIGHT; z++)
		{
			for (int y = 0; y < DEPTH; y++) 
			{
				if (chunkBlocks[x][y][z]->type != BlockType::EMPTY)
				{
					//left faces: block to left is empty & not farthest left in the chunk
					if (x > 0)
					{
						if (chunkBlocks[x - 1][y][z]->type == BlockType::EMPTY)
						{
							integrateFace(chunkBlocks[x][y][z], BlockFaces::LEFT);
						}
					}
					else
					{
						integrateFace(chunkBlocks[x][y][z], BlockFaces::LEFT);
					}

					//right faces: block to right is empty & farthest right in chunk
					if (x < WIDTH - 1)
					{
						if (chunkBlocks[x + 1][y][z]->type == BlockType::EMPTY)
						{
							integrateFace(chunkBlocks[x][y][z], BlockFaces::RIGHT);
						}
					}
					else
					{
						integrateFace(chunkBlocks[x][y][z], BlockFaces::RIGHT);
					}

					//top faces: block above is empty & fartest up in chunk
					if (y < DEPTH - 1)
					{
						if (chunkBlocks[x][y + 1][z]->type == BlockType::EMPTY)
						{
							integrateFace(chunkBlocks[x][y][z], BlockFaces::TOP);
						}
					}
					else
					{
						integrateFace(chunkBlocks[x][y][z], BlockFaces::TOP);
					}

					//bottom faces: block below is empty & farthes down in chunk
					if (y > 0)
					{
						if (chunkBlocks[x][y - 1][z]->type == BlockType::EMPTY)
						{
							integrateFace(chunkBlocks[x][y][z], BlockFaces::BOTTOM);
						}
					}
					else
					{
						integrateFace(chunkBlocks[x][y][z], BlockFaces::BOTTOM);
					}

					//front faces
					if (z < HEIGHT - 1)
					{
						if (chunkBlocks[x][y][z + 1]->type == BlockType::EMPTY)
						{
							integrateFace(chunkBlocks[x][y][z], BlockFaces::FRONT);
						}
					}
					else
					{
						integrateFace(chunkBlocks[x][y][z], BlockFaces::FRONT);
					}

					//back faces
					if (z > 0)
					{
						if (chunkBlocks[x][y][z - 1]->type == BlockType::EMPTY)
						{
							integrateFace(chunkBlocks[x][y][z], BlockFaces::BACK);
						}
					}
					else
					{
						integrateFace(chunkBlocks[x][y][z], BlockFaces::BACK);
					}
				}
			}
		}
	}
}

void Chunk::render()
{	
	//draw faces
	this->VAO.Bind();

	VBO VBO(this->chunkVertices);

	this->VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	this->VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	VBO.Unbind();

	glDrawArrays(GL_TRIANGLES, 0, this->chunkVertices.size());
}