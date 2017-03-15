#include "OpenGLTexture.h"

RedSt4R::API::OpenGLTexture::OpenGLTexture(char* texturePath, bool bGenerateMipMaps)
{
	LoadTextureFromFile(texturePath);
}

RedSt4R::API::OpenGLTexture::~OpenGLTexture()
{

}

void RedSt4R::API::OpenGLTexture::LoadTextureFromFile(char* texturePath)
{
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	soilTexture = SOIL_load_image(texturePath, &textureWidth, &textureHeight, 0, SOIL_LOAD_RGB);
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, textureWidth, textureHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, soilTexture);
	glGenerateMipmap(GL_TEXTURE_2D);
	SOIL_free_image_data(soilTexture);
	glBindTexture(GL_TEXTURE_2D, 0);
}

void RedSt4R::API::OpenGLTexture::Bind(int bindPoint)
{
	glBindTexture(GL_TEXTURE_2D, texture);
}

void RedSt4R::API::OpenGLTexture::GenerateMipMaps()
{
	
}

void RedSt4R::API::OpenGLTexture::ClearTexture()
{
	
}

void RedSt4R::API::OpenGLTexture::ClearTexture(glm::vec3 clearColor)
{
	
}
