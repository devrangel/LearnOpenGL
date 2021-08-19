#pragma once

#include <array>

#include "GLEW/glew.h"
#include "GLFW/glfw3.h"
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "geometry.h"
#include "camera.h"
#include "utils/shader.h"

class Cube : public IGeometry
{
public:
	Cube(const char* path0, const char* path1);
	void draw(const Camera& camera) override;
private:
	Shader m_shaderProgram;
	GLuint m_VAO;
	GLuint m_VBO;
	std::array<glm::vec3, 10> m_CubePositions;

	glm::vec3 m_CameraPos;
	glm::vec3 m_CameraFront;
	glm::vec3 m_CameraUp;
};