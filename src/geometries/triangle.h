#pragma once

#include <cmath>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"

namespace Geometry
{
	class Triangle
	{
	public:
		Triangle();
		void drawSingleColor(const GLuint& shaderProgram);
		void drawSingleColorVarying(const GLuint& shaderProgram);
	private:
		GLuint m_VAO;
		GLuint m_VBO;
	};
}
