#ifndef VERTEX_BUFFER_OBJ_H
#define VERTEX_BUFFER_OBJ_H

#include "OpenGLEnv.h"

namespace GFX {

class BufferObj
{
public:
	enum class Target {
		ARRAY_BUFFER = GL_ARRAY_BUFFER,
		ELEMENT_ARRAY_BUFFER = GL_ELEMENT_ARRAY_BUFFER,
	};
	BufferObj(Target target = Target::ARRAY_BUFFER)
		: target_(static_cast<GLenum>(target))
	{
		glGenBuffers(1, &buffer_);
	}
	BufferObj(const BufferObj&) = delete;
	BufferObj& operator=(const BufferObj&) = delete;
	void BufferData(GLsizeiptr size, const void* data, GLenum usage) const;
	unsigned int GetBufferObj() const { return buffer_; }
private:
	unsigned int buffer_ = 0;
	GLenum target_ = 0;
};

} // GFX

#endif // !VERTEX_BUFFER_OBJ_H



