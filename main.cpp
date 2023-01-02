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

const char* g_fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"\n"
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = ourColor;\n"
	"}\n";

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
		-0.37f, 0.07f, 0.0f,
		 -0.49f, -0.21f, 0.0f,
		 -0.23f,  -0.2f, 0.0f,
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
	glVertexAttribPointer(0, 3,
		GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);
	// 4. ubind vao1
	glBindVertexArray(0);

	std::vector<float> pentagon = {
		-0.08f, 0.18f, 0.0f,
		0.12f, -0.15f, 0.0f,
		0.35f, 0.05f, 0.0f,
		0.22f, 0.25f, 0.0f,
		0.07f, 0.33f, 0.0f,
	};
	std::vector<unsigned int> indices = {
		0, 1, 2,
		0, 2, 3,
		0, 3, 4,
	};
	unsigned int vbo2, vao2, ebo2;
	// prepare objects
	glGenVertexArrays(1, &vao2);
	glGenBuffers(1, &vbo2);
	glGenBuffers(1, &ebo2);
	// 1. bind vao
	glBindVertexArray(vao2);
	// 2. copy data to vbo
	glBindBuffer(GL_ARRAY_BUFFER, vbo2);
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(float) * pentagon.size(), pentagon.data(), GL_STATIC_DRAW);
	// 3. copy data to ebo
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo2);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		sizeof(indices[0]) * indices.size(), indices.data(), GL_STATIC_DRAW);
	// 4.
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,
		3, GL_FLOAT, false, 3 * sizeof(float), 0);
	glBindVertexArray(0);


	// compile shader
	// 1. compile vertex shader
	int success = 0;
	char infoLog[CONST::g_strLen];
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER); // prepare a shader object
	glShaderSource(vertexShader, 1, &CONST::g_vertexShaderSource, nullptr);
	glCompileShader(vertexShader);
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n"
			<< infoLog << std::endl;
		return 1;
	}
	// 2. compile fragment shader
	unsigned int fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &CONST::g_fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n"
			<< infoLog << std::endl;
		return 1;
	}
	// 3. link shaders above
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, sizeof(infoLog), nullptr, infoLog);
		std::cerr << "ERROR::SHADER::LINK::COMPILATION_FAILED\n"
			<< infoLog << std::endl;
		return 1;
	}
	// 4. use shader and release source
	glUseProgram(shaderProgram);
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);


	auto start = std::chrono::system_clock::now();
	while (!window.WindowShouldClose())
	{
		auto end = std::chrono::system_clock::now();
		std::chrono::duration<float> diff = end - start;
		window.ProcessInput();
		glClearColor(0.314f, 0.15f, 0.92f, 0.65f);
		glClear(GL_COLOR_BUFFER_BIT);

		glUseProgram(shaderProgram);
		int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
		glUniform4f(vertexColorLocation, 0.271f, 0.428f + 0.3f * sin(diff.count()), 0.82f + 0.045f * cos(diff.count()), 0.90f);
		// draw triangle
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		glBindVertexArray(vao1);
		glDrawArrays(GL_TRIANGLES, 0, triangle.size());
		// draw pentagon
		glUseProgram(shaderProgram);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		glUseProgram(shaderProgram);
		glBindVertexArray(vao2);
		glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, nullptr);

		glfwSwapBuffers(window.GetWindow());
		glfwPollEvents();
	}

	return 0;
}