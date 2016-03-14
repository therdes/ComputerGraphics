#pragma once

#include <fstream>
#include <string>
#include <vector>
#include "define.h"
#include "HEEdge.h"
#include "HEFace.h"
#include "HEVertex.h"
#include "SimpleGraph.h"
#include "../Include/Coordinate.h"

class HalfEdgeRepresent
{
public:
	HalfEdgeRepresent(const std::string& fileName) :
		HalfEdgeRepresent(std::ifstream(fileName))
	{}
	HalfEdgeRepresent(std::ifstream&);
	~HalfEdgeRepresent() = default;

	void LoopTessellate(int);

private:
	/*size_t numOfVertex;
	size_t numOfEdge;
	size_t numOfFace;*/

	std::vector<std::shared_ptr<HEEdge>> edgeList;
	std::vector<std::shared_ptr<HEVertex>> vertexList;
	std::vector<std::shared_ptr<HEFace>> faceList;

	typename SimpleGraph objToGraph(std::ifstream&, std::vector<Coordinate>&);
	void buildHE(const SimpleGraph&, const std::vector<Coordinate>&);

	std::vector<std::string> split(const std::string&, char);
	std::shared_ptr<HEVertex> constructedVertex(int);
	bool hasConstructFace(int);
	//bool hasConstructEdge(int, int, std::shared_ptr<HEEdge>);
};
