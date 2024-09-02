#include "glslProgram.h"

GLSLProgram::GLSLProgram() : _programID(0), _vShaderID(0), _fShaderID(0), _numAttribs(0)
{

}

GLSLProgram::~GLSLProgram()
{
}

void GLSLProgram::compileShaders(const std::string& vShaderPath, const std::string& fShaderPath)
{
	_vShaderID = glCreateShader(GL_VERTEX_SHADER);
	if (!_vShaderID)
		fatalError("VERTEX_SHADER::FAILED_TO_CREATE");

	_fShaderID = glCreateShader(GL_FRAGMENT_SHADER);
	if (!_fShaderID)
		fatalError("FRAGMENT_SHADER::FAILED_TO_CREATE");

	compileShader(vShaderPath, _vShaderID);
	compileShader(fShaderPath, _fShaderID);
}

void GLSLProgram::linkShaders()
{

	_programID = glCreateProgram();

	glAttachShader(_programID, _vShaderID);
	glAttachShader(_programID, _fShaderID);

	glLinkProgram(_programID);

	GLint isLinked = 0;
	glGetProgramiv(_programID, GL_LINK_STATUS, (int*) & isLinked);
	if(isLinked == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(_programID, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<GLchar> infoLog(maxLength);
		glGetProgramInfoLog(_programID, maxLength, &maxLength, &infoLog[0]);

		glDeleteProgram(_programID);
		glDeleteShader(_vShaderID);
		glDeleteShader(_fShaderID);
		

		std::printf("%s\n", &infoLog[0]);
		fatalError("Shader failed to link");
	}

	glDetachShader(_programID, _vShaderID);
	glDetachShader(_programID, _fShaderID);
	glDeleteShader(_vShaderID);
	glDeleteShader(_fShaderID);
}
void GLSLProgram::bindAttribute(const std::string& attributeName)
{
	glBindAttribLocation(_programID, _numAttribs++, attributeName.c_str());
}

GLint GLSLProgram::getUniformLocation(const std::string& name)
{
	GLuint location =  glGetUniformLocation(_programID, name.c_str());
	if (location == GL_INVALID_INDEX)
		fatalError("Invalid Uniform Name: " + name);
	return location;
}

void GLSLProgram::use()
{
	glUseProgram(_programID);
	for(int i = 0; i < _numAttribs; i++)
	{
		glEnableVertexAttribArray(i);
	}
}

void GLSLProgram::unuse()
{
	glUseProgram(0);
	for (int i = 0; i < _numAttribs; i++)
	{
		glDisableVertexAttribArray(i);
	}
}

void GLSLProgram::compileShader(const std::string& filePath, GLuint& id)
{
	std::ifstream vertexFile(filePath);
	if (vertexFile.fail())
	{
		perror(filePath.c_str());
		fatalError("FRAGMENT_SHADER::FAILED_TO_OPEN_FILE: " + filePath);
	}

	std::string fileContents;
	std::string line;

	while (std::getline(vertexFile, line))
	{
		fileContents += line + "\n";
	}
	vertexFile.close();
	const char* contentsPtr = fileContents.c_str();
	glShaderSource(id, 1, &contentsPtr, nullptr);

	glCompileShader(id);

	GLint status = 0;
	glGetShaderiv(id, GL_COMPILE_STATUS, &status);

	if (status == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &maxLength);

		std::vector<char> errorLog(maxLength);
		glGetShaderInfoLog(id, maxLength, &maxLength, &errorLog[0]);

		glDeleteShader(id);

		std::printf("%s\n", &errorLog[0]);
		fatalError("Shader " + filePath + " failed to compile");

		return;
	}
}
