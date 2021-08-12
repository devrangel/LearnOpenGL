#pragma once

#include "GLEW/glew.h"

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

class Shader
{
public:
	Shader();
	Shader(const char* vertexShaderCode, const char* fragmentShaderCode);

	GLuint getId() const;
	void useProgram() const;

	void setBool(const GLchar* name, GLboolean value) const;
	void setInt(const GLchar* name, GLint value) const;
	void setFloat(const GLchar* name, GLfloat value) const;

private:
	GLuint m_Id;

	GLuint compileShader(GLenum shaderType, const GLchar* const* shaderSourceCode) const;
	GLuint createProgram(GLuint vertexShader, GLuint fragmentShader) const;
};