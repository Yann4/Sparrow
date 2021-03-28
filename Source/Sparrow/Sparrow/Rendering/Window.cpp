#include "Window.h"

namespace Sparrow
{
	namespace Rendering
	{
		Callback<void, int32_t /*width*/, int32_t /*height*/> Window::OnWindowResized;

		Window::Window(int32_t width, int32_t height, const char* name) :
			m_Width(width), m_Height(height)
		{
#if SPARROW_GL
			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, SPARROW_GL_MAJOR);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, SPARROW_GL_MINOR);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			m_Handle = glfwCreateWindow(m_Width, m_Height, name, nullptr, nullptr);
			if (m_Handle == nullptr)
			{
				throw std::exception("Failed to create GLFW window");
			}

			glfwSetFramebufferSizeCallback(m_Handle, &Window::OnGLWindowResize);
#endif //SPARROW_GL
		}

		bool Window::ShouldClose()
		{
#if SPARROW_GL
			return glfwWindowShouldClose(m_Handle);
#else
			return true;
#endif
		}

#if SPARROW_GL
		void Window::OnGLWindowResize(GLFWwindow* window, int32_t width, int32_t height)
		{
			OnWindowResized.Invoke(width, height);
		}
#endif //SPARROW_GL
	}
}