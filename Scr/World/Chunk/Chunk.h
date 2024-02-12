#pragma once
#include <unordered_map>

#include "ChunkMeshBuilder.h"

class World;
namespace cubecraft {
	using blockDataType = std::unordered_map<BlockCroodInChunk, Block, CroodHash, CroodEqual>;
	
	class Chunk{
	public:
		Chunk(World* p, ChunkCroodInWorld c){
			mp_world = p;
			builder = ChunkMeshBuilder(p, c);

			m_crood = c;
		}

		blockDataType& getBlockData();
		void setBlock(BlockCroodInChunk crood, Block block);
		void buildMesh();
		Mesh getMesh();
		Block getBlock(BlockCroodInChunk crood);
		
		bool empty();
	private:
		ChunkCroodInWorld m_crood;
		blockDataType blockData;
		Mesh mesh;
		ChunkMeshBuilder builder = ChunkMeshBuilder(nullptr, {});
		World* mp_world;
	};
}
