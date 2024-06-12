#include "Chunk.h"
#include "Camera.h"

const unsigned int windowWidth = 1440;
const unsigned int windowHeight = 900;

float fovAngle = 45.0f;
float deltaTime, lastFrame = 0.0f;


int main() {
	glfwInit();

	//we are using OpenGL 3.3 version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	
	GLFWwindow* window = glfwCreateWindow(windowWidth, windowHeight, "My OpenGl Game", NULL, NULL);

	if (window == NULL) {
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	gladLoadGL();
	glViewport(0, 0, windowWidth, windowHeight);

	Shader shaderProgram("default.vert", "default.frag");

	Texture TerrainTexture("Terrain.png", 0, GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE);
	TerrainTexture.setTextureUnit(shaderProgram, "terrainTex");
	TerrainTexture.Bind();
	
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 3.0f));
	Chunk chunk(16, 16, 16);

	glEnable(GL_DEPTH_TEST);
	glFrontFace(GL_CCW);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	double prevTime = 0.0;
	double crntTime = 0.0;
	double timeDiff;
	unsigned int count = 0;

	while (!glfwWindowShouldClose(window)){
		//FPS counter
		crntTime = glfwGetTime();
		timeDiff = crntTime - prevTime;
		count++;
		if (timeDiff >= 1.0 / 30.0)
		{
			std::string FPS = std::to_string((1.0 / timeDiff) * count);
			std::string ms = std::to_string((timeDiff / count) * 1000);
			std::string newTitle = "My Opengl Game - " + FPS + "FPS / " + ms + "ms";
			glfwSetWindowTitle(window, newTitle.c_str());
			prevTime = crntTime;
			count = 0;
		}

		//background color
		glClearColor(0.2f, 0.13f, 0.37f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//TODO:camera frame setup so that the speed is equal to all users
		float currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		camera.speed = 25.0f * deltaTime; //TODO: ?

		camera.updateMatrix(fovAngle, 0.1f, 100.0f);
		camera.processKeyboardInputs(window);
		camera.processMouseInputs(window);
		camera.setMatrix(shaderProgram, "cameraMatrix");


		chunk.render();

		//update window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}