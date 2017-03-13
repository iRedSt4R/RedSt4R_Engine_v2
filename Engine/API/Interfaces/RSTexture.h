#pragma once

namespace RedSt4R
{
	namespace API
	{
		class RSTexture
		{
		public:
			virtual void Bind(int bindFlag) = 0;

			static RSTexture* CreateTexture(float width, float hight, int textureType, int flags);
		};
	}
}