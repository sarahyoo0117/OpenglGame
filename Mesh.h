#pragma once
#ifndef MESH_CLASS_H
#define MESH_CLASS_H

#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <vector>
#include "Shader.h"
#include "Texture.h"
#include "VAO.h"
#include "VBO.h"

class Mesh
{
public:
	std::vector<Vertex> vertices;
	std::vector<Texture> textures;

	Mesh(std::vector<Vertex>& vertices, std::vector<Texture>& textures);
	void Draw(Shader& shader, glm::mat4 model, glm::vec3 position);
private:
	VAO VAO;
};

#endif