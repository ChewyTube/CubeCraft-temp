#pragma once

#include <cmath>
#include <random>
#include <vector>

#include <glad/glad.h>

namespace cubecraft {
    // 定义一个柏林噪声类
    class PerlinNoise {
    public:
        // 构造函数，初始化梯度向量和置换数组
        PerlinNoise();
        
        GLdouble getNoise(GLdouble x, GLdouble y) {
            return noise(x, y);
        }
    private:
        std::vector<std::pair<double, double>> grads; // 梯度向量数组
        std::vector<int> perm; // 置换数组
        // 生成一个随机的梯度向量的函数
        std::pair<double, double> random_grad() {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(-1.0, 1.0);
            double x = dis(gen);
            double y = dis(gen);
            double len = std::sqrt(x * x + y * y);
            return std::make_pair(x / len, y / len);
        }

        // 生成一个随机的置换数组的函数
        std::vector<int> random_perm() {
            std::vector<int> perm(256);
            for (int i = 0; i < 256; i++) {
                perm[i] = i;
            }
            std::random_device rd;
            std::mt19937 gen(rd());
            std::shuffle(perm.begin(), perm.end(), gen);
            return perm;
        }

        // 计算点积
        double dot(double x1, double y1, double x2, double y2) {
            return x1 * x2 + y1 * y2;
        }
        // 计算插值
        double lerp(double a, double b, double t) {
            return a + t * (b - a);
        }
        // 计算平滑函数
        double smooth(double t) {
            return t * t * t * (t * (t * 6 - 15) + 10);
        }
        // 计算柏林噪声值
        double noise(double x, double y) {
            // 计算网格单元坐标
            int x0 = (int)std::floor(x);
            int y0 = (int)std::floor(y);
            int x1 = x0 + 1;
            int y1 = y0 + 1;

            // 计算网格单元内的相对坐标
            double xr = x - x0;
            double yr = y - y0;

            // 通过置换数组找到对应的梯度向量
            int aa = perm[(perm[x0 & 255] + y0) & 255];
            int ab = perm[(perm[x0 & 255] + y1) & 255];
            int ba = perm[(perm[x1 & 255] + y0) & 255];
            int bb = perm[(perm[x1 & 255] + y1) & 255];
            auto gaa = grads[aa];
            auto gab = grads[ab];
            auto gba = grads[ba];
            auto gbb = grads[bb];

            // 计算点积
            double u = dot(xr, yr, gaa.first, gaa.second);
            double v = dot(xr - 1, yr, gba.first, gba.second);
            double w = dot(xr, yr - 1, gab.first, gab.second);
            double s = dot(xr - 1, yr - 1, gbb.first, gbb.second);

            // 计算插值
            double sx = smooth(xr);
            double sy = smooth(yr);
            double a = lerp(u, v, sx);
            double b = lerp(w, s, sx);
            double h = lerp(a, b, sy);

            // 返回噪声值，范围为[-1, 1]
            return h;
        }
    };
    
    
}