#pragma once

#include <array>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace cubecraft {
    // from https://github.com/Hopson97/MineCraft-One-Week-Challenge.git

    GLfloat frontFace[20]{
        0, 0, 1, 0, 0,
        1, 0, 1, 1, 0,
        1, 1, 1, 1, 1, 
        0, 1, 1, 0, 1,
    };
    GLfloat backFace[12]{
        1, 0, 0, 
        0, 0, 0, 
        0, 1, 0, 
        1, 1, 0,
    };
    GLfloat leftFace[12]{
        0, 0, 0, 
        0, 0, 1, 
        0, 1, 1, 
        0, 1, 0,
    };
    GLfloat rightFace[12]{
        1, 0, 1, 
        1, 0, 0, 
        1, 1, 0, 
        1, 1, 1,
    };

    GLfloat topFace[12]{
        0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 0,
    };

    GLfloat bottomFace[12]{
        0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1,
    };

    GLfloat indices[6] {
        0, 1, 3,
        1, 2, 3,
    };
}