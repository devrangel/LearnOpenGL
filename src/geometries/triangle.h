#pragma once

#include <cmath>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

#include "utils/shader.h"

namespace Geometry
{
	class Triangle
	{
	public:
		Triangle(bool colorPerVertex);
		void drawSingleColor();
		void drawSingleColorVarying();
		void drawColorPerVertex();
	private:
		Shader m_shaderProgram;
		GLuint m_VAO;
		GLuint m_VBO;
	};
}
