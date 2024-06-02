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

const unsigned int windowWidth = 1024;
const unsigned int windowHeight = 796;

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

	//2D square vertices
	GLfloat vertices[] =
	{    // positions          // colors           // texture coords
		0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
		0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
		-0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
		-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left 
	};

	GLuint indices[] =
	{
		0, 2, 1, //upper triangle
		0, 3, 2  //lower triangle
	};

	//3D Cube verteces
	GLfloat cubeVertices[] =
	{	// positions			// colors           // texture coords
		-0.5f, -0.5f, -0.5f,	1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,//0
		-0.5f, 0.5f, -0.5f,		0.0f, 1.0f, 0.0f,	 1.0f, 1.0f,//1
		0.5f, 0.5f, -0.5f,		0.0f, 0.0f, 1.0f,    1.0f, 1.0f,//2
		0.5f, -0.5f, -0.5f,		1.0f, 1.0f, 0.0f,    1.0f, 0.0f,//3
		0.5f, -0.5f, 0.5f,		1.0f, 0.0f, 0.0f,	 0.0f, 0.0f,//4
		0.5f, 0.5f, 0.5f,		0.0f, 1.0f, 0.0f,	 0.0f, 1.0f,//5
		-0.5f, 0.5f, 0.5f,		0.0f, 0.0f, 1.0f,    1.0f, 1.0f,//6
		-0.5f, -0.5f, 0.5f,		1.0f, 1.0f, 0.0f,    1.0f, 0.0f //7
	};

	GLuint cubeIndices[] =
	{
		//side 1
		0, 1, 2,
		2, 3, 0,
		//side 2
		2, 3, 4,
		4, 5, 2,
		//side 3
		4, 5, 6,
		6, 7, 4,
		//side 4
		6, 7, 0,
		0, 1, 6,
		//side 5
		7, 0, 3,
		3, 4, 7,
		//side 6
		1, 6, 5,
		5, 2, 1
	};

	glm::vec3 cubePositions[] = {
		 glm::vec3(0.0f,  0.0f,  0.0f),
		 glm::vec3(2.0f,  5.0f, -15.0f),
		 glm::vec3(-1.5f, -2.2f, -2.5f),
		 glm::vec3(-3.8f, -2.0f, -12.3f),
		 glm::vec3(2.4f, -0.4f, -3.5f),
		 glm::vec3(-1.7f,  3.0f, -7.5f),
		 glm::vec3(1.3f, -2.0f, -2.5f),
		 glm::vec3(1.5f,  2.0f, -2.5f),
		 glm::vec3(1.5f,  0.2f, -1.5f),
		 glm::vec3(-1.3f,  1.0f, -1.5f)
	};

	//Shader
	Shader shaderProgram("shader.vert", "shader.frag");

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(cubeVertices, sizeof(cubeVertices));
	EBO EBO1(cubeIndices, sizeof(cubeIndices));

	//configure position, color, textureCoords attributes
	const int numOfAttribsInaRow = 8;
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, numOfAttribsInaRow * sizeof(float), (void *)0); //positions
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, numOfAttribsInaRow * sizeof(float), (void*)(3 * sizeof(float))); //colors
	VAO1.LinkAttrib(VBO1, 2, 2, GL_FLOAT, numOfAttribsInaRow * sizeof(float), (void*)(6 * sizeof(float))); //texture coords

	//unbind vertex array and buffers
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	GLuint uniformID = glGetUniformLocation(shaderProgram.ID, "scale");

	//textures
	Texture texture0("container.jpg", GL_TEXTURE_2D, GL_TEXTURE0, GL_RGB, GL_RGB, GL_UNSIGNED_BYTE);
	texture0.LinkToShader(shaderProgram, "texture0", 0);

	Texture texture1("awesomeface.png", GL_TEXTURE_2D, GL_TEXTURE1, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	texture1.LinkToShader(shaderProgram, "texture1", 1);

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
		
		texture1.Activate();
		texture1.Bind();

		//draw verteces
		VAO1.Bind();
		for (int i = 0; i < 10; i++) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, cubePositions[i]);
			
			float angle = 50.0f * (i + 1);
			model = glm::rotate(model, (float)glfwGetTime() * glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
			
			GLuint modelLocation = glGetUniformLocation(shaderProgram.ID, "model");
			glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));
			
			glDrawElements(GL_TRIANGLES, sizeof(cubeIndices) / sizeof(int), GL_UNSIGNED_INT, 0);
		}

		//update window
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();
	texture0.Delete();
	texture1.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}