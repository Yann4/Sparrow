#include "Mesh.h"

#if SPARROW_GL
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#endif //SPARROW_GL

namespace Sparrow
{
	namespace Rendering
	{
		Mesh::Mesh(std::shared_ptr<Material> material) :
			m_Material(material)
		{
			float vertices[] = {
				 0.5f,  0.5f, 0.0f,  // top right
				 0.5f, -0.5f, 0.0f,  // bottom right
				-0.5f, -0.5f, 0.0f,  // bottom left
				-0.5f,  0.5f, 0.0f   // top left 
			};

			unsigned int indices[] = {  // note that we start from 0!
				0, 1, 3,   // first triangle
				1, 2, 3    // second triangle
			};

#if SPARROW_GL
			glGenVertexArrays(1, &m_VertexArrayObject);

			glGenBuffers(1, &m_VertexBufferObject);
			glGenBuffers(1, &m_ElementBufferObject);

			glBindVertexArray(m_VertexArrayObject);

			glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferObject);
			glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferObject);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
			glEnableVertexAttribArray(0);

			glBindVertexArray(0);
#endif //SPARROW_GL
		}

		Mesh::~Mesh()
		{
#if SPARROW_GL
			glDeleteVertexArrays(1, &m_VertexArrayObject);
			glDeleteBuffers(1, &m_VertexBufferObject);
			glDeleteBuffers(1, &m_ElementBufferObject);
#endif //SPARROW_GL
		}

		void Mesh::Render()
		{
#if SPARROW_GL
			glUseProgram(m_Material->GetShaderProgram());
			glBindVertexArray(m_VertexArrayObject);
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBufferObject);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
#endif //SPARROW_GL
		}
	}
}