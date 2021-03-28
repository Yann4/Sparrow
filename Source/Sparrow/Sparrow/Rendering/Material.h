#pragma once
#include "Core/Defines.h"

#include <cstdint>

#if SPARROW_GL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif //SPARROW_GL

namespace Sparrow
{
	namespace Rendering
	{
		class Material
		{
		public:
			Material();

#if SPARROW_GL
			uint32_t GetShaderProgram() const { return m_ShaderProgram; }
		private:
			bool CompileShader(GLenum shaderType, const char* shaderSource, uint32_t& shader) const;
		private:
			uint32_t m_ShaderProgram;
#endif //SPARROW_GL
		};
	}
}