#include "ChunkMeshBuilder.h"

#include "../World.h"

namespace cubecraft {
	Mesh ChunkMeshBuilder::buildMesh(chunkDataType data) {
		if (data.size() == 0) {
			std::cout << "Empty chunk;Chunkcrood:" << m_crood.x << ", " << m_crood.y << ", " << m_crood.z << std::endl;
			return Mesh();
		}
		float startTime = static_cast<float>(glfwGetTime());

		// 通过区块数据合成一个顶点数据
		std::vector<GLfloat> vertices;
		std::vector<GLuint> vIndices;
		std::vector<GLfloat> tIndices;

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

		//@TODO使用Log.h
		float endTime = static_cast<float>(glfwGetTime());
		std::cout << "Successfully build chunk mesh. Use time:" << (endTime - startTime)*1000 << "ms";
		std::cout << "	Chunk crood:" << m_crood.x << ", " << m_crood.y << ", " << m_crood.z << std::endl;
		return mesh;
	}
	int ChunkMeshBuilder::getBlock(chunkDataType& data, BlockCroodInChunk crood) {
		auto result = data.find(crood);
		if (result != data.end()) {
			return result->second.getId();
		}
		else
		{
			auto blockcrood = getBlockWorldCrood(crood, m_crood);
			auto block = mp_world->getBlock(blockcrood, get);
			return block.getId();
		}
	}
	void ChunkMeshBuilder::addFace(
		std::vector<GLfloat>&	vertices,
		std::vector<GLuint>&	vIndices, 
		std::vector<GLfloat>&	tIndices,
		Direction				dir, 
		BlockCroodInChunk		pos, 
		int&					addedFaces
	) {
		std::array<GLfloat, 8> textureIndices{};
		switch (dir)
		{
		case cubecraft::up:
			textureIndices = segmenter.getTexIndices({ 2, 0 });
			break;
		case cubecraft::down:
			textureIndices = segmenter.getTexIndices({ 0, 0 });
			break;
		case cubecraft::left:
			textureIndices = segmenter.getTexIndices({ 1, 0 });
			break;
		case cubecraft::right:
			textureIndices = segmenter.getTexIndices({ 1, 0 });
			break;
		case cubecraft::front:
			textureIndices = segmenter.getTexIndices({ 1, 0 });
			break;
		case cubecraft::back:
			textureIndices = segmenter.getTexIndices({ 1, 0 });
			break;
		default:
			textureIndices = segmenter.getTexIndices({ 0, 0 });
			break;
		}

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
		vIndices.insert(vIndices.end(), blockIndices.begin(), blockIndices.end());
		tIndices.insert(tIndices.end(), textureIndices.begin(), textureIndices.end());
		// 调整索引
		for (int i = 0; i < 12; i++) {
			if (i % 3 == 0) { vertices[vertices.size() - 12 + i] += (pos.x - 1); }
			if (i % 3 == 1) { vertices[vertices.size() - 12 + i] += (pos.y - 1); }
			if (i % 3 == 2) { vertices[vertices.size() - 12 + i] += (pos.z - 1); }
		}
		for (int i = 0; i < 6; i++) {
			vIndices[vIndices.size() - i - 1] += 4 * addedFaces;
		}

		addedFaces++;
	}
	// ---------------------------------------------------------------
	// 似乎顶点数据要和材质索引一一对应
	Mesh ChunkMeshBuilder::buildMeshwithPoint(chunkDataType data) {
		float startTime = static_cast<float>(glfwGetTime());

		// 通过区块数据合成一个顶点数据
		Vertices verticesPoints;
		std::vector<GLuint> vIndices;

		int addedFaces = 0;// 已添加的面数

		for (auto& block : data) {
			auto position = block.first;
			auto blockType = block.second;
			adj.update(position);

			if (getBlock(data, adj.up) == -1) { // 上面没有方块
				addFaceWithPoint(verticesPoints, vIndices, up, adj.up, addedFaces);
			}
			if (getBlock(data, adj.down) == -1) { // 下面没有方块
				addFaceWithPoint(verticesPoints, vIndices, down, adj.up, addedFaces);
			}
			if (getBlock(data, adj.left) == -1) {
				addFaceWithPoint(verticesPoints, vIndices, left, adj.up, addedFaces);
			}
			if (getBlock(data, adj.right) == -1) {
				addFaceWithPoint(verticesPoints, vIndices, right, adj.up, addedFaces);
			}
			if (getBlock(data, adj.front) == -1) {
				addFaceWithPoint(verticesPoints, vIndices, front, adj.up, addedFaces);
			}
			if (getBlock(data, adj.back) == -1) {
				addFaceWithPoint(verticesPoints, vIndices, back, adj.up, addedFaces);
			}
		}

		auto vertices = getVerticesfromPoints(verticesPoints);
		auto tIndices = getTIndicesfromPoints(verticesPoints);
  		Mesh mesh(vertices, vIndices, tIndices);

		//@TODO使用Log.h
		float endTime = static_cast<float>(glfwGetTime());
		std::cout << "Successfully build chunk mesh. Use time:" << (endTime - startTime) * 1000 << "ms\n";

		return mesh;
	}
	void ChunkMeshBuilder::addFaceWithPoint(
		Vertices&				verticesPoints,
		std::vector<GLuint>&	vIndices, 
		Direction				dir, 
		BlockCroodInChunk		pos, 
		int&					addedFaces
	) {
		/*
		// 最终点数据（已去重），转化为vertices返回, GLuint是对应的vIndices索引
		std::array<Point, 4> points;			// 暂存点(坐标)数据
		std::array<GLuint, 4> tmpVIndices{};	// 暂存索引数据

		std::array<Vertex, 4> vertices{};		// 暂存顶点数据

		// 获取，修正对应点
		switch (dir)
		{
		case cubecraft::up:
			points = topPoint;
			break;
		case cubecraft::down:
			points = bottomPoint;
			break;
		case cubecraft::left:
			points = leftPoint;
			break;
		case cubecraft::right:
			points = rightPoint;
			break;
		case cubecraft::front:
			points = frontPoint;
			break;
		case cubecraft::back:
			points = backPoint;
			break;
		default:
			break;
		}
		for (int i = 0; i < vertices.size(); i++) {
			auto& v = vertices[i];
			v.p = points[i];
			v.p.x += pos.x;
			v.p.y += pos.y;
			v.p.z += pos.z;
			v.t.x = texturePoints[i][0];
			v.t.y = texturePoints[i][1];
		}

		// 遍历points,看p是否已经出现过，出现过就直接使用索引
		for (int i = 0; i < vertices.size();i++) {
			auto& p = vertices[i];
			auto it = verticesPoints.find(p);
			if (it == verticesPoints.end()) { // 没出现过 增加这个点
				verticesPoints.insert({ p, verticesPoints.size()});
			}
			// 增加索引
			tmpVIndices[i] = verticesPoints.find(p)->second;
			tIndices.insert(tIndices.end(), texturePoints[i].begin(), texturePoints[i].end());
		}

		// 插入顶点索引
		vIndices.push_back(tmpVIndices[0]);
		vIndices.push_back(tmpVIndices[1]);
		vIndices.push_back(tmpVIndices[3]);
		vIndices.push_back(tmpVIndices[1]);
		vIndices.push_back(tmpVIndices[2]);
		vIndices.push_back(tmpVIndices[3]);
		*/
		std::array<Vertex, 4> vertices{};	// 候选顶点
		std::array<Point, 4> points{};		// 候选顶点的point部分
		std::array<GLuint, 4> indices{};	// 获选顶点的索引

		// 获取并修正vertices
		switch (dir)
		{
		case cubecraft::up:
			points = topPoint;
			break;
		case cubecraft::down:
			points = bottomPoint;
			break;
		case cubecraft::left:
			points = leftPoint;
			break;
		case cubecraft::right:
			points = rightPoint;
			break;
		case cubecraft::front:
			points = frontPoint;
			break;
		case cubecraft::back:
			points = backPoint;
			break;
		default:
			break;
		}
		for (int i = 0; i < vertices.size(); i++) {
			points[i].x += pos.x;
			points[i].y += pos.y;
			points[i].z += pos.z;

			vertices[i].p = points[i];
			vertices[i].t.x = texturePoints[i][0];
			vertices[i].t.y = texturePoints[i][1];
		}
 
		// vertex是否已经出现过(在verticesPoints中存在)
		for (int i = 0; i < vertices.size(); i++) {
			auto it = verticesPoints.find(vertices[i]);
			if (it == verticesPoints.end()) {
				// 没出现过
				verticesPoints.insert({ vertices[i], verticesPoints.size() });
			}
			indices[i] = verticesPoints.find(vertices[i])->second;
		}

		// 完成顶点索引
		vIndices.push_back(indices[0]);
		vIndices.push_back(indices[1]);
		vIndices.push_back(indices[3]);
		vIndices.push_back(indices[1]);
		vIndices.push_back(indices[2]);
		vIndices.push_back(indices[3]);

		addedFaces++;
	}
	std::vector<GLfloat> ChunkMeshBuilder::getVerticesfromPoints(Vertices& verticesPoints) {
		std::vector<GLfloat> result(verticesPoints.size() * 3);
		for (auto& p : verticesPoints) {
			//result.insert(result.end(), { p.first.x, p.first.y, p.first.z });
			result[p.second * 3 + 0] = p.first.p.x;
			result[p.second * 3 + 1] = p.first.p.y;
			result[p.second * 3 + 2] = p.first.p.z;
		}
		return result;
	}
	std::vector<GLfloat> ChunkMeshBuilder::getTIndicesfromPoints(Vertices& verticesPoints) {
		std::vector<GLfloat> result(verticesPoints.size() * 2);
		for (auto& v : verticesPoints) {
			result[v.second * 2 + 0] = v.first.t.x;
			result[v.second * 2 + 1] = v.first.t.y;
		}
		return result;
	}
}