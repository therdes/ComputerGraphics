#ifndef NEWEDGETABLE_H
#define NEWEDGETABLE_H

#include <memory>
#include <list>
#include "Edge.h"
#include "PolygonScanConversion.h"
#include "EdgeNode.h"
#include "../Include/Coordinate.h"
#include <iterator>
#include <algorithm>

class NewEdgeTable
{
public:
	NewEdgeTable(const std::vector<Coordinate>& vs) :
		vertexSet(vs), scanLineIndex(INFINITY), net(nullptr)
	{}
	~NewEdgeTable() = default;

	NewEdgeTable(const NewEdgeTable&) = delete;
	const NewEdgeTable& operator=(const NewEdgeTable&) = delete;

	std::shared_ptr<Polygon::EdgeList>
		operator[](double);

private:
	std::vector<Coordinate> vertexSet;

	double scanLineIndex;
	std::shared_ptr<Polygon::EdgeList> net;

	const double offset = 0.0001;
};

#endif /* NEWEDGETABLE_H */