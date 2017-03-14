#pragma once

#include "../RSIncludeOpenGL.h"
#include "../Interfaces/RSIndexBuffer.h"
#include "../../Config/RenderingConfig.h"
#include "../../Core/Vertex/VertexTypes.h"

namespace RedSt4R
{
	namespace API
	{
		class OpenGLIndexBuffer : public RSIndexBuffer
		{
		public:
			GLuint indexBuffer;

			uint32_t* indexBufferData;
			int indexBufferSize;

		public:
			OpenGLIndexBuffer(int size, uint32_t* indexData);
			~OpenGLIndexBuffer();

			__forceinline GLuint GetIndexBuffer() { return indexBuffer; }
		};
	}
}