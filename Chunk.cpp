#include "Chunk.h"

Chunk::Chunk(int width, int height, int depth, std::vector<Texture>& textures) 
	: WIDTH(width), HEIGHT(height), DEPTH(depth), textures(textures)
{
	this->heightMap = generateChunk();
	this->chunkBlocks.resize(width, std::vector<std::vector<Voxel*>>(height, std::vector<Voxel*>(depth, nullptr))); //TODO
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
			heightMap[x][z] = perlin.octave2D_01(x, z, 4) * 10; //TODO::adjust number
			//std::cout << heightMap[x][z]  << std::endl;
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
	this->chunkVertices.insert(chunkVertices.begin(), faceVertices.begin(), faceVertices.end()); //TODO: Face Culling?
}

void Chunk::generateBlocks()
{
	for (int x = 0; x < WIDTH; x++)
	{
		for (int z = 0; z < HEIGHT; z++)
		{
			int columnHeight = (int)(heightMap[x][z]); //TODO:: generate chunk using peril noise
			std::cout << columnHeight << std::endl;
			for (int y = 0; y < DEPTH; y++)
			{
				if (y < columnHeight)
				{
					delete chunkBlocks[x][z][y];
					chunkBlocks[x][z][y] = new Voxel(glm::vec3(x, y, z), BlockType::DIRT);
				}
				else
				{
					delete chunkBlocks[x][z][y];
					chunkBlocks[x][z][y] = new Voxel(glm::vec3(x, y, z), BlockType::EMPTY);
				}
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
				//TODO: check qualifications and draw faces

			}
		}
	}
}

void Chunk::render(Shader& shader)
{
	//draw faces
	this->VAO.Bind();

	VBO VBO(this->chunkVertices);

	this->VAO.LinkAttrib(VBO, 0, 3, GL_FLOAT, sizeof(Vertex), (void*)0);
	this->VAO.LinkAttrib(VBO, 1, 2, GL_FLOAT, sizeof(Vertex), (void*)(3 * sizeof(float)));

	VBO.Unbind();

	shader.Activate();

	int blockNum = 0;
	for (int i = 0; i < textures.size(); i++)
	{
		std::string num;
		std::string name = textures[i].name;
		if (name == "block")
		{
			num = std::to_string(blockNum++);
		}
		textures[i].setTextureUnit(shader, (name + num).c_str(), i);
		textures[i].Bind();
	}

	glDrawArrays(GL_TRIANGLES, 0, this->chunkVertices.size());
}