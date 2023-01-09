#include "gfx_log.h"
#include "OpenGLEnv.h"

namespace GFX {

OpenGLEnv& OpenGLEnv::GetInstance()
{
	static OpenGLEnv env;
	return env;
}

void OpenGLEnv::InitGlfw()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

}

