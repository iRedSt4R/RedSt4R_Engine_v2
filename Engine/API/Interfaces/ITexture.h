#pragma once

namespace RedSt4R
{
	namespace API
	{
		class Texture
		{
		public:
			virtual void Bind(int bindFlag) = 0;

			static Texture* CreateTexture(float width, float hight, int textureType, int flags);
		};
	}
}