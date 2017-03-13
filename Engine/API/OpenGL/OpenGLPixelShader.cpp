#include "OpenGLPixelShader.h"

RedSt4R::API::OpenGLPixelShader::OpenGLPixelShader(char* shaderPath)
{
	std::string shaderSourceString = ReadTextFromFile(shaderPath);
	const char* shaderSource = shaderSourceString.c_str();

	pixelShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(pixelShader, 1, &shaderSource, NULL);
	glCompileShader(pixelShader);

	glGetShaderiv(pixelShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(pixelShader, 512, NULL, infoLog);
		RS_ERROR("Failed Compiling GLSL Vertex Shader\n" << infoLog);
	}
}

RedSt4R::API::OpenGLPixelShader::~OpenGLPixelShader()
{

}

char* RedSt4R::API::OpenGLPixelShader::ReadTextFromFile(char* filePath)
{
	FILE* fp = fopen(filePath, "r");
	fseek(fp, 0, SEEK_END);
	long fileLenght = ftell(fp);
	fseek(fp, 0, SEEK_SET);
	char* contents = new char[fileLenght + 1];
	for (int i = 0; i < fileLenght; i++)
	{
		contents[i] = 0;
	}
	fread(contents, 1, fileLenght, fp);
	contents[fileLenght + 1] = '\0';
	fclose(fp);

	RS_WARNING(contents);
	return contents;
}
