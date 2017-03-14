#include "OpenGLIndexBuffer.h"

RedSt4R::API::OpenGLIndexBuffer::OpenGLIndexBuffer(int size, uint32_t* indexData)
	:indexBufferSize(size), indexBufferData(indexBufferData)
{
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indexData, GL_STATIC_DRAW);
}

RedSt4R::API::OpenGLIndexBuffer::~OpenGLIndexBuffer()
{

}
