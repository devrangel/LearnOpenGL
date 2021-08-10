#include "triangle.h"

namespace Geometry
{
	Triangle::Triangle()
	{
		float vertices[] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f
		};

		this->m_VAO;
		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		this->m_VBO;
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	void Triangle::draw(const GLuint& shaderProgram)
	{
		glUseProgram(shaderProgram);
		glBindVertexArray(this->m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
	}
}