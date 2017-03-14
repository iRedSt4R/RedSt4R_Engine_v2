#include "OpenGLGraphicsPipeline.h"

RedSt4R::API::OpenGLGraphicsPipeline::OpenGLGraphicsPipeline(RSVertexBuffer* rsVB, RSVertexShader* rsVS, RSPixelShader* rsPS)
{
	vertexBuffer = (OpenGLVertexBuffer*)rsVB;
	vertexShader = (OpenGLVertexShader*)rsVS;
	pixelShader = (OpenGLPixelShader*)rsPS;


	shaderProgram = glCreateProgram();
	//glBindFragDataLocation(shaderProgram, 0, "color");
	glAttachShader(shaderProgram, vertexShader->GetVertexShaderCompiled());
	glAttachShader(shaderProgram, pixelShader->GetPixelShaderCompiled());
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		RS_ERROR("Failed Linking GLSL Shader\n" << infoLog);
	}

}

RedSt4R::API::OpenGLGraphicsPipeline::~OpenGLGraphicsPipeline()
{

}

void RedSt4R::API::OpenGLGraphicsPipeline::SetVertexBuffer(RSVertexBuffer* rsVB)
{
	
}

void RedSt4R::API::OpenGLGraphicsPipeline::SetVertexShader(RSVertexShader* rsVS)
{
	
}

void RedSt4R::API::OpenGLGraphicsPipeline::SetPixelShader(RSPixelShader* rsPS)
{
	
}

void RedSt4R::API::OpenGLGraphicsPipeline::Execute()
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetVertexBuffer());
	glVertexAttribPointer(0, 3,GL_FLOAT, GL_FALSE, sizeof(VertexBase), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexBase), (GLvoid*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);
	glUseProgram(shaderProgram);
	glDrawArrays(GL_TRIANGLES, 0, 3);
}