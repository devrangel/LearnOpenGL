#include "rectangle.h"

static const char* vertexShaderCode = R"(#version 330 core
layout(location = 0) in vec3 aPos;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
}
)";

static const char* fragmentShaderCode = R"(#version 330 core
out vec4 FragColor;

void main()
{
	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
}
)";

namespace Geometry
{
	Rectangle::Rectangle(bool wireframeMode)
	{
		float vertices[] = {
			 0.5f,  0.5f, 0.0f, // top right
			 0.5f, -0.5f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f  // top left

		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
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

		this->m_IBO;
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		if(wireframeMode)
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

		glBindVertexArray(0);

		this->m_shaderProgram = Shader(vertexShaderCode, fragmentShaderCode);
	}

	void Rectangle::draw(const Camera& camera)
	{
		this->m_shaderProgram.useProgram();

		glBindVertexArray(this->m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}