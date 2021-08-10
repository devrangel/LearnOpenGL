#include <iostream>
#include <cassert>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "geometries/triangle.h"
#include "utils/callbacks.h"

const int WIDTH_SCREEN = 800;
const int HEIGHT_SCREEN = 600;

GLuint compileShader(GLenum shaderType, const GLchar* const* shaderSourceCode);
GLuint createProgram(GLuint vertexShader, GLuint fragmentShader);

const char* vertexShaderCode = R"(#version 330 core
layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
}
)";

const char* fragmentShaderCode = R"(#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

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
	glGetIntegerv(GL_MAJOR_VERSION, &GLMajorVersion);
	glGetIntegerv(GL_MINOR_VERSION, &GLMinorVersion);
	std::cout << "OpenGL Version: " << GLMajorVersion << "." << GLMinorVersion << std::endl;
	std::cout << "OpenGL Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "OpenGL Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
	std::cout << "GLSL Version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

	// ----------------------------------------------------------------------------------------
	// ----------------------------------------------------------------------------------------
	// ----------------------------------------------------------------------------------------

	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, &vertexShaderCode);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, &fragmentShaderCode);
	GLuint shaderProgram = createProgram(vertexShader, fragmentShader);

	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

	Geometry::Triangle triangle;

	while (!glfwWindowShouldClose(window))
	{
		Callbacks::processInput(window);

		glClear(GL_COLOR_BUFFER_BIT);

		// Draw
		triangle.draw(shaderProgram);

		glfwSwapBuffers(window);
		glfwWaitEvents();
	}

	glfwTerminate();
	return 0;
}

GLuint compileShader(GLenum shaderType, const GLchar* const *shaderSourceCode)
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSourceCode, nullptr);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	if (shaderType == GL_VERTEX_SHADER)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}
	}

	return shader;
}

GLuint createProgram(GLuint vertexShader, GLuint fragmentShader)
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
