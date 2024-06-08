#include "Chunk.h"

Chunk::Chunk(int width, int height, int depth, std::vector<Texture>& textures)
{
	this->WIDTH = width;
	this->HEIGHT = height;
	this->DEPTH = depth;
	this->heightMap = generateChunk();
	//this->chunkBlocks.resize(WIDTH, std::vector<std::vector<Voxel>>(DEPTH, std::vector<Voxel>(HEIGHT)));

	this->textures = textures; //TODO: texture atlas
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
			heightMap[x][z] = perlin.octave2D_01(x, z, 4) * 10; //TODO::adjust number
			std::cout << heightMap[x][z]  << std::endl;
		}
	}
	return heightMap;
}

void Chunk::integrateFace(Shader& shader, Voxel& block, BlockFaces face)
{
	std::vector<Vertex> vertices = convertVertexToVector(face);
	this->chunkVertices.insert(chunkVertices.begin(), vertices.begin(), vertices.end()); //TODO: Face Culling?
	block.Draw(shader, vertices, this->textures);
}

void Chunk::generateBlocks(Shader& shader)
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < HEIGHT; z++)
		{
			int columnHeight = (int)(heightMap[x][z]); //TODO:: generate chunk using peril noise
			//std::cout << columnHeight << std::endl;
			for (int y = 0; y < columnHeight; y++)
			{
				if (y < columnHeight)
				{
					Voxel block(glm::vec3(x, y, z), BlockType::DIRT);
					//chunkBlocks[x][y][z] = block;

					int numOfFaces = 0;

					integrateFace(shader, block, BlockFaces::FRONT);
					integrateFace(shader, block, BlockFaces::BACK);
					integrateFace(shader, block, BlockFaces::LEFT);
					integrateFace(shader, block, BlockFaces::RIGHT);
					integrateFace(shader, block, BlockFaces::TOP);
					integrateFace(shader, block, BlockFaces::BOTTOM);

					numOfFaces += 6;
				}
				else
				{
					Voxel block(glm::vec3(x, y, z), BlockType::EMPTY);
				}
			}
		}
	}
}