﻿#include "Texture.h"

#include "../Log/Log.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../../stb_image.h"

namespace cubecraft {
    GLuint LoadTexture(std::string filePath) {
        //stbi_set_flip_vertically_on_load(true);

        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        // 为当前绑定的纹理对象设置环绕、过滤方式
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // 加载并生成纹理
        int width, height, nrChannels;
        unsigned char* data = stbi_load(filePath.c_str(), &width, &height, &nrChannels, 0);
        if (data)
        {
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            outputLog("Failed to load texture");
        }
        stbi_image_free(data);

        return texture;
    }
    // @ TODO 为这个函数找到一个更合适的头文件
    TexRelCrood getTexCrood(BlockType block, Direction dir) {
        switch (block)
        {
        case cubecraft::Dirt:
            return { 0, 0 };
            break;
        case cubecraft::Grass:
            switch (dir)
            {
            case cubecraft::up:
                return { 2, 0 };
                break;
            case cubecraft::down:
                return { 0, 0 };
                break;
            case cubecraft::left:
            case cubecraft::right:
            case cubecraft::front:
            case cubecraft::back:
                return { 1, 0 };
                break;
            default:
                return { 0, 0 };
                break;
            }
            break;
        case cubecraft::Log:
            switch (dir)
            {
            case cubecraft::up:
            case cubecraft::down:
                return { 0, 1 };
                break;
            case cubecraft::left:
            case cubecraft::right:
            case cubecraft::front:
            case cubecraft::back:
                return { 1, 1 };
                break;
            default:
                return { 0, 0 };
                break;
            }
        case cubecraft::Leave:
            return { 2, 1 };
        default:
            return { 0, 0 };
            break;
        }
    }
}