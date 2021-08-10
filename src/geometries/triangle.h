#pragma once

#include "GLEW/glew.h"

namespace Geometry
{
	class Triangle
	{
	public:
		Triangle();
		GLuint getVAO();
	private:
		GLuint m_VAO;
		GLuint m_VBO;
	};
}
