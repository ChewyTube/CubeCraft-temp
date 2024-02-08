#pragma once

#include "Context.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture/Texture.h"
#include "Renderer/Renderer.h"

#include "World/Chunk/Chunk.h"

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
		Renderer renderer;
		GLuint VAO, VBO, EBO, texture;
		GLuint VerticesVBO, TextureVBO;
		Chunk chunk;

		// from https://github.com/Hopson97/MineCraft-One-Week-Challenge.git
		float _vertices[30] = {
			1.0f, 1.0f, 0.0f,     1.0f, 1.0f, // top right
			1.0f, 0.0f, 0.0f,     1.0f, 0.0f, // bottom right
			0.0f, 0.0f, 0.0f,     0.0f, 0.0f, // bottom left
			0.0f, 1.0f, 0.0f,     0.0f, 1.0f, // top left
			1.0f, 1.0f, 0.0f,     1.0f, 1.0f, // top right
			0.0f, 0.0f, 0.0f,     0.0f, 0.0f, // bottom left
		};
		GLuint _indices[6]{
			0, 1, 3,
			1, 2, 3,
		};
		GLfloat _frontFace[12]{
			0, 0, 1, 1, 0, 1, 1, 1, 1, 0, 1, 1, 
		};
		GLfloat _backFace[12]{
			1, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 0,
		};
		GLfloat _leftFace[12]{
			0, 0, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0,
		};
		GLfloat _rightFace[12]{
			1, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1,
		};
		GLfloat _topFace[12]{
			0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
		};
		GLfloat _bottomFace[12]{
			0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1,
		};
		GLfloat _textureIndices[8] = {
			0, 0, 1, 0, 1, 1, 0, 1,
		};
	};
}
