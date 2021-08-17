#include <iostream>
#include <cassert>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "utils/callbacks.h"
//#include "geometries/triangle.h"
//#include "geometries/rectangle.h"
//#include "geometries/rectangle_texture.h"
#include "geometries/cube.h"

const int WIDTH_SCREEN = 800;
const int HEIGHT_SCREEN = 600;

int main()
{
	assert(glfwInit() == GLFW_TRUE);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Creates a GLFW window and makes it current
	GLFWwindow* window = glfwCreateWindow(WIDTH_SCREEN, HEIGHT_SCREEN, "Learn OpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	// Callbacks for GLFW
	glfwSetFramebufferSizeCallback(window, Callbacks::framebufferSizeCallback);

	assert(glewInit() == GLEW_OK);

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

	// ----------------------------------------------------------------------------------------
	// ----------------------------------------------------------------------------------------
	// ----------------------------------------------------------------------------------------

	//Geometry::Triangle triangle(true);
	//Geometry::Rectangle rectangle(true);
	//Geometry::RectangleTexture rectangleTexture("assets/stone.jpg", "assets/face.png");
	Geometry::Cube cube("assets/stone.jpg", "assets/face.png");


	while (!glfwWindowShouldClose(window))
	{
		Callbacks::processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw
		//rectangle.draw();
		//triangle.drawSingleColorVarying(shaderProgram);
		//triangle.drawColorPerVertex();
		cube.draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();
	return 0;
}


