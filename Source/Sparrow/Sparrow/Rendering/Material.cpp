#include "Material.h"

#include <iostream>
#include <exception>

namespace Sparrow
{
	namespace Rendering
	{
		Material::Material()
		{
			const char* vertexShaderSource = "#version 330 core\n"
				"layout (location = 0) in vec3 aPos;\n"
				"void main()\n"
				"{\n"
				"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
				"}\0";

			const char* fragmentShaderSource = "#version 330 core\n"
				"out vec4 FragColor;\n"
				"void main()\n"
				"{\n"
				"	FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
				"}\0";

#if SPARROW_GL
			uint32_t vertexShader;
			if (!CompileShader(GL_VERTEX_SHADER, vertexShaderSource, vertexShader))
			{
				throw std::exception("Failed vertex shader compilation");
			}
			
			uint32_t fragmentShader;
			if (!CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSource, fragmentShader))
			{
				throw std::exception("Failed fragment shader compilation");
			}

			m_ShaderProgram = glCreateProgram();
			glAttachShader(m_ShaderProgram, vertexShader);
			glAttachShader(m_ShaderProgram, fragmentShader);

			glLinkProgram(m_ShaderProgram);

			int success;
			char log[512];
			glGetProgramiv(m_ShaderProgram, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(m_ShaderProgram, 512, NULL, log);
				std::cout << "Shader Program linking failed with error:\n" << log << std::endl;
				throw std::exception("Shader program linking failed");
			}

			glDeleteShader(vertexShader);
			glDeleteShader(fragmentShader);
#endif //SPARROW_GL
		}

#if SPARROW_GL
		bool Material::CompileShader(GLenum shaderType, const char* shaderSource, uint32_t& shader) const
		{
			shader = glCreateShader(shaderType);
			glShaderSource(shader, 1, &shaderSource, NULL);
			glCompileShader(shader);

			int success;
			char log[512];
			glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
			if (!success)
			{
				glGetShaderInfoLog(shader, 512, NULL, log);
				std::cout << "Vertex shader compilation failed with error:\n" << log << std::endl;
				return false;
			}

			return true;
		}
#endif //SPARROW_GL
	}
}