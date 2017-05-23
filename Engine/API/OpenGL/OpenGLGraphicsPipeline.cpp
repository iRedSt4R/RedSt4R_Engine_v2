#include "OpenGLGraphicsPipeline.h"

RedSt4R::API::OpenGLGraphicsPipeline::OpenGLGraphicsPipeline(RSVertexBuffer* rsVB, RSVertexShader* rsVS, RSPixelShader* rsPS, RSIndexBuffer* rsIB)
{
	vertexBuffer = (OpenGLVertexBuffer*)rsVB;
	vertexShader = (OpenGLVertexShader*)rsVS;
	pixelShader = (OpenGLPixelShader*)rsPS;
	indexBuffer = (OpenGLIndexBuffer*)rsIB;



	shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader->GetVertexShaderCompiled());
	glAttachShader(shaderProgram, pixelShader->GetPixelShaderCompiled());
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		RS_ERROR("Failed Linking GLSL Shader\n" << infoLog);
	}

	glGenVertexArrays(1, &vertexArray);

	glBindVertexArray(vertexArray);
		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer->GetVertexBuffer());
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer->GetIndexBuffer());

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)(sizeof(glm::vec3)));
		glEnableVertexAttribArray(1);
	glBindVertexArray(0);
}

RedSt4R::API::OpenGLGraphicsPipeline::~OpenGLGraphicsPipeline()
{

}

