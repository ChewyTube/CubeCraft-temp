#pragma once

#include "Context.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture/Texture.h"
//#include "Renderer/Renderer.h"

namespace cubecraft {
	class CubeCraft {
	public:
		void Init();
		void Loop();
		void Quit();
		CubeCraft* Instance() {
			return this;
		}
	private:
		Context m_context;
		GLFWwindow* window;
		Shader* shader;
		GLuint VAO, VBO, EBO, texture;
		GLuint VerticesVBO, TextureVBO;

		float vertices[30] = {
			1.0f, 1.0f, 0.0f,     1.0f, 1.0f, // top right
			1.0f, 0.0f, 0.0f,     1.0f, 0.0f, // bottom right
			0.0f, 0.0f, 0.0f,     0.0f, 0.0f, // bottom left
			0.0f, 1.0f, 0.0f,     0.0f, 1.0f, // top left
			1.0f, 1.0f, 0.0f,     1.0f, 1.0f, // top right
			0.0f, 0.0f, 0.0f,     0.0f, 0.0f, // bottom left
		};
		GLuint indices[6]{
			0, 1, 3,
			1, 2, 3,
		};
		GLfloat frontFace[12]{
			0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 
		};
		GLfloat backFace[12]{
			1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,
		};
		GLfloat leftFace[12]{
			0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
		};
		GLfloat rightFace[12]{
			1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,
		};
		GLfloat topFace[12]{
			0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
		};
		GLfloat bottomFace[12]{
			0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1,
		};
		GLfloat textureIndices[8] = {
			0, 0, 1, 0, 1, 1, 0, 1,
		};
	};
}
