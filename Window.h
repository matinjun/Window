#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include "OpenGLEnv.h"

namespace GFX {

class Window
{
public:
	Window() = default;
	Window(const Window&) = delete;
	~Window()
	{
		Deinit();
	}
	Window& operator=(const Window&) = delete;
	GLFWwindow* GetWindow() const { return window_; }
	int GetWidth() const { return width_; }
	int GetHeight() const { return height_; }
	const std::string& GetTitle() const { return title_; }
	void ProcessInput() const;
	void Init(const int width, const int height, const std::string &title);
	void InitGlad() const;
	void Deinit();
	void SetFramebufferSizeCallback(GLFWframebuffersizefun func);
	bool WindowShouldClose() const;

private:
	GLFWwindow* window_ = nullptr;
	int width_ = 800;
	int height_ = 600;
	std::string title_ = "OpenGL";
};

}


#endif // !WINDOW_H


