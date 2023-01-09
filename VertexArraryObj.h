#ifndef VERTEX_ARRAY_OBJ_H
#define VERTEX_ARRAY_OBJ_H

#include "OpenGLEnv.h"
#include "BufferObj.h"

namespace GFX {

class VertexArraryObj
{
public:
	enum class Type
	{
		VBO,
		EBO,
	};
	VertexArraryObj() : vbo_(BufferObj::Target::ARRAY_BUFFER),
		ebo_(BufferObj::Target::ELEMENT_ARRAY_BUFFER)
	{
		glGenVertexArrays(1, &vao_);
	}
	void Use() const { glBindVertexArray(vao_); }
	void BufferData(Type type,
		GLsizeiptr size, const void* data, GLenum usage) const;
	void VertexAttribPointer(GLuint index,// The first argument is the index of vertex attribute in vertex shader
		GLint size, GLenum type, GLboolean normalized,
		GLsizei stride, const void* pointer) const;
	unsigned int GetVAO() const { return vao_; }
	unsigned int GetVBO() const { return vbo_.GetBufferObj(); }
	unsigned int GetEBO() const { return ebo_.GetBufferObj(); }
private:
	// ![img](https://learnopengl.com/img/getting-started/vertex_array_objects.png)
	unsigned int vao_ = 0;
	BufferObj vbo_;
	BufferObj ebo_;
};

} // GFX


#endif // !VERTEX_ARRAY_OBJ_H


