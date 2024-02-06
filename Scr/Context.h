#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "Log/Log.h"
#include "Shader.h"
#include "Config.h"


namespace cubecraft {
	class Context {
	public:
		GLFWwindow* initOpenGL();
		Shader* buildShader(std::string vertPath, std::string fragPath);
		std::pair<int, int> buildVBO_VAO(float* vertices, int size);

		// @TODO ���뺯�����µ�ͷ�ļ�
		void initTexture();
		GLuint LoadTexture(std::string filePath);
		//int buildVAO();
	private:
	};
}