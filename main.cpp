#include <cmath>
#include <vector>
#include <chrono>
#include <iostream>
#include "gfx_log.h"
#include "OpenGLEnv.h"
#include "Window.h"
#include "Shader.h"
#include "VertexArraryObj.h"

// TODO: add class VertexArrayObj
// TODO: add class VertexBufferObj

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
	OpenGLEnv& env = OpenGLEnv::GetInstance();
	env.Init();

	Window window;
	window.Init(800, 800, "OpenGL");
	window.InitGlad();
	window.SetFramebufferSizeCallback(CALLBACK::framebuffer_size_callback);

	std::vector<float> quardrangle = {
		-0.37f, 0.07f, 0.0f, 1.0f, 0.0f, 0.0f,
		 -0.49f, -0.21f, 0.0f, 0.0f, 1.0f, 0.0f,
		 -0.23f,  -0.2f, 0.0f, 0.0f, 0.0f, 1.0f,
		 0.11f, 0.37f, 0.0f, 0.5f, 0.8f, 0.6f,
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,
	};
	
	VertexArraryObj vao;
	vao.Use();
	vao.BufferData(VertexArraryObj::Type::VBO, quardrangle.size() * sizeof(quardrangle[0]), quardrangle.data(), GL_STATIC_DRAW);
	vao.BufferData(VertexArraryObj::Type::EBO, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);
	vao.VertexAttribPointer(0, 3,
		GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(0));
	vao.VertexAttribPointer(1, 3,
		GL_FLOAT, GL_FALSE, 6 * sizeof(float), reinterpret_cast<void*>(3 * sizeof(float)));

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
		// draw quardrangle
		vao.Use();
		// for vertex array
		// glDrawArrays(GL_TRIANGLES, 0, quardrangle.size());
		// for vertex index array
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	return 0;
}