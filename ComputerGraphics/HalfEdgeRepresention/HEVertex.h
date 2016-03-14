#pragma once

#include <memory>
#include "../Include/Coordinate.h"
#include "define.h"
#include "HEEdgeInitializer.h"
#include "HalfEdgeRepresent.h"
#include "HEEdge.h"

class HEVertex
{
	friend class HalfEdgeRepresent;
	friend class HEEdgeInitializer;
public:
	int getVertexNo() const
	{
		return vertexNo;
	}

	Coordinate getCoor() const
	{
		return point;
	}

	/*const std::shared_ptr<HEEdge> getEdge() const
	{
		return edge;
	}*/

	size_t getAdjEdgeCount() const
	{
		return edges.size();
	}
	const std::shared_ptr<HEEdge> adjEdgeAt(size_t pos) const
	{
		return edges.at(pos);
	}

private:
	int vertexNo;
	Coordinate point;
	//std::shared_ptr<HEEdge> edge;

	std::vector<std::shared_ptr<HEEdge>> edges;
};
