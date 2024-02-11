#pragma once

#include <unordered_map>

#include "../Maths/Croods.h"
#include "Chunk/Chunk.h"

namespace cubecraft{
	enum usage {
		set,
		get,
	};

	class World {
	public:
		World() {
			p_world = this;
		}
		void setBlock(BlockCroodInWorld crood);
		std::unordered_map<ChunkCroodInWorld, Chunk, CroodHash, CroodEqual> getWorldData();
		// @TODO 写一个获得世界Mesh的函数/合并chunkMesh
		void buildWorldMesh();
		Mesh getMesh();

		void buildMesh();//对所有区块buildMesh

		Block getBlock(BlockCroodInWorld crood, usage u);
		Chunk& getChunk(ChunkCroodInWorld crood, usage u);
	private:
		std::unordered_map<ChunkCroodInWorld, Chunk, CroodHash, CroodEqual> worldData;
		Mesh worldMesh;
		World* p_world;
	};
}

