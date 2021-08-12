#include "rectangle_texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

static const char* vertexShaderCode = R"(#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 aColor;
layout(location = 2) in vec2 aTexCoord;

out vec3 outColor;
out vec2 outTexCoord;

void main()
{
	gl_Position = vec4(aPos, 1.0f);
	outColor = aColor;
	outTexCoord = aTexCoord;
}
)";

static const char* fragmentShaderCode = R"(#version 330 core
in vec3 outColor;
in vec2 outTexCoord;

out vec4 FragColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

void main()
{
	FragColor = mix(texture(uTexture0, outTexCoord), texture(uTexture1, outTexCoord), 0.5);
}
)";

namespace Geometry
{
	RectangleTexture::RectangleTexture(const char* path0, const char* path1)
	{
		float vertices[] = {
			// Position			// colors		  // Texture Coords
			 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, // top right
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, // bottom right
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // bottom left
			-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f  // top left
		};

		unsigned int indices[] = {
			0, 1, 3, // first triangle
			1, 2, 3  // second triangle
		};

		this->m_VAO;
		glGenVertexArrays(1, &this->m_VAO);
		glBindVertexArray(this->m_VAO);

		// Vertices
		this->m_VBO;
		glGenBuffers(1, &m_VBO);
		glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		// Positions
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);

		// Colors
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(1);

		// Texture Coords
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glEnableVertexAttribArray(2);

		// Indices
		this->m_IBO;
		glGenBuffers(1, &m_IBO);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		glBindVertexArray(0);

		// Create shader program
		this->m_shaderProgram = Shader(vertexShaderCode, fragmentShaderCode);
		
		// Texture0
		GLuint texture0;
		glGenTextures(1, &texture0);
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		int width;
		int height;
		int nrChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(path0, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		// Texture1
		GLuint texture1;
		glGenTextures(1, &texture1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		data = stbi_load(path1, &width, &height, &nrChannels, 0);

		if (data)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}
		else
		{
			std::cout << "Failed to load texture" << std::endl;
		}
		stbi_image_free(data);

		this->m_shaderProgram.useProgram();
		this->m_shaderProgram.setInt("uTexture0", 0);
		this->m_shaderProgram.setInt("uTexture1", 1);
		glUseProgram(0);
	}

	void RectangleTexture::draw()
	{
		this->m_shaderProgram.useProgram();

		glBindVertexArray(this->m_VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);
	}
}