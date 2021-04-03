#pragma once
#include "Defines.h"
#include "Core/Utilities/Callback.h"

#if SPARROW_GL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif //SPARROW_GL

namespace Sparrow
{
	namespace Rendering
	{
		class Window
		{
		public:
			Window(int32_t width, int32_t height, const char* name);

			bool ShouldClose();

			int32_t GetWidth() const { return m_Width; }
			int32_t GetHeight() const { return m_Height; }

#if SPARROW_GL
			GLFWwindow* GetHandle() const { return m_Handle; }
#endif //SPARROW_GL

		private:
#if SPARROW_GL
			static void OnGLWindowResize(GLFWwindow* window, int32_t width, int32_t height);
#endif //SPARROW_GL

		public:
			static Callback<void, int32_t /*width*/, int32_t /*height*/> OnWindowResized;
		private:
			int32_t m_Width;
			int32_t m_Height;

#if SPARROW_GL
			GLFWwindow* m_Handle;
#endif //SPARROW_GL
		};
	}
}