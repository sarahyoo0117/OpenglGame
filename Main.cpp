#include "Mesh.h"

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
	Vertex vertices[] =
	{  //positions							//texture coords
	   // Front
	  Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	   // Right
	  Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 0.0f)},
	   // Back
	  Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(1.0f, 0.0f)},
	   // Left
	  Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	   // Top
	  Vertex{glm::vec3(-0.5f, 0.5f, -0.5f),	glm::vec2(0.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, -0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, 0.5f, 0.5f),	glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, 0.5f, 0.5f),	glm::vec2(1.0f, 0.0f)},
	   // Bottom
	  Vertex{glm::vec3(-0.5f, -0.5f, 0.5f),	glm::vec2(0.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, 0.5f),	glm::vec2(1.0f, 1.0f)},
	  Vertex{glm::vec3(-0.5f, -0.5f, -0.5f),glm::vec2(0.0f, 0.0f)},
	  Vertex{glm::vec3(0.5f, -0.5f, -0.5f),	glm::vec2(1.0f, 0.0f)}
	};

	Texture textures[] =
	{
		Texture("Dirt_Block.png", "block", 0, GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE)
	};

	//Shader
	Shader shaderProgram("default.vert", "default.frag");
	
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 3.0f));

	std::vector<Vertex> vertexVectors(vertices, vertices + sizeof(vertices) / sizeof(Vertex));
	std::vector<Texture> textureVectors(textures, textures + sizeof(textures) / sizeof(Texture));

	Mesh mesh(vertexVectors, textureVectors);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window)) {
		//background color
		glClearColor(0.2f, 0.13f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//TODO:camera frame setup so that the speed is equal to all users
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera.speed = 25.0f * deltaTime; //TODO
		//std::cout << camera.speed << std::endl;

		camera.updateMatrix(fovAngle, 0.1f, 100.0f);
		camera.processKeyboardInputs(window);
		camera.processMouseInputs(window);

		//chunk
		for (int i = 0; i < 5; i++)
		{
			for (int r = 0; r < 10 - 2 * i; r++) 
			{
				for (int c = 0; c < 10 - 2 * i; c++)
				{
					glm::mat4 model = glm::mat4(1.0f);
					glm::vec3 position = glm::vec3(1.0f * c + i, 1.0f * i, 1.0f * r + i);
					mesh.Draw(shaderProgram, camera, model, position);
				}
			}
		}

		//update window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}