#pragma once
#include "../RSIncludeOpenGL.h"
#include "../../Config/RenderingConfig.h"
#include "../../Debug/DebugMacros.h"
#include "../../Core/Vertex/VertexTypes.h"

namespace RedSt4R
{
	namespace API
	{
		class RSVertexBuffer
		{
		public:
			static RSVertexBuffer* CreateVertexBuffer(int size, VertexBase* vertexData);
		};
	}
}