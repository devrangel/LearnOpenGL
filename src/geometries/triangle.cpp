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
		glGenBuffers(1, &this->m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		glBindVertexArray(0);
	}

	void Triangle::drawSingleColor(const GLuint& shaderProgram)
	{
		glUseProgram(shaderProgram);

		int uColorLocation = glGetUniformLocation(shaderProgram, "uColor");
		glUniform4f(uColorLocation, 1.0f, 0.5f, 0.2f, 1.0f);

		glBindVertexArray(this->m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	void Triangle::drawSingleColorVarying(const GLuint& shaderProgram)
	{
		float timeValue = (float)glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;

		glUseProgram(shaderProgram);

		int uColorLocation = glGetUniformLocation(shaderProgram, "uColor");
		glUniform4f(uColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(this->m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}