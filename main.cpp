#include <cmath>
#include <vector>
#include <chrono>
#include <iostream>
#include "gfx_log.h"
#include "OpenGLEnv.h"
#include "Window.h"
#include "Shader.h"

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

const unsigned int g_strLen = 512;

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
		-0.37f, 0.07f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -0.49f, -0.21f, 0.0f, 0.0f, 1.0f, 0.0f,
		 -0.23f,  -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
	};
	unsigned int vbo1, vao1;
	// ![img](https://learnopengl.com/img/getting-started/vertex_array_objects.png)
	// prepare a vertex array object
	glGenVertexArrays(1, &vao1);
	// prepare a vertex buffer object
	glGenBuffers(1, &vbo1);
	// 1. bind Vertex Array Object
	glBindVertexArray(vao1);
	// 2. copy our vertices array in a buffer for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, vbo1);
	glBufferData(GL_ARRAY_BUFFER,
		triangle.size() * sizeof(triangle[0]), triangle.data(), GL_STATIC_DRAW);
	// 3. then set our vertex attributes pointers
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, // The first argument is the index of vertex attribute in vertex shader
		GL_FLOAT, GL_FALSE, 6 * sizeof(float), static_cast<void*>(0));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));
	// 4. ubind vao1
	glBindVertexArray(0);

	std::string vertexShaderPath = "D:\\code\\C++\\Graphics\\Window\\glsl\\vertex.glsl";
	std::string fragmentShaderPath = "D:\\code\\C++\\Graphics\\Window\\glsl\\fragment.glsl";
	Shader shader(vertexShaderPath.c_str(), fragmentShaderPath.c_str());

	auto start = std::chrono::system_clock::now();
	while (!window.WindowShouldClose())
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> diff = end - start;
		window.ProcessInput();
		glClearColor(0.314f + 0.2f * sin(diff.count()), 0.15f, 0.92f, 0.65f);
		glClear(GL_COLOR_BUFFER_BIT);

		shader.use();
		// draw triangle
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, triangle.size());

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	return 0;
}