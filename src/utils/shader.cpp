#include "shader.h"

Shader::Shader()
{

}

Shader::Shader(const char* vertexShaderCode, const char* fragmentShaderCode)
{
	GLuint vertexShader = compileShader(GL_VERTEX_SHADER, &vertexShaderCode);
	GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, &fragmentShaderCode);

	this->m_Id = createProgram(vertexShader, fragmentShader);
}

GLuint Shader::getId() const
{
	return this->m_Id;
}

void Shader::useProgram() const
{
	glUseProgram(this->m_Id);
}

void Shader::setBool(const GLchar* name, GLboolean value) const
{
	glUniform1i(glGetUniformLocation(this->m_Id, name), (GLint)value);
}	

void Shader::setInt(const GLchar* name, GLint value) const
{
	glUniform1i(glGetUniformLocation(this->m_Id, name), value);
}

void Shader::setFloat(const GLchar* name, GLfloat value) const
{
	glUniform1f(glGetUniformLocation(this->m_Id, name), value);
}

GLuint Shader::compileShader(GLenum shaderType, const GLchar* const* shaderSourceCode) const
{
	GLuint shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, shaderSourceCode, nullptr);
	glCompileShader(shader);

	GLint success;
	GLchar infoLog[512];

	if (shaderType == GL_VERTEX_SHADER)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}
	}
	else if (shaderType == GL_FRAGMENT_SHADER)
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 512, nullptr, infoLog);
			std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
			return -1;
		}
	}

	return shader;
}

GLuint Shader::createProgram(GLuint vertexShader, GLuint fragmentShader) const
{
	GLuint program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	GLint success;
	GLchar infoLog[512];

	glGetProgramiv(program, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(program, 512, nullptr, infoLog);
		std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}