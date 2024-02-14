#pragma once

#include <cmath>
#include <random>
#include <vector>
#include <numeric>

#include <glad/glad.h>

namespace cubecraft {
    // 声明一个二维柏林噪声类
    class PerlinNoise {
    public:
        // 构造函数，根据seed初始化置换数组
        PerlinNoise(GLint64 seed) {
            // 设置随机数种子
            rng.seed(seed);
            // 生成0到255的随机排列
            std::vector<int> permutation(256);
            std::iota(permutation.begin(), permutation.end(), 0);
            std::shuffle(permutation.begin(), permutation.end(), rng);
            // 复制到置换数组中，使其长度为512
            for (int i = 0; i < 256; i++) {
                p[i] = p[i + 256] = permutation[i];
            }
        }
        // 计算二维柏林噪声值，输入为二维坐标
        double noise(double x, double y) {
            // 计算单元格的整数坐标
            int X = (int)std::floor(x) & 255;
            int Y = (int)std::floor(y) & 255;
            // 计算单元格内的小数坐标
            x -= std::floor(x);
            y -= std::floor(y);
            // 计算平滑函数的值
            double u = smooth(x);
            double v = smooth(y);
            // 计算梯度函数的哈希值
            int A = p[X] + Y;
            int B = p[X + 1] + Y;
            // 计算梯度函数的值
            double g00 = grad(p[A], x, y);
            double g10 = grad(p[B], x - 1, y);
            double g01 = grad(p[A + 1], x, y - 1);
            double g11 = grad(p[B + 1], x - 1, y - 1);
            // 计算插值函数的值
            double gx0 = lerp(g00, g10, u);
            double gx1 = lerp(g01, g11, u);
            double gxy = lerp(gx0, gx1, v);
            // 返回噪声值，范围为-1到1
            return gxy;
        }
    private:
        // 定义一个随机数生成器
        std::mt19937 rng;
        // 定义一个插值函数
        double lerp(double a, double b, double t) {
            return a + t * (b - a);
        }
        // 定义一个平滑函数
        double smooth(double t) {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }
        // 定义一个梯度函数
        double grad(int hash, double x, double y) {
            // 根据hash值选择一个向量
            int h = hash & 3;
            double u = h < 2 ? x : y;
            double v = h == 0 || h == 3 ? y : x;
            // 根据最高位决定正负
            return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
        }
        // 定义一个置换数组
        int p[512];
    };

}