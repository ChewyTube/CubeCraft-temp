#include "CubeCraft.h"

namespace cubecraft {
	Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
	float lastX = SCR_WIDTH		/ 2.0f;
	float lastY = SCR_HEIGHT	/ 2.0f;
	bool firstMouse = true;
	// 帧率相关
	GLuint frame = 0, deltaFrame = 0;
	GLfloat start, end, first, second;
	
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
		if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
			speed = 32.0f;
		}
		else
		{
			speed = 4.0f;
		}

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

		// 放置方块
		for (float x = 0; x < 64; x+=1) {
			for (float z = 0; z < 64; z+=1) {
				auto h = noise.getNoise(x/16, z/16)*16+10;
				if (h < 0) {
					continue;
				}
				world.setBlock({ (int)x, (int)h, (int)z }, Block(Grass));
				for (int y = 0; y < h; y++) {
					world.setBlock({ (int)x, (int)y, (int)z }, Block(Dirt));
				}
			}
		}
		// 构建Mesh
		world.buildWorldMesh();

		auto textureIndices = world.getMesh().getTex_Indices();
		auto vertices = world.getMesh().getVertices();
		auto verticesIndices = world.getMesh().getVer_Indices();

 		TextureVBO  = m_context.buildVBO(textureIndices.data(), textureIndices.size()*sizeof(GLfloat));
		VerticesVBO = m_context.buildVBO(vertices.data(), vertices.size()*sizeof(GLfloat));

		VAO = m_context.buildVAO(VerticesVBO, TextureVBO);
		EBO = m_context.buildEBO(verticesIndices.data(), verticesIndices.size()*sizeof(GLuint), VAO);

		shader = m_context.buildShader("Shader/shader.vert", "Shader/shader.frag");

     	texture = LoadTexture("Resources/Texture/texture.png");
	}
	void CubeCraft::Loop() {
		start = static_cast<float>(glfwGetTime());
		first = static_cast<float>(glfwGetTime());
		while (!glfwWindowShouldClose(window)){
			frame++; deltaFrame++;
			float currentFrame = static_cast<float>(glfwGetTime());
			deltaTime = currentFrame - lastFrame;
			lastFrame = currentFrame;

			if (frame % 512 == 0) {
				second = static_cast<float>(glfwGetTime());
				std::cout << "FPS:" << (float)deltaFrame / (second - first) << std::endl;
				deltaFrame = 0;
				first = second;
			}

			processInput(window);

			renderer.startRender();

			// 为方便调试
			//renderer.render(shader, camera, VAO);
			glBindTexture(GL_TEXTURE_2D, texture);
			shader->use();

			glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, near, far);
			shader->setMat4("projection", projection);
			glm::mat4 view = camera.GetViewMatrix();
			shader->setMat4("view", view);

			auto points = world.getMesh().getVertices().size();
			glm::mat4 model = glm::mat4(1.0f);
			shader->setMat4("model", model);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, points, GL_UNSIGNED_INT, 0);

			// -------------------------------------------
			renderer.endRender(window);
		}
		end = static_cast<float>(glfwGetTime());
	}
	void CubeCraft::Quit() const {
		std::cout << "Average FPS:" << frame / (end - start) << std::endl;

		glDeleteVertexArrays(1, &VAO);
		glDeleteBuffers(1, &VerticesVBO);
		glDeleteBuffers(1, &TextureVBO);
		glDeleteBuffers(1, &EBO);

		glfwTerminate();
	}
}