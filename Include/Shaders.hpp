#pragma once

#include <string>

using std::string;

string LoadShaderSource(const string& filepath);
unsigned int CompileShader(unsigned int shaderType, const string& shaderSource);
unsigned int CreateShaderProgram(unsigned int vertexShader, unsigned int fragmentShader);