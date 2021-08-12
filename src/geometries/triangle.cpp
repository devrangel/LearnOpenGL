#include "triangle.h"

// For drawSingleColor() and drawSingleColorVarying()
static const char* vertexShaderCodeSingleColor = R"(#version 330 core
layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
}
)";

// For drawSingleColor() and drawSingleColorVarying()
static const char* fragmentShaderCodeSingleColor = R"(#version 330 core
out vec4 FragColor;

uniform vec4 uColor;

void main()
{
	FragColor = uColor;
}
)";

// For drawColorPerVertex()
static const char* vertexShaderCodeColorPerVertex = R"(#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;

out vec3 outColor;

void main()
{
	outColor = aColor;
	gl_Position = vec4(aPos, 1.0f);
}
)";

// For drawColorPerVertex()
static const char* fragmentShaderCodeColorPerVertex = R"(#version 330 core
in vec3 outColor;

out vec4 FragColor;

void main()
{
	FragColor = vec4(outColor, 1.0);
}
)";

namespace Geometry
{
	Triangle::Triangle(bool colorPerVertex)
	{
		// For drawSingleColor() and drawSingleColorVarying()
		if (!colorPerVertex)
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

			this->m_shaderProgram = Shader(vertexShaderCodeSingleColor, fragmentShaderCodeSingleColor);
		}
		// For drawColorPerVertex()
		else
		{
			float vertices[] = {
				// Positions		// Colors
				 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom right
				-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, // bottom left
				 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f  // top
			};

			this->m_VAO;
			glGenVertexArrays(1, &this->m_VAO);
			glBindVertexArray(this->m_VAO);

			this->m_VBO;
			glGenBuffers(1, &this->m_VBO);
			glBindBuffer(GL_ARRAY_BUFFER, this->m_VBO);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			// Position
			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			// Color
			glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
			glEnableVertexAttribArray(1);

			glBindVertexArray(0);

			this->m_shaderProgram = Shader(vertexShaderCodeColorPerVertex, fragmentShaderCodeColorPerVertex);
		}
	}

	void Triangle::drawSingleColor()
	{
		this->m_shaderProgram.useProgram();

		int uColorLocation = glGetUniformLocation(this->m_shaderProgram.getId(), "uColor");
		glUniform4f(uColorLocation, 1.0f, 0.5f, 0.2f, 1.0f);

		glBindVertexArray(this->m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	void Triangle::drawSingleColorVarying()
	{
		float timeValue = (float)glfwGetTime();
		float greenValue = sin(timeValue) / 2.0f + 0.5f;

		this->m_shaderProgram.useProgram();

		int uColorLocation = glGetUniformLocation(this->m_shaderProgram.getId(), "uColor");
		glUniform4f(uColorLocation, 0.0f, greenValue, 0.0f, 1.0f);

		glBindVertexArray(this->m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}

	void Triangle::drawColorPerVertex()
	{
		this->m_shaderProgram.useProgram();

		glBindVertexArray(this->m_VAO);
		glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(0);
	}
}