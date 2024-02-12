#pragma once

#include "Context.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture/Texture.h"
#include "Renderer/Renderer.h"

#include "World/Chunk/Chunk.h"
#include "World/World.h"

#include "Maths/Noise.h"

namespace cubecraft {
	class CubeCraft {
	public:
		void Init();
		void Loop();
		void Quit() const;
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
		World world;

		PerlinNoise noise;
	};
}
