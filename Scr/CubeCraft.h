#pragma once

#include "Context.h"
#include "Camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace cubecraft {
	class CubeCraft {
	public:
		void Init();
		void Loop();
		void Quit();
		CubeCraft* Instance() {
			return this;
		}
		Camera* getCamera() {
			return camera;
		}
	private:
		Context m_context;
		GLFWwindow* window;
		Shader* shader;
		Camera* camera;
		GLuint VAO, VBO, texture;

		float vertices[30] = {
		 0.5f, 0.5f, 0.0f,     1.0f, 1.0f, // top right
		 0.5f,-0.5f, 0.0f,     1.0f, 0.0f, // bottom right
		-0.5f,-0.5f, 0.0f,     0.0f, 0.0f, // bottom left
		-0.5f, 0.5f, 0.0f,     0.0f, 1.0f, // top left
		 0.5f, 0.5f, 0.0f,     1.0f, 1.0f, // top right
		-0.5f,-0.5f, 0.0f,     0.0f, 0.0f, // bottom left
		};
	};
}
