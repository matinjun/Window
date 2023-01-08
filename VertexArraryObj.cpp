#include "VertexArraryObj.h"

void GFX::VertexArraryObj::BufferData(Type type, GLsizeiptr size, const void* data, GLenum usage) const
{
	switch (type)
	{
	case GFX::VertexArraryObj::Type::VBO:
		vbo_.BufferData(size, data, usage);
		break;
	case GFX::VertexArraryObj::Type::EBO:
		ebo_.BufferData(size, data, usage);
		break;
	default:
		break;
	}
}

void GFX::VertexArraryObj::VertexAttribPointer(GLuint index, GLint size, GLenum type, GLboolean normalized, GLsizei stride, const void* pointer) const
{
	glEnableVertexAttribArray(index);
	glVertexAttribPointer(index, size, type, normalized, stride, pointer);
}
