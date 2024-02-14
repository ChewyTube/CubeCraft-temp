#pragma once

#include "Context.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Renderer/Renderer.h"

#include "World/World.h"
#include "World/Chunk/Chunk.h"
#include "Enum/BlockType.h"

#include "World/Generator/Terrain/TerrainGenerator.h"

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

		TerrainGenerator generator = TerrainGenerator(4.0f, 0.02f, 4.0f, 2.0f, 4, &world);
		//PerlinNoise noise;

	};
}
