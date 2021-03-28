#pragma once

#include "Core/Defines.h"
#include "Renderer.h"

#include "Mesh.h"
#include "Material.h"

#if SPARROW_GL
namespace Sparrow
{
	namespace Rendering
	{
		class GLRenderer : public Renderer
		{
		public:
			GLRenderer(int32_t width, int32_t height, const char* windowName);
			~GLRenderer();

			void Update() override;

		private:
			void OnWindowResized(int32_t width, int32_t height);

		private:
			std::shared_ptr<Material> m_Material;
			std::shared_ptr<Mesh> m_Mesh;
		};
	}
}
#endif //SPARROW_GL