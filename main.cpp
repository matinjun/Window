#include <cmath>
#include <vector>
#include <chrono>
#include <iostream>
#include "gfx_log.h"
#include "OpenGLEnv.h"
#include "Window.h"

namespace GFX {

// 回调事件集合
namespace CALLBACK {

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

}

// 常量
namespace CONST{

const char* g_vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

}

}

int main(int argc, char** argv) {
	using namespace GFX;
	OpenGLEnv& env = OpenGLEnv::Create();
	env.Init();

	Window window;
	window.Init(800, 800, "OpenGL");
	window.InitGlad();
	window.SetFramebufferSizeCallback(CALLBACK::framebuffer_size_callback);

	std::vector<float> triangle = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.0f,  0.5f, 0.0f,
	};
	unsigned int vbo;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER,
		triangle.size() * sizeof(triangle[0]), triangle.data(), GL_STATIC_DRAW);

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);

	auto start = std::chrono::system_clock::now();
	while (!window.WindowShouldClose())
	{
		window.ProcessInput();
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> diff = end - start;
		glClearColor(0.5f + 0.4f * cos(0.9f * diff.count() + 0.5f),
			0.3f + 0.2f * sin(diff.count()),
			0.3f,
			.5f + 0.2f * sin(0.5f * diff.count() + 0.9f));
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	return 0;
}