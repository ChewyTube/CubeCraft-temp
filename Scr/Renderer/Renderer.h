#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../Shader.h"
#include "../Camera.h"

#include "../Config.h"

namespace cubecraft {
    class Renderer {
    public:
        void startRender();
        void endRender(GLFWwindow* window);

        void render(Shader* shader, Camera camera, GLuint VAO);
    private:

    };
    
}