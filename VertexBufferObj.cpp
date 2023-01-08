#include "VertexBufferObj.h"

void GFX::BufferObj::BufferData(GLsizeiptr size, const void* data, GLenum usage) const
{
	glBindBuffer(target_, buffer_);
	glBufferData(target_, size, data, usage);
}
