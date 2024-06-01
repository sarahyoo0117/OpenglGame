#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::processMatrix(float FOVangle, float near, float far, Shader& shader, const char* uniformName)
{
	glm::mat4 view = glm::mat4(1.0f);
	glm::mat4 projection = glm::mat4(1.0f);

	view = glm::lookAt(Position, Position + Orientation, Up);
	projection = glm::perspective(glm::radians(FOVangle), (float)width / height, near, far);

	GLuint uniformLocation = glGetUniformLocation(shader.ID, uniformName);
	glUniformMatrix4fv(uniformLocation, 1, GL_FALSE, glm::value_ptr(projection * view));
}

void Camera::processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		Position += speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		Position -= speed * Orientation;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		Position += glm::normalize(glm::cross(Orientation, Up)) * speed;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		Position -= glm::normalize(glm::cross(Orientation, Up)) * speed;
	}
}