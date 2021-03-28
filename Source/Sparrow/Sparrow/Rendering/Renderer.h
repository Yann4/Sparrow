#pragma once

#include "Window.h"
#include <memory>

namespace Sparrow
{
	namespace Rendering
	{
		class Renderer
		{
		public:
			Renderer(int32_t width, int32_t height, const char* windowName);

			bool IsReady() const { return m_Initialised; }

			virtual void Update() = 0;

			std::shared_ptr<Window> GetWindow() const { return m_Window; }
		protected:
			std::shared_ptr<Window> m_Window;

			bool m_Initialised = false;
		};
	}
}