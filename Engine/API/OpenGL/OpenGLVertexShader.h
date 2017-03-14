#pragma once

#include "../RSIncludeOpenGL.h"
#include "../Interfaces/RSVertexShader.h"
#include "../../Config/RenderingConfig.h"
#include "../../Debug/DebugMacros.h"
#include <string>
#include <fstream>

namespace RedSt4R
{
	namespace API
	{
		class OpenGLVertexShader : public RSVertexShader
		{
		public:
			GLuint vertexShaderCompiled;

			//For Shader Compiling Result
			GLint success;
			GLchar infoLog[512];

		public:
			OpenGLVertexShader(char* shaderPath);
			~OpenGLVertexShader();

			std::string ReadTextFromFile(char* filePath);

			__forceinline GLuint GetVertexShaderCompiled() { return vertexShaderCompiled; }
		};
	}
}
