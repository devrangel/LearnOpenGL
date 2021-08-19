#pragma once

#include <iostream>

#include "GLEW/glew.h"

#include "utils/shader.h"
#include "geometry.h"
#include "camera.h"

namespace Geometry
{
	class RectangleTexture : IGeometry
	{
	public:
		RectangleTexture(const char* path0, const char* path1);
		void draw(const Camera& camera) override;
	private:
		Shader m_shaderProgram;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
	};
}