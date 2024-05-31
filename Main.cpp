#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include "Texture.h"

int main() {
	//initialize GLFW
	glfwInit();

	//Tell GLFW what version of OpenGl we are using. --> we are using 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//Tell GLFW we are using core profile, meaning we are only using the modern function.
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	//Creates window
	GLFWwindow* window = glfwCreateWindow(1042, 796, "My OpenGl Game", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	//adds the window to the current context
	glfwMakeContextCurrent(window);

	//setup gl viewport
	gladLoadGL();
	glViewport(0, 0, 1024, 796);

	//Shader
	Shader shaderProgram("shader.vert", "shader.frag");

	//square vertices
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
	const int numOfIndices = 6;

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(vertices, sizeof(vertices));
	EBO EBO1(indices, sizeof(indices));

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


	while (!glfwWindowShouldClose(window)) {
		//background color
		glClearColor(0.2f, 0.13f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		shaderProgram.Activate();

		//adjusts the picture scale
		glUniform1f(uniformID, 1);

		//activates textures
		texture0.Activate();
		texture0.Bind();
		
		texture1.Activate();
		texture1.Bind();

		//draw verteces
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, numOfIndices, GL_UNSIGNED_INT, 0);

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