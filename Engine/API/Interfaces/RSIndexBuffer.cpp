#include "RSIndexBuffer.h"
#include "../OpenGL/OpenGLIndexBuffer.h"

namespace RedSt4R
{
	namespace API
	{

		RSIndexBuffer* RSIndexBuffer::CreateIndexBuffer(int size, uint32_t* indexData)
		{
			if (USE_OPENGL) return new OpenGLIndexBuffer(size, indexData);
		}

	}
}