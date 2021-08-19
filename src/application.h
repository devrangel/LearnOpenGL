#pragma once

#include <iostream>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "scene.h"
#include "globals.h"

class Application
{
public:
	Application(int screenWidth, int screenHeight, const char* title)
		: m_ScreenWidth(screenWidth), m_ScreenHeight(screenHeight)
	{
		if (glfwInit() != GLFW_TRUE)
		{
			std::cout << "Failed to initialize GLFW" << std::endl;
		}
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		// Creates a GLFW window and makes it current
		this->m_Window = glfwCreateWindow(screenWidth, screenHeight, title, nullptr, nullptr);
		if (this->m_Window == nullptr)
		{
			std::cout << "Failed to create GLFW window" << std::endl;
			glfwTerminate();
		}
		glfwMakeContextCurrent(this->m_Window);

		// Callbacks for GLFW
		glfwSetFramebufferSizeCallback(this->m_Window, this->framebufferSizeCallback);
		glfwSetInputMode(this->m_Window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
		glfwSetCursorPosCallback(this->m_Window, this->mouseCallback);

		if (glewInit() != GLEW_OK)
		{
			std::cout << "Failed to initialize GLEW" << std::endl;
		}

		// Display OpenGL infos
		GLint GLMajorVersion = 0;
		GLint GLMinorVersion = 0;
		GLint nrVertexAttributes;
		glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
		glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
		std::cout << "OpenGL Version: " << GLMajorVersion << "." << GLMinorVersion << std::endl;
		std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
		std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
		std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
		std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;
		glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &nrVertexAttributes);
		std::cout << "Max number of vertex attributes supported: " << nrVertexAttributes << std::endl;

		// Initialize global variables
		Global::firstMouse = true;
		Global::lastX = screenWidth / 2.0f;
		Global::lastY = screenHeight / 2.0f;
	}

	void run(Scene& scene)
	{
		while (!glfwWindowShouldClose(this->m_Window))
		{
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

			this->processInput(this->m_Window);

			scene.draw(this->m_Window);

			glfwSwapBuffers(this->m_Window);
			glfwPollEvents();
		}
	}

	static void framebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}

	void processInput(GLFWwindow* window)
	{
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, true);
		}
	}

	static void mouseCallback(GLFWwindow* window, double xpos, double ypos)
	{
		float xPos = (float)xpos;
		float yPos = (float)ypos;

		if (Global::firstMouse)
		{
			Global::lastX = xPos;
			Global::lastY = yPos;
			Global::firstMouse = false;
		}

		float xoffset = xPos - Global::lastX;
		float yoffset = Global::lastY - yPos;

		Global::lastX = xPos;
		Global::lastY = yPos;
	}

private:
	GLFWwindow* m_Window;
	int m_ScreenWidth;
	int m_ScreenHeight;
};