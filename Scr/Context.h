#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

#include "Log/Log.h"
#include "Shader.h"

namespace cubecraft {
	class Context {
	public:
		GLFWwindow* initOpenGL();
		Shader* buildShader(std::string vertPath, std::string fragPath);
		std::pair<int, int> buildVBO_VAO(float* vertices, int size);
		//int buildVAO();
	private:
		const unsigned int SCR_WIDTH = 800;
		const unsigned int SCR_HEIGHT = 600;
	};
}