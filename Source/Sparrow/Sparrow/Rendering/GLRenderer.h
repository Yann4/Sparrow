#pragma once

#include "Core/Defines.h"
#include "Renderer.h"

#if SPARROW_GL
namespace Sparrow
{
	namespace Rendering
	{
		class GLRenderer : public Renderer
		{
		public:
			GLRenderer(int32_t width, int32_t height, const char* windowName);
			void Update() override;

		private:
			void OnWindowResized(int32_t width, int32_t height);
		};
	}
}
#endif //SPARROW_GL