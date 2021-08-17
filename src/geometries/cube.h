#pragma once

#include <array>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "utils/shader.h"

namespace Geometry
{
	class Cube
	{
	public:
		Cube(const char* path0, const char* path1);
		void draw();
	private:
		Shader m_shaderProgram;
		GLuint m_VAO;
		GLuint m_VBO;
		std::array<glm::vec3, 10> m_CubePositions;
	};
}