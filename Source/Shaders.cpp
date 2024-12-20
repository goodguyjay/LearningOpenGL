#include "pch.hpp"
#include "Shaders.hpp"
#include <iostream>
#include <fstream>
#include <sstream>

using std::string;

string LoadShaderSource(const string& filepath)
{
	const std::ifstream shaderFile(filepath);

	if (!shaderFile.is_open())
	{
		std::cerr << "failed to open shader file: " << filepath << "\n";
		return "";
	}

	std::stringstream buffer;
	buffer << shaderFile.rdbuf();
	return buffer.str();
}

unsigned int CompileShader(const unsigned int shaderType, const string& shaderSource)
{
	const char* source = shaderSource.c_str();
	const unsigned int shader = glCreateShader(shaderType);

	glShaderSource(shader, 1, &source, nullptr);
	glCompileShader(shader);

	int success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetShaderInfoLog(shader, 512, nullptr, infoLog);
		std::cout << "shader compilation failed: " << infoLog << "\n";
	}

	return shader;
}

unsigned int CreateShaderProgram(const unsigned int vertexShader, const unsigned int fragmentShader)
{
	const unsigned int shaderProgram = glCreateProgram();

	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	int success;
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

	if (!success)
	{
		char infoLog[512];
		glGetProgramInfoLog(shaderProgram, 512, nullptr, infoLog);
		std::cout << "program linking failed: " << infoLog << "\n";
	}

	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

