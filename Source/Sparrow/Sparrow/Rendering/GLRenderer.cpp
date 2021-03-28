#include "GLRenderer.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#if SPARROW_GL
namespace Sparrow
{
	namespace Rendering
	{
		GLRenderer::GLRenderer(int32_t width, int32_t height, const char* windowName) : 
			Renderer(width, height, windowName)
		{
			if (glfwInit() != GLFW_TRUE)
			{
				throw std::exception("Failed to init glfw");
			}

			m_Window = std::make_shared<Window>(width, height, windowName);
			glfwMakeContextCurrent(m_Window->GetHandle());

			if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
			{
				throw std::exception("Failed to initialise GLAD");
			}

			glViewport(0, 0, m_Window->GetWidth(), m_Window->GetHeight());
			Window::OnWindowResized += std::bind(&GLRenderer::OnWindowResized, this, std::placeholders::_1, std::placeholders::_2);
			m_Initialised = true;
		}

		GLRenderer::~GLRenderer()
		{
			glfwTerminate();
		}

		void GLRenderer::OnWindowResized(int32_t width, int32_t height)
		{
			std::cout << "Window resized to (" << width << ", " << height << ")\n";
			glViewport(0, 0, width, height);
		}

		void GLRenderer::Update()
		{
			glfwSwapBuffers(m_Window->GetHandle());
			glfwPollEvents();
		}
	}
}
#endif //SPARROW_GL