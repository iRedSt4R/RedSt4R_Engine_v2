#pragma once

#include "../RSIncludeOpenGL.h"
#include "../Interfaces/RSPixelShader.h"
#include "../../Config/RenderingConfig.h"
#include "../../Debug/DebugMacros.h"
#include <string>
#include <fstream>

namespace RedSt4R
{
	namespace API
	{
		class OpenGLPixelShader : public RSPixelShader
		{
		public:
			GLuint pixelShaderCompiled;

			//For Shader Compiling Result
			GLint success;
			GLchar infoLog[512];

		public:
			OpenGLPixelShader(char* shaderPath);
			~OpenGLPixelShader();

			char* ReadTextFromFile(char* filePath);
			
			__forceinline GLuint GetPixelShaderCompiled() { return pixelShaderCompiled; }
		};
	}
}
