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

		GLuint buildVBO(GLfloat* data, GLint size);
		GLuint buildVAO(GLuint VerticesVBO, GLuint TextureVBO);
		GLuint buildEBO(GLuint* indices, GLint size, GLuint VAO);
	private:
	};
}