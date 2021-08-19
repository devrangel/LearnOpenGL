#include "cube.h"

#include "stb/stb_image.h"

static const char* vertexShaderCode = R"(#version 330 core
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 uModel;
uniform mat4 uView;
uniform mat4 uProjection;

out vec3 outColor;
out vec2 outTexCoord;

void main()
{
	gl_Position = uProjection * uView * uModel * vec4(aPos, 1.0f);
	outTexCoord = aTexCoord;
}
)";

static const char* fragmentShaderCode = R"(#version 330 core
in vec2 outTexCoord;

out vec4 FragColor;

uniform sampler2D uTexture0;
uniform sampler2D uTexture1;

void main()
{
	FragColor = mix(texture(uTexture0, outTexCoord), texture(uTexture1, outTexCoord), 0.5);
}
)";

Cube::Cube(const char* path0, const char* path1)
	: m_CameraPos(glm::vec3(0.0f, 0.0f, 3.0f)), m_CameraFront(glm::vec3(0.0f, 0.0f, -1.0f)), m_CameraUp(glm::vec3(0.0f, 1.0f, 0.0f))
{
	float vertices[] = {
		// Position			  // Texture
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
		 0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		 0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
		-0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
		-0.5f,  0.5f, -0.5f,  0.0f, 1.0f
	};

	this->m_CubePositions.at(0) = glm::vec3(0.0f, 0.0f, 0.0f);
	this->m_CubePositions.at(1) = glm::vec3(2.0f, 5.0f, -15.0f);
	this->m_CubePositions.at(2) = glm::vec3(-1.5f, -2.2f, -2.5f);
	this->m_CubePositions.at(3) = glm::vec3(-3.8f, -2.0f, -12.3f);
	this->m_CubePositions.at(4) = glm::vec3(2.4f, -0.4f, -3.5f);
	this->m_CubePositions.at(5) = glm::vec3(-1.7f, 3.0f, -7.5f);
	this->m_CubePositions.at(6) = glm::vec3(1.3f, -2.0f, -2.5f);
	this->m_CubePositions.at(7) = glm::vec3(1.5f, 2.0f, -2.5f);
	this->m_CubePositions.at(8) = glm::vec3(1.5f, 0.2f, -1.5f);
	this->m_CubePositions.at(9) = glm::vec3(-1.3f, 1.0f, -1.5f);

	this->m_VAO;
	glGenVertexArrays(1, &this->m_VAO);
	glBindVertexArray(this->m_VAO);

	// Vertices
	this->m_VBO;
	glGenBuffers(1, &m_VBO);
	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Texture Coords
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

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

	// Projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
	GLuint projectionLocation = glGetUniformLocation(this->m_shaderProgram.getId(), "uProjection");
	glUniformMatrix4fv(projectionLocation, 1, GL_FALSE, glm::value_ptr(projection));

	glUseProgram(0);

	glEnable(GL_DEPTH_TEST);
}

void Cube::draw(const Camera& camera)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	this->m_shaderProgram.useProgram();

	// Camera(view) matrix
	glm::mat4 view = camera.getViewMatrix();
	GLuint viewLocation = glGetUniformLocation(this->m_shaderProgram.getId(), "uView");
	glUniformMatrix4fv(viewLocation, 1, GL_FALSE, glm::value_ptr(view));

	glBindVertexArray(this->m_VAO);
	for (int i = 0; i < 10; i++)
	{
		// Model matrix
		glm::mat4 model = glm::mat4(1.0f);
		model = glm::translate(model, this->m_CubePositions.at(i));
		float angle = (float)glfwGetTime() * 20.0f * i;
		model = glm::rotate(model, glm::radians(angle), glm::vec3(1.0f, 0.3f, 0.5f));
		GLuint modelLocation = glGetUniformLocation(this->m_shaderProgram.getId(), "uModel");
		glUniformMatrix4fv(modelLocation, 1, GL_FALSE, glm::value_ptr(model));

		glDrawArrays(GL_TRIANGLES, 0, 36);
	}

	glBindVertexArray(0);
}