#pragma once

#include "Context.h"

namespace cubecraft {
	class CubeCraft {
	public:
		void Init();
		void Loop();
		void Quit();
	private:
		Context m_context;
		GLFWwindow* window;
		Shader* shader;
		GLuint VAO, VBO;

		float vertices[18] = {
		-0.5f, -0.5f, 0.0f,
		 0.5f, -0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		 -0.5f, -0.5f, 0.0f,
		 -0.5f, 0.5f, 0.0f,
		 0.5f,  0.5f, 0.0f,
		};
	};
}
