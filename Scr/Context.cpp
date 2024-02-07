#include "Context.h"

namespace cubecraft {
    GLFWwindow* Context::initOpenGL() {
        glfwInit();
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        //glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

        GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "CubeCraft", NULL, NULL);
        if (window == NULL)
        {
            outputLog("Failed to create GLFW window");
            glfwTerminate();
            return nullptr;
        }
        glfwMakeContextCurrent(window);

        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            outputLog("Failed to initialize GLAD");
            return nullptr;
        }

        glfwMakeContextCurrent(window);

        //glEnable(GL_DEPTH_TEST);

        return window;
	}

    Shader* Context::buildShader(std::string vertPath, std::string fragPath) {
        auto shader = new Shader(vertPath.c_str(), fragPath.c_str());
        return shader;
    }
    std::pair<int, int> Context::buildVBO_VAO(float* vertices, int size) {
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        
        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);

        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(sizeof(GLfloat)*3));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        glBindVertexArray(0);

        return { VBO, VAO };
    }
    GLuint Context::buildVBO(GLfloat* data, GLint size) {
        GLuint VBO;

        glGenBuffers(1, &VBO);
        glBindBuffer(GL_ARRAY_BUFFER, VBO);

        glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return VBO;
    }
    GLuint Context::buildVAO(GLuint VerticesVBO, GLuint TextureVBO) {
        // @TODO ���ƺ���
        // ����˵����
        // num: VBO�ĸ���
        // VBOs: һ���޷����������飬�洢ÿ��VBO��ID
        // attribs: һ���������飬�洢ÿ��VBO��Ӧ�Ķ������Ե�λ�ã�location��
        // components: һ���������飬�洢ÿ���������Եķ�������
        // stride: һ���������飬�洢ÿ���������ԵĲ������ֽ�Ϊ��λ��
        // offset: һ���������飬�洢ÿ���������Ե�ƫ�������ֽ�Ϊ��λ��

        GLuint VAO;

        glGenVertexArrays(1, &VAO);
        glBindVertexArray(VAO);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, VerticesVBO);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, TextureVBO);
        glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return VAO;
    }
    GLuint Context::buildEBO(GLuint* indices, GLint size, GLuint VAO) {
        GLuint EBO;

        glGenBuffers(1, &EBO);
        glBindVertexArray(VAO);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);

        glBindVertexArray(0);
        //glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return EBO;
    }
}