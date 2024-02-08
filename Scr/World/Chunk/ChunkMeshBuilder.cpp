#include "ChunkMeshBuilder.h"

namespace cubecraft {
	Mesh ChunkMeshBuilder::buildMesh(chunkDataType data) {
		// 通过区块数据合成一个顶点数据
		std::vector<GLfloat> vertices;
		std::vector<GLuint> vIndices;
		std::vector<GLuint> tIndices;

		int addedFaces = 0;// 已添加的面数

		for (auto& block : data) {
			auto position = block.first;
			auto blockType = block.second;
			adj.update(position);

			if (getBlock(data, adj.up) == -1) { // 上面没有方块
				addFace(vertices, vIndices, tIndices, up, adj.up, addedFaces);
			}
			if (getBlock(data, adj.down) == -1) { // 下面没有方块
				addFace(vertices, vIndices, tIndices, down, adj.up, addedFaces);
			}
			if (getBlock(data, adj.left) == -1) { 
				addFace(vertices, vIndices, tIndices, left, adj.up, addedFaces);
			}
			if (getBlock(data, adj.right) == -1) { 
				addFace(vertices, vIndices, tIndices, right, adj.up, addedFaces);
			}
			if (getBlock(data, adj.front) == -1) { 
				addFace(vertices, vIndices, tIndices, front, adj.up, addedFaces);
			}
			if (getBlock(data, adj.back) == -1) { 
				addFace(vertices, vIndices, tIndices, back, adj.up, addedFaces);
			}
		}

		Mesh mesh(vertices, vIndices, tIndices);

		return mesh;
	}
	int ChunkMeshBuilder::getBlock(chunkDataType& data, BlockCroodInChunk crood) {
		try
		{
			return data.at(crood);
		}
		catch (const std::exception&)
		{
			return -1;
		}
	}
	void ChunkMeshBuilder::addFace(std::vector<GLfloat>& vertices,
		std::vector<GLuint>& vIndices, std::vector<GLuint>& tIndices,
		Direction dir, BlockCroodInChunk pos, int& addedFaces) {
		// 添加索引
		switch (dir)
		{
		case cubecraft::up:
			vertices.insert(vertices.end(), topFace.begin(), topFace.end());
			break;
		case cubecraft::down:
			vertices.insert(vertices.end(), bottomFace.begin(), bottomFace.end());
			break;
		case cubecraft::left:
			vertices.insert(vertices.end(), leftFace.begin(), leftFace.end());
			break;
		case cubecraft::right:
			vertices.insert(vertices.end(), rightFace.begin(), rightFace.end());
			break;
		case cubecraft::front:
			vertices.insert(vertices.end(), frontFace.begin(), frontFace.end());
			break;
		case cubecraft::back:
			vertices.insert(vertices.end(), backFace.begin(), backFace.end());
			break;
		default:
			break;
		}
		vIndices.insert(vIndices.begin(), blockIndices.begin(), blockIndices.end());
		tIndices.insert(tIndices.begin(), textureIndices.begin(), textureIndices.end());
		// 调整索引
		for (int i = 0; i < 12; i++) {
			(vertices.end() - i) += 12 * addedFaces;
		}
		for (int i = 0; i < 6; i++) {
			(vIndices.end() - i) += 6 * addedFaces;
		}
		for (int i = 0; i < 8; i++) {
			(tIndices.end() - i) += 8 * addedFaces;
		}

		addedFaces++;
	}
}