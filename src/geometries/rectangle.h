#pragma once

#include "GLEW/glew.h"

#include "utils/shader.h"
#include "geometry.h"
#include "camera.h"

namespace Geometry
{
	class Rectangle : IGeometry
	{
	public:
		Rectangle(bool wireframeMode);
		void draw(const Camera& camera) override;
	private:
		Shader m_shaderProgram;
		GLuint m_VAO;
		GLuint m_VBO;
		GLuint m_IBO;
	};
}