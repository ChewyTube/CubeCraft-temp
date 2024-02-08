#include "Renderer.h"

namespace cubecraft {
	void Renderer::startRender() {
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}
	void Renderer::endRender(GLFWwindow* window) {
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	void Renderer::render(Shader* shader, Camera camera, GLuint VAO) {
		shader->use();

		glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);
		shader->setMat4("projection", projection);
		glm::mat4 view = camera.GetViewMatrix();
		shader->setMat4("view", view);

		for (int x = 0; x < 16; x += 1) {
			glm::mat4 model = glm::mat4(1.0f);
			model = glm::translate(model, { x, 0, 0 });
			shader->setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		}
	}
}