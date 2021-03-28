#pragma once
#include <cstdint>
#include <memory>

#include "Core/Defines.h"
#include "Material.h"

namespace Sparrow
{
	namespace Rendering
	{
		class Mesh
		{
		public:
			Mesh(std::shared_ptr<Material> material);
			~Mesh();

			void Render();
		private:
			std::shared_ptr<Material> m_Material;
#if SPARROW_GL
			uint32_t m_VertexBufferObject;
			uint32_t m_VertexArrayObject;
			uint32_t m_ElementBufferObject;
#endif //SPARROW_GL
		};
	}
}