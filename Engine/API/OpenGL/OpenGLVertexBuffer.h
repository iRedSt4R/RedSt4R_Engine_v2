#pragma once

#include "../RSIncludeOpenGL.h"
#include "../Interfaces/RSVertexBuffer.h"
#include "../../Config/RenderingConfig.h"
#include "../../Core/Vertex/VertexTypes.h"

namespace RedSt4R
{
	namespace API
	{
		class OpenGLVertexBuffer : public RSVertexBuffer
		{
		public:
			GLuint vertexBuffer;

			VertexBase* vertexBufferData;
			int vertexBufferSize;

		public:
			OpenGLVertexBuffer(int size, VertexBase* vertexData);
			~OpenGLVertexBuffer();

			__forceinline GLuint GetVertexBuffer() { return vertexBuffer; }
		};
	}
}
