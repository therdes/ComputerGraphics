#pragma once

#include "HalfEdgeRepresent.h"
#include <vector>

class SimpleEdge
{
public:
	SimpleEdge(int s, int p, int f) :
		start(s), end(p), face(f)
	{}

	int startVertex() const
	{
		return start;
	}
	int endVertex() const
	{
		return end;
	}
	int faceNo() const
	{
		return face;
	}

private:
	int start;
	int end;
	int face;
};

class SimpleGraph
{
	friend class HalfEdgeRepresent;
public:
	SimpleGraph() = default;

	SimpleGraph(int size)
	{
		setSize(size);
	}

	void addEdge(int s, int p, int faceNo)
	{
		adjMatrix[s][p] = faceNo;
	}

	bool isConnect(int s, int p) const
	{
		return adjMatrix[s][p] != NO_EDGE;
	}
	int faceNo(int s, int p) const
	{
		return adjMatrix[s][p];
	}

	std::vector<SimpleEdge> edgeOf(int v) const
	{
		std::vector<SimpleEdge> ret;

		auto len = adjMatrix[v].size();
		for (decltype(len) i = 0; i < len; i++)
		{
			auto face = faceNo(v, i);
			if (face != NO_EDGE)
				ret.push_back(SimpleEdge(v, i, face));
		}

		return std::move(ret);
	}

private:
	const int NO_EDGE = -1;

	std::vector<std::vector<int>> adjMatrix;

	void setSize(size_t size)
	{
		adjMatrix.resize(size);
		for (auto& item : adjMatrix)
		{
			item.resize(size);
			for (auto& edge : item)
				edge = NO_EDGE;
		}
	}
};
