#ifndef CAMERA_CLASS_H
#define CAMERA_CLASS_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Shader.h"

class Camera
{
public:
	//main vectors of the camera
	glm::vec3 Position;
	glm::vec3 Orientation = glm::vec3(0.0f, 0.0f, -0.1f);
	glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);

	int width, height;
	float speed = 50.0f;
	float sensitivity = 0.1f;
	float yaw = -90.0f;
	float pitch = 0.0f;
	float lastX, lastY;
	bool isFirstClick = true;

	Camera(int width, int height, glm::vec3 position);
	void processMatrix(float FOVangle, float near, float far, Shader& shader, const char* uniformName);
	void processKeyboardInputs(GLFWwindow* window);
	void processMouseInputs(GLFWwindow* window);
};

#endif