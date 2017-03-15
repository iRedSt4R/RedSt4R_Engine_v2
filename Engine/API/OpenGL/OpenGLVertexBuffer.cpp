#include "OpenGLVertexBuffer.h"

RedSt4R::API::OpenGLVertexBuffer::OpenGLVertexBuffer(int size, Vertex* pVertexData)
	:vertexBufferData(pVertexData), vertexBufferSize(size)
{
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, size, pVertexData, GL_STATIC_DRAW);
}

RedSt4R::API::OpenGLVertexBuffer::~OpenGLVertexBuffer()
{

}
