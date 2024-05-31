#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb/stb_image.h>

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

	//texture
	unsigned int texture0, texture1;
	glGenTextures(1, &texture0);
	glBindTexture(GL_TEXTURE_2D, texture0);

	//texture settings
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	//get images for texture0
	int texWidth, texHeight, nrChannels;
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("container.jpg", &texWidth, &texHeight, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
		glEnable(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data); //deletes the image data as it is in Opengl texture object now
	
	//texture 1
	glGenTextures(1, &texture1);
	glBindTexture(GL_TEXTURE_2D, texture1);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	data = stbi_load("awesomeface.png", &texWidth, &texHeight, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texWidth, texHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	stbi_image_free(data);

	shaderProgram.Activate();

	GLuint tex0Uni = glGetUniformLocation(shaderProgram.ID, "texture0");
	glUniform1i(tex0Uni, 0);

	GLuint tex1Uni = glGetUniformLocation(shaderProgram.ID, "texture1");
	glUniform1i(tex1Uni, 1);


	while (!glfwWindowShouldClose(window)) {
		//background color
		glClearColor(0.2f, 0.13f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//adjusts the picture scale
		glUniform1f(uniformID, 1);

		//activates textures
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		shaderProgram.Activate();

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

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}