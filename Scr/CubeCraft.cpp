#include "CubeCraft.h"

void processInput(GLFWwindow* window, cubecraft::CubeCraft* instance)
{
	auto& camera = *instance->getCamera();
	auto deltaTime = 0.01;
	auto speed = 5;

	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
	
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		camera.ProcessKeyboard(FORWARD, deltaTime * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		camera.ProcessKeyboard(BACKWARD, deltaTime * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		camera.ProcessKeyboard(LEFT, deltaTime * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		camera.ProcessKeyboard(RIGHT, deltaTime * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		camera.ProcessKeyboard(DOWN, deltaTime * speed);
	}
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
		camera.ProcessKeyboard(UP, deltaTime * speed);
	}
}

namespace cubecraft {
	void CubeCraft::Init() {
		window = m_context.initOpenGL();
		auto result = m_context.buildVBO_VAO(vertices, sizeof(vertices));
		VBO = result.first;
		VAO = result.second;
		shader = m_context.buildShader("Shader/shader.vert", "Shader/shader.frag");

		//m_context.initTexture();
		texture = m_context.LoadTexture("Resources/Texture/dirt.png");
		auto m_camera = Camera(glm::vec3(0.0f, 0.0f, 3.0f));
		camera = &m_camera;
	}
	void CubeCraft::Loop() {
		while (!glfwWindowShouldClose(window)){
			processInput(window, this);

			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			glBindTexture(GL_TEXTURE_2D, texture);

			shader->use();

			glm::mat4 projection = glm::perspective(glm::radians(camera->Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
			shader->setMat4("projection", projection);
			glm::mat4 view = camera->GetViewMatrix();
			shader->setMat4("view", view);
			glm::mat4 model = glm::mat4(1.0f);
			shader->setMat4("model", model);

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