#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <functional>
#include <type_traits>

#include "glad/glad.h"

namespace cubecraft {
	struct Crood : glm::vec4
	{
		Crood() = default;
		template<typename T>
		Crood(T x, T y, T z, T w=0) {
			this->x = x;
			this->y = y;
			this->z = z;
			this->w = w;
		}
	};

	struct CroodHash {
		std::size_t operator()(const Crood& c) const {
			std::hash<decltype(c.x)> hasher;

			auto hash1 = hasher(c.x);
			auto hash2 = hasher(c.y);
			auto hash3 = hasher(c.z);
			auto hash4 = hasher(c.w);

			return std::hash<decltype(c.x)>{}(
				(hash1 ^ (hash2 >> hash3) ^ hash4) ^ (hash1 | hash4)
				);
		}
	};
	struct CroodEqual {
		bool operator()(const Crood& c1, const Crood& c2) const {
			return c1.x == c2.x && c1.y == c2.y && c1.z == c2.z && c1.w == c2.w;
		}
	};

	struct BlockCroodInWorld : Crood
	{
		// @TODO用构造函数转换可能更好
		using Crood::Crood;
		//BlockCroodInWorld(BlockCroodInChunk c1, ChunkCroodInWorld c2);
	};
	struct BlockCroodInChunk : Crood
	{
		using Crood::Crood;
		//BlockCroodInChunk(BlockCroodInWorld c);
	};
	struct ChunkCroodInWorld : Crood
	{
		using Crood::Crood;
		//ChunkCroodInWorld(BlockCroodInWorld c);
	};
	
	ChunkCroodInWorld getChunkCrood(BlockCroodInWorld c);
	BlockCroodInChunk getBlockChunkCrood(BlockCroodInWorld c);
	BlockCroodInWorld getBlockWorldCrood(BlockCroodInChunk c1, ChunkCroodInWorld c2);

	struct TexAbsCrood
	{
		GLdouble x, y;
	}; 
	struct TexRelCrood
	{
		GLuint x, y;
	};
}
