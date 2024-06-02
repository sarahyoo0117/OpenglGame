#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"
#include "Camera.h"

const unsigned int windowWidth = 1440;
const unsigned int windowHeight = 900;

float fovAngle = 45.0f;
float deltaTime, lastFrame = 0.0f;


int main() {
	//initialize GLFW
	glfwInit();

	//Tell GLFW what version of OpenGl we are using. --> we are using 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using core profile, meaning we are only using the modern function.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Creates window
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "My OpenGl Game", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	//adds the window to the current context
	glfwMakeContextCurrent(window);
	//setup gl viewport
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	//3D Cube verteces
	GLfloat vertices[] =
	{  //positions				//texture coords
	   // Front
	   -0.5f, 0.5f, 0.5f,		0.0f, 1.0f,
	   -0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
	   0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
	   0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
	   -0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
	   0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
	   // Right
	   0.5f, 0.5f, 0.5f,		0.0f, 1.0f,
	   0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
	   0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
	   0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
	   0.5f, -0.5f, 0.5f,		0.0f, 0.0f,
	   0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
	   // Back
	   0.5f, 0.5f, -0.5f,		0.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
	   -0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
	   -0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
	   0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
	   -0.5f, -0.5f, -0.5f,		1.0f, 0.0f,
	   // Left
	   -0.5f, 0.5f, -0.5f,		0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
	   -0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
	   -0.5f, 0.5f, 0.5f,		1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
	   -0.5f, -0.5f, 0.5f,		1.0f, 0.0f,
	   // Top
	   -0.5f, 0.5f, -0.5f,		0.0f, 1.0f,
	   -0.5f, 0.5f, 0.5f,		0.0f, 0.0f,
	   0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
	   0.5f, 0.5f, -0.5f,		1.0f, 1.0f,
	   -0.5f, 0.5f, 0.5f,		0.0f, 0.0f,
	   0.5f, 0.5f, 0.5f,		1.0f, 0.0f,
	   // Bottom
	   -0.5f, -0.5f, 0.5f,		0.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
	   0.5f, -0.5f, 0.5f,		1.0f, 1.0f,
	   0.5f, -0.5f, 0.5f,		1.0f, 1.0f,
	   -0.5f, -0.5f, -0.5f,		0.0f, 0.0f,
	   0.5f, -0.5f, -0.5f,		1.0f, 0.0f
	};

	//Shader
	Shader shaderProgram("shader.vert", "shader.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));

	//configure position, color, textureCoords attributes
	const int numOfAttribsInaRow = 5;
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, numOfAttribsInaRow * sizeof(float), (void *)0); //positions
	VAO1.LinkAttrib(VBO1, 1, 2, GL_FLOAT, numOfAttribsInaRow * sizeof(float), (void*)(3 * sizeof(float))); //texture coords

	//unbind vertex array and buffers
	VAO1.Unbind();
	VBO1.Unbind();

	GLuint uniformID = glGetUniformLocation(shaderProgram.ID, "scale");

	//textures
	Texture texture0("Dirt_Block.png", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	texture0.LinkToShader(shaderProgram, "texture0", 0);

	glEnable(GL_DEPTH_TEST);

	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 3.0f));

	while (!glfwWindowShouldClose(window)) {
		//background color
		glClearColor(0.2f, 0.13f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		shaderProgram.Activate();

		//TODO:camera frame setup so that the speed is equal to all users
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera.speed = 25.0f * deltaTime; //TODO
		//std::cout << camera.speed << std::endl;

		camera.processMatrix(fovAngle, 0.1f, 100.0f, shaderProgram, "cameraMatrix");
		camera.processKeyboardInputs(window);
		camera.processMouseInputs(window);
		
		//adjusts the picture scale
		glUniform1f(uniformID, 1.0);

		//activates textures
		texture0.Activate();
		texture0.Bind();

		//draw verteces
		VAO1.Bind();

		//chunks
		for (int i = 0; i < 5; i++)
		{
			for (int r = 0; r < 10 - 2 * i; r++) {
				for (int c = 0; c < 10 - 2 * i; c++)
				{
					glm::mat4 model = glm::mat4(1.0f);
					glm::vec3 position = glm::vec3(1.0f * c + i, 1.0f * i, 1.0f * r + i);
					model = glm::translate(model, position);
					GLuint modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
					glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
					glDrawArrays(GL_TRIANGLES, 0, 36);
				}
			}
		}
		
		//update window
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	shaderProgram.Delete();
	//texture0.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}