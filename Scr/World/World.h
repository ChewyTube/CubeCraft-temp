#pragma once

#include <unordered_map>

#include "Chunk/Chunk.h"

#include "../Enum/Usage.h"

namespace cubecraft{
	using WorldDataType = std::unordered_map<ChunkCroodInWorld, Chunk, CroodHash, CroodEqual>;
	
	class World {
	public:
		World() {
			p_world = this;
		}
		void setBlock(BlockCroodInWorld crood, Block block);
		std::unordered_map<ChunkCroodInWorld, Chunk, CroodHash, CroodEqual> getWorldData();
		// @TODO 写一个获得世界Mesh的函数/合并chunkMesh
		void buildWorldMesh();
		Mesh getMesh();

		void buildMesh();//对所有区块buildMesh

		Block getBlock(BlockCroodInWorld crood, usage u);
		Chunk& getChunk(ChunkCroodInWorld crood, usage u);
	private:
		WorldDataType worldData;
		Mesh worldMesh;
		World* p_world;
	};
}

