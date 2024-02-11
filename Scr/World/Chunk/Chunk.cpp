#include "Chunk.h"

namespace cubecraft {
	blockDataType& Chunk::getBlockData() {
		return blockData;
	}
	void Chunk::setBlock(BlockCroodInChunk crood, int block) {
		blockData.insert({ crood, block });
	}
	
	void Chunk::buildMesh() {
		//mesh = builder.buildMeshwithPoint(blockData);
		mesh = builder.buildMesh(blockData);
	}
	Mesh Chunk::getMesh() {
		return mesh;
	}
	Block Chunk::getBlock(BlockCroodInChunk crood) {
		auto block = blockData.find(crood);
		if (block != blockData.end()) {
			return block->second;
		}
		else {
			return Block(-1);
		}
	}
	bool Chunk::empty() {
		return (mp_world == nullptr) && (m_crood == ChunkCroodInWorld());
	}
}