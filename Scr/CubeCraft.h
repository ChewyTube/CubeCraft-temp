#pragma once

#include "Context.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Renderer.h"

#include "World/World.h"
#include "World/Chunk/Chunk.h"
#include "Enum/BlockType.h"

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
		GLuint VAO, EBO, texture;
		GLuint VerticesVBO, TextureVBO;
		World world;

		PerlinNoise noise;
	};
}
