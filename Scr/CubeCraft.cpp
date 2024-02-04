#include "CubeCraft.h"

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

namespace cubecraft {
	void CubeCraft::Init() {
		window = m_context.initOpenGL();
		auto result = m_context.buildVBO_VAO(vertices, sizeof(vertices));
		VBO = result.first;
		VAO = result.second;
		shader = m_context.buildShader("Shader/shader.vert", "Shader/shader.frag");
	}
	void CubeCraft::Loop() {
		while (!glfwWindowShouldClose(window)){
			processInput(window);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			shader->use();
			glBindVertexArray(VAO);
			glDrawArrays(GL_TRIANGLES, 0, 6);
			glfwSwapBuffers(window);
			glfwPollEvents();
		}
	}
	void CubeCraft::Quit() {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);

		glfwTerminate();
	}
}