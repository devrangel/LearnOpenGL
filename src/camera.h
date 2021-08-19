#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVY = 0.000005f;
const float ZOOM = 45.0f;

class Camera
{
public:
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	Camera(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp, float yaw = YAW, float pitch = PITCH)
		: position(cameraPos), front(cameraFront), up(cameraUp),
		  m_DeltaTime(0.0f), m_LastFrame(0.0f),
		  m_MovementSpeed(SPEED), m_MouseSensity(SENSITIVY), m_Zoom(ZOOM),
		  m_Yaw(yaw), m_Pitch(pitch)
		  
	{
		this->updateCameraVectors();
	}

	glm::mat4 getViewMatrix() const
	{
		return glm::lookAt(this->position, this->position + this->front, this->up);
	}

	void processKeyboard(GLFWwindow* window)
	{
		// Calculate de delta time in order to make a smooth moviment
		float currentFrame = (float)glfwGetTime();
		this->m_DeltaTime = currentFrame - this->m_LastFrame;
		this->m_LastFrame = currentFrame;

		const float cameraSpeed = this->m_MovementSpeed * m_DeltaTime;

		if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
			position += cameraSpeed * front;

		if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
			position -= cameraSpeed * front;

		if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
			position -= glm::normalize(glm::cross(front, up)) * cameraSpeed;

		if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
			position += glm::normalize(glm::cross(front, up)) * cameraSpeed;
	}

	void processMouseMovement(float xoffset, float yoffset, bool constrainPitch = true)
	{
		xoffset *= this->m_MouseSensity;
		yoffset *= this->m_MouseSensity;

		this->m_Yaw += xoffset;
		this->m_Pitch += yoffset;

		if (constrainPitch)
		{
			if (this->m_Pitch > 89.0f)
				this->m_Pitch = 89.0f;
			if (this->m_Pitch < -89.0f)
				this->m_Pitch = -89.0f;
		}

		this->updateCameraVectors();
	}

private:
	float m_DeltaTime;
	float m_LastFrame;
	float m_MouseSensity;

	float m_MovementSpeed;
	float m_Zoom;

	float m_Yaw;
	float m_Pitch;

	void updateCameraVectors()
	{
		glm::vec3 frontVec;
		frontVec.x = cos(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));
		frontVec.y = sin(glm::radians(this->m_Pitch));
		frontVec.z = sin(glm::radians(this->m_Yaw)) * cos(glm::radians(this->m_Pitch));

		this->front = glm::normalize(frontVec);
		glm::vec3 right = glm::normalize(glm::cross(this->front, this->up));
		this->up = glm::normalize(glm::cross(right, this->front));
	}
};