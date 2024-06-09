#include "Chunk.h"
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

	Texture textures[] =
	{
		Texture("Dirt_Block.png", "block", 0, GL_TEXTURE_2D, GL_RGBA, GL_RGBA, GL_UNSIGNED_BYTE)
	};
	std::vector<Texture> textureVectors(textures, textures + sizeof(textures) / sizeof(Texture)); //TODO:: Texture Atlas

	Shader shaderProgram("default.vert", "default.frag");
	Camera camera(windowWidth, windowHeight, glm::vec3(0.0f, 0.0f, 3.0f));
	Chunk chunk(16, 16, 16, textureVectors);

	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_CULL_FACE);
	//glCullFace(GL_BACK);
	//glFrontFace(GL_CCW);

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
		camera.speed = 25.0f * deltaTime; //TODO
		//std::cout << camera.speed << std::endl;

		camera.updateMatrix(fovAngle, 0.1f, 100.0f);
		camera.processKeyboardInputs(window);
		camera.processMouseInputs(window);
		camera.setMatrix(shaderProgram, "cameraMatrix");

		//chunk
		chunk.render(shaderProgram);

		//update window
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	shaderProgram.Delete();

	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}