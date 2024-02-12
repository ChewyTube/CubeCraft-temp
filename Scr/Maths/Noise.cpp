#include "Noise.h"

namespace cubecraft {
	PerlinNoise::PerlinNoise() {
        for (int i = 0; i < 256; i++) {
            grads.push_back(random_grad());
        }
        perm = random_perm();
    }
}