#pragma once
#include "../../Core/Vertex/VertexTypes.h"
#include "RSDevice.h"

/*enum class EVertexType
{
	P, PC, PT, PTN
};
*/

namespace RedSt4R
{
	namespace API
	{
		class RSVertexBuffer
		{
		public:
			//static RSVertexBuffer* CreateVertexBuffer(int size, Vertex* vertexData);
			static RSVertexBuffer* CreateVertexBuffer(RSDevice* pDevice, VertexColor* vertexData);
		};
	}
}