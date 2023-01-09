#ifndef OPENGLENV_H
#define OPENGLENV_H
#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace GFX {

class OpenGLEnv
{
public:
	OpenGLEnv(const OpenGLEnv&) = delete;
	OpenGLEnv& operator=(const OpenGLEnv&) = delete;
	~OpenGLEnv() = default;
	static OpenGLEnv& GetInstance();
	void Init()
	{
		InitGlfw();
	}
private:
	OpenGLEnv() = default;
	void InitGlfw();
};

}

#endif // !OPENGLENV_H


