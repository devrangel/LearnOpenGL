#pragma once

#include "GLEW/glew.h"

namespace Geometry
{
	class Triangle
	{
	public:
		Triangle();
		void draw(const GLuint& shaderProgram);
	private:
		GLuint m_VAO;
		GLuint m_VBO;
	};
}
