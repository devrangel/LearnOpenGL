#pragma once

#include <iostream>

#include "GLEW/glew.h"

#include "utils/shader.h"

namespace Geometry
{
	class RectangleTexture
	{
	public:
		RectangleTexture(const char* path0, const char* path1);
		void draw();
	private:
		Shader m_shaderProgram;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
	};
}