#pragma once

#include "../RSIncludeOpenGL.h"
#include "../Interfaces/RSVertexBuffer.h"
#include "../../Config/RenderingConfig.h"

namespace RedSt4R
{
	namespace API
	{
		class OpenGLVertexBuffer : public RSVertexBuffer
		{

		public:
			OpenGLVertexBuffer(int size, glm::vec3* vertexData);
			~OpenGLVertexBuffer();


		};
	}
}
