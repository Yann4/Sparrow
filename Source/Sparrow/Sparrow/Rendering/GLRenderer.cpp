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

			m_Material = std::make_shared<Material>();
			m_Mesh = std::make_shared<Mesh>(m_Material);

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
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			m_Mesh->Render();

			glfwSwapBuffers(m_Window->GetHandle());
			glfwPollEvents();
		}
	}
}
#endif //SPARROW_GL