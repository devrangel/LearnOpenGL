#pragma once

#include "GLEW/glew.h"

namespace Geometry
{
	class Rectangle
	{
	public:
		Rectangle(bool wireframeMode);
		void draw(const GLuint& shaderProgram);
	private:
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
	};
}