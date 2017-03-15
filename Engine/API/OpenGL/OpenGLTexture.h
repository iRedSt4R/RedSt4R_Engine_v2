#pragma once
#include "../Interfaces/RSTexture.h"
#include <soil.h>

namespace RedSt4R
{
	namespace API
	{
		class OpenGLTexture : public RSTexture
		{
		private:
			int textureWidth;
			int textureHeight;
			GLuint texture;
			unsigned char* soilTexture;

			
		public:
			OpenGLTexture(char* texturePath, bool bGenerateMipMaps);
			~OpenGLTexture();

			virtual void LoadTextureFromFile(char* texturePath) override;
			virtual void Bind(int bindPoint) override;
			virtual void GenerateMipMaps() override;
			virtual void ClearTexture() override;
			virtual void ClearTexture(glm::vec3 clearColor) override;

		};
	}
}
