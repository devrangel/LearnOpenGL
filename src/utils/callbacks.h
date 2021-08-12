#pragma once

#include "GLFW/glfw3.h"

namespace Callbacks
{
	static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	static void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}
}