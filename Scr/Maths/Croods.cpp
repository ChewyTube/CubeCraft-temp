﻿#include "Croods.h"

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
		auto x = (GLint64)c.x / 16;
		auto y = (GLint64)c.y / 16;
		auto z = (GLint64)c.z / 16;
		auto w = (GLint64)c.w / 16;
		return { x, y, z, w };
	}
	BlockCroodInChunk getBlockChunkCrood(BlockCroodInWorld c) {
		auto x = (GLint64)c.x % 16;
		auto y = (GLint64)c.y % 16;
		auto z = (GLint64)c.z % 16;
		auto w = (GLint64)c.w % 16;
		return { x, y, z, w };
	}
	BlockCroodInWorld getBlockWorldCrood(BlockCroodInChunk c1, ChunkCroodInWorld c2) {
		GLint64 x = c1.x + c2.x * 16;
		GLint64 y = c1.y + c2.y * 16;
		GLint64 z = c1.z + c2.z * 16;
		GLint64 w = c1.w + c2.w * 16;
		return{ x, y, z, w };
	}
}