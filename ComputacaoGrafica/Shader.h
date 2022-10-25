#include <GL/glew.h>
#include <iostream>
#include <fstream>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();
	void CreateFromString(const char* vertexCode, const char* fragmentCode);
	void CreateFromFile(const char* vertexLocation, const char* fragmnetLocation);
	void UseProgram();
	GLuint GetUniformModel() { return uniformModel; };
	GLuint GetUniformProjection() { return uniformProjection; };
	GLuint GetUniformView() { return uniformView; };


private:
	GLuint shaderId;
	GLuint uniformModel, uniformProjection, uniformView;
	void Compile(const char* vertexCode, const char* fragmentCode);
	std::string ReadFile(const char* fileLocation);
};

