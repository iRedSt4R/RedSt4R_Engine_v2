#pragma once
#include "../RSIncludeOpenGL.h"
#include "../Interfaces/RSGraphicsPipeline.h"
#include "../RS_API.h"
#include "../../Config/RenderingConfig.h"
#include "OpenGLVertexBuffer.h"
#include "OpenGLVertexShader.h"
#include "OpenGLPixelShader.h"

namespace RedSt4R
{
	namespace API
	{
		class OpenGLGraphicsPipeline : public RSGraphicsPipeline
		{
		public:
			OpenGLVertexBuffer* vertexBuffer;
			OpenGLVertexShader* vertexShader;
			OpenGLPixelShader* pixelShader;

			GLuint shaderProgram;
			//For Shader Linking Result
			GLint success;
			GLchar infoLog[512];

			GLuint vertexArray;

		public:
			virtual void SetVertexBuffer(RSVertexBuffer* rsVB) override;
			virtual void SetVertexShader(RSVertexShader* rsVS) override;
			virtual void SetPixelShader(RSPixelShader* rsPS) override;
			virtual void Execute() override;


		public:
			OpenGLGraphicsPipeline(RSVertexBuffer* rsVB, RSVertexShader* rsVS, RSPixelShader* rsPS);
			~OpenGLGraphicsPipeline();
		};
	}
}

