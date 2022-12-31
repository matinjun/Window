#include "Window.h"
#include "gfx_log.h"

namespace GFX {

void Window::ProcessInput() const
{
	GFX_CHK_RETURN_NOT_VALUE((window_ == nullptr), GFX_LOGE("window is nullptr"));
	if (glfwGetKey(window_, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
		glfwSetWindowShouldClose(window_, true);
	}
}

void Window::Init(const int width, const int height, const std::string& title)
{
	if (window_ != nullptr) {
		GFX_LOGE("a window has been created!");
		return;
	}
	width_ = width;
	height_ = height;
	title_ = title;
	window_ = glfwCreateWindow(width_, height_, title_.c_str(), nullptr, nullptr);
	if (nullptr == window_)
	{
		GFX_LOGE("Failed to create GLFW window");
		glfwTerminate();
	}
	glfwMakeContextCurrent(window_);
}

void Window::InitGlad() const
{
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		GFX_LOGE("Failed to initialize GLAD");
	}
}

void Window::Deinit()
{
	if (window_) {
		glfwDestroyWindow(window_);
		window_ = nullptr;
	}
}

void Window::SetFramebufferSizeCallback(GLFWframebuffersizefun func)
{
	GFX_CHK_RETURN_NOT_VALUE((nullptr == window_), GFX_LOGE("window_ is nullptr"));
	glfwSetFramebufferSizeCallback(window_, func);
}

bool Window::WindowShouldClose() const
{
	GFX_CHK_RETURN((nullptr == window_), true, GFX_LOGE("window_ is nullptr"));
	return glfwWindowShouldClose(window_);
}

} // GFX

