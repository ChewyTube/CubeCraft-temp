#include "Croods.h"

namespace cubecraft {
	/*
	BlockCroodInWorld::BlockCroodInWorld(BlockCroodInChunk c1, ChunkCroodInWorld c2) {
		this->x = c2.x * 16 + c1.x;
		this->y = c2.y * 16 + c1.y;
		this->z = c2.z * 16 + c1.z;
		this->w = c2.w * 16 + c1.w;
	}
	BlockCroodInChunk::BlockCroodInChunk(BlockCroodInWorld c) {
		// @TODO看着不太安全 -> 用concept限定Crood模板的T
		this->x = (size_t)c.x % 16;
		this->y = (size_t)c.y % 16;
		this->z = (size_t)c.z % 16;
		this->w = (size_t)c.w % 16;
	}
	ChunkCroodInWorld::ChunkCroodInWorld(BlockCroodInWorld c) {
		this->x = (size_t)c.x / 16;
		this->y = (size_t)c.y / 16;
		this->z = (size_t)c.z / 16;
		this->w = (size_t)c.w / 16;
	}
	*/
	ChunkCroodInWorld getChunkCrood(BlockCroodInWorld c) {
		auto x = (size_t)c.x / 16;
		auto y = (size_t)c.y / 16;
		auto z = (size_t)c.z / 16;
		auto w = (size_t)c.w / 16;
		return { x, y, z, w };
	}
	BlockCroodInChunk getBlockChunkCrood(BlockCroodInWorld c) {
		auto x = (size_t)c.x % 16;
		auto y = (size_t)c.y % 16;
		auto z = (size_t)c.z % 16;
		auto w = (size_t)c.w % 16;
		return { x, y, z, w };
	}
}