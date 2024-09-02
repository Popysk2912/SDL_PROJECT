#pragma once
#include "errors.h"

#include <string>
#include <vector>
#include <fstream>
#include <GL/glew.h>

class GLSLProgram
{
public:
	GLSLProgram();
	~GLSLProgram();
	void compileShaders(const std::string& vShaderPath, const std::string& fShaderPath);

	void linkShaders();

	void bindAttribute(const std::string& attributeName);

	GLint getUniformLocation(const std::string& name);

	void use();
	void unuse();
private:
	void compileShader(const std::string& filePath, GLuint& id);
	GLuint _numAttribs;
	GLuint _programID;
	GLuint _vShaderID;
	GLuint _fShaderID;
};

