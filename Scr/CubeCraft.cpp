#include "CubeCraft.h"

namespace cubecraft {
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH / 2.0f;
	float lastY = SCR_HEIGHT / 2.0f;
	bool firstMouse = true;
	
	// timing
	float deltaTime = 0.0f;	// time between current frame and last frame
	float lastFrame = 0.0f;

	void framebuffer_size_callback(GLFWwindow* window, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
	void mouse_callback(GLFWwindow* window, double xposIn, double yposIn)
	{
		float xpos = static_cast<float>(xposIn);
		float ypos = static_cast<float>(yposIn);

		if (firstMouse)
		{
			lastX = xpos;
			lastY = ypos;
			firstMouse = false;
		}

		float xoffset = xpos - lastX;
		float yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

		lastX = xpos;
		lastY = ypos;

		camera.ProcessMouseMovement(xoffset, yoffset);
	}
	void processInput(GLFWwindow* window)
	{
		float speed = 4.0f;

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

	void CubeCraft::Init() {
		window = m_context.initOpenGL();

		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);

		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
		glfwSetCursorPosCallback(window, mouse_callback);

		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

		for (int x = 0; x < 16; x++) {
			for (int y = 0; y < 16; y++) {
				for (int z = 0; z < 16; z++) {
					BlockCroodInChunk c(x, y, z);
					chunk.setBlock(c, 1);
				}
			}
		}
		chunk.buildMesh();
		auto textureIndices = chunk.getMesh().getTex_Indices();
		auto vertices = chunk.getMesh().getVertices();
		auto verticesIndices = chunk.getMesh().getVer_Indices();

		TextureVBO = m_context.buildVBO(textureIndices.data(), textureIndices.size()*sizeof(GLuint));
		VerticesVBO = m_context.buildVBO(vertices.data(), vertices.size()*sizeof(GLfloat));

		VAO = m_context.buildVAO(VerticesVBO, TextureVBO);
		EBO = m_context.buildEBO(verticesIndices.data(), verticesIndices.size()*sizeof(GLuint), VAO);

		shader = m_context.buildShader("Shader/shader.vert", "Shader/shader.frag");

		texture = LoadTexture("Resources/Texture/dirt.png");
	}
	void CubeCraft::Loop() {
		while (!glfwWindowShouldClose(window)){
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			processInput(window);

			renderer.startRender();

			glBindTexture(GL_TEXTURE_2D, texture);

			// 为方便调试
			//renderer.render(shader, camera, VAO);
			shader->use();

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);
			shader->setMat4("projection", projection);
			glm::mat4 view = camera.GetViewMatrix();
			shader->setMat4("view", view);

			//auto& data = chunk.getBlockData();
			/*
			for (auto& block : data) {
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::translate(model, { block.first.x, block.first.y, block.first.z });
				shader->setMat4("model", model);
				glBindVertexArray(VAO);
				glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			}
			*/

			auto points = chunk.getMesh().getVertices().size();
			glm::mat4 model = glm::mat4(1.0f);
			shader->setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, points/2, GL_UNSIGNED_INT, 0);
			// -------------------------------------------
			renderer.endRender(window);
		}
	}
	void CubeCraft::Quit() const {
		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VBO);
		glDeleteBuffers(1, &EBO);

		glfwTerminate();
	}
}