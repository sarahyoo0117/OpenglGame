#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

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

	GLfloat verticesWithColors[] =
	{	//positions				//color	
		-0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f, //0
		0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,  //1
		0.0f, (0.5f / 8 + 0.5f + 0.5f / 8), 0.0f,     0.0f, 0.0f, 1.0f,//2
		-0.5f / 2, 0.5f / 8, 0.0f,    1.0f, 0.0f, 0.0f,//3
		0.5f / 2, 0.5f / 8, 0.0f,     0.0f, 1.0f, 0.0f,//4
		0.0f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,//5
		-0.5f * 3 / 4, (0.5f / 8 - 0.5f) / 2, 0.0f,      1.0f, 0.0f, 0.0f,//6
		-0.5f / 4, (0.5f / 8 - 0.5f) / 2, 0.0f,     0.0f, 1.0f, 0.0f,//7
		-0.5f / 2, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,//8
		0.5f / 4, (0.5f / 8 - 0.5f) / 2, 0.0f,      1.0f, 0.0f, 0.0f,//9
		0.5f * 3 / 4, (0.5f / 8 - 0.5f) / 2, 0.0f,      0.0f, 1.0f, 0.0f,//10
		0.5f / 2, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,//11
		-0.5f / 4, ((0.5f / 8 + 0.5f + 0.5f / 8) + 0.5f / 8) / 2, 0.0f,     1.0f, 0.0f, 0.0f, //12
		0.5f/ 4, ((0.5f / 8 + 0.5f + 0.5f / 8) + 0.5f / 8) / 2, 0.0f,      0.0f, 1.0f, 0.0f,//13
		0.0f, 0.5f / 8, 0.0f,     0.0f, 0.0f, 1.0f,//14
	};

	GLfloat vertices[] =
	{	//positions			
		-0.5f, -0.5f, 0.0f, //0
		0.5f, -0.5f, 0.0f, //1
		0.0f, (0.5f / 8 + 0.5f + 0.5f / 8), 0.0f, //2
		-0.5f / 2, 0.5f / 8, 0.0f,//3
		0.5f / 2, 0.5f / 8, 0.0f, //4
		0.0f, -0.5f, 0.0f, //5
		-0.5f * 3 / 4, (0.5f / 8 - 0.5f) / 2, 0.0f, //6
		-0.5f / 4, (0.5f / 8 - 0.5f) / 2, 0.0f, //7
		-0.5f / 2, -0.5f, 0.0f, //8
		0.5f / 4, (0.5f / 8 - 0.5f) / 2, 0.0f, //9
		0.5f * 3 / 4, (0.5f / 8 - 0.5f) / 2, 0.0f, //10
		0.5f / 2, -0.5f, 0.0f, //11
		-0.5f / 4, ((0.5f / 8 + 0.5f + 0.5f / 8) + 0.5f / 8) / 2, 0.0f, //12
		0.5f / 4, ((0.5f / 8 + 0.5f + 0.5f / 8) + 0.5f / 8) / 2, 0.0f, //13
		0.0f, 0.5f / 8, 0.0f, //14
	};

	GLuint indices[] = {
		0, 6, 8,
		8, 7, 5,
		6, 3, 7,
		3, 12, 14,
		12, 2, 13,
		14, 13, 4,
		9, 4, 10,
		5, 9, 11,
		11, 10, 1
	};

	VAO VAO1;
	VAO1.Bind();

	VBO VBO1(verticesWithColors, sizeof(verticesWithColors));
	EBO EBO1(indices, sizeof(indices));

	//configure position & color attributes
	const int numOfVertexArrayAttribs = 6; //for normal vertices, set it to be 3.
	VAO1.LinkAttrib(VBO1, 0, 3, GL_FLOAT, numOfVertexArrayAttribs * sizeof(float), (void *)0);
	VAO1.LinkAttrib(VBO1, 1, 3, GL_FLOAT, numOfVertexArrayAttribs * sizeof(float), (void*)(3 * sizeof(float)));

	//unbind vertex array and buffers
	VAO1.Unbind();
	VBO1.Unbind();
	EBO1.Unbind();

	while (!glfwWindowShouldClose(window)) {
		//background color
		glClearColor(0.2f, 0.13f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//update uniform color (only usable with vertices)
		//float timeValue = glfwGetTime();
		//float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
		//shaderProgram.setUniformColor("ourColor", 1.0f, greenValue, 0.3f, 1.0f);

		shaderProgram.Activate();

		//draw verteces
		VAO1.Bind();
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

		//update window
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	VAO1.Delete();
	VBO1.Delete();
	EBO1.Delete();
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}