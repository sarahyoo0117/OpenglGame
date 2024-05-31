#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos, 1.0);\n"
"}\0";
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"uniform vec4 ourColor;\n"
"void main()\n"
"{\n"
"   FragColor = ourColor;\n"
"}\n\0";

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

	//creates shaders
	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);

	//creates shader program
	GLuint shaderProgram = glCreateProgram();

	//attach thoes two shaders above to the program
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

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
		0.5f/ 4, ((0.5f / 8 + 0.5f + 0.5f / 8) + 0.5f / 8) / 2, 0.0f, //13
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

	GLuint VAO, VBO, EBO;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);//binds the VBO
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //introduce vertices into VBO

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	//configuer the vertex attribute.
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	//enables vertex attribute
	glEnableVertexAttribArray(0);

	//unbind vertex array and buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	//add color to window
	glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	while (!glfwWindowShouldClose(window)) {
		//background color
		glClearColor(0.2f, 0.13f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//update uniform color
		float timeValue = glfwGetTime();
		float colorValue = (sin(timeValue) / 2.0f) + 0.5f;
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUseProgram(shaderProgram);
		glUniform4f(vertexColorLocation, 1.0f, colorValue, 0.3f, 1.0f);

		//draw verteces
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, sizeof(indices), GL_UNSIGNED_INT, 0);

		//update window
		glfwSwapBuffers(window);

		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}