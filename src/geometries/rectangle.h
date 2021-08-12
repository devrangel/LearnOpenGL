#pragma once

#include "GLEW/glew.h"

#include "utils/shader.h"

namespace Geometry
{
	class Rectangle
	{
	public:
		Rectangle(bool wireframeMode);
		void draw();
	private:
		Shader m_shaderProgram;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
	};
}