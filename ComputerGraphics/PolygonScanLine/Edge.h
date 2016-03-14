#ifndef EDGE_H
#define EDGE_H

#include "../Include/Coordinate.h"
#include <algorithm>

class Edge
{
	friend class EdgeNode;
public:
	Edge(const Coordinate& p, const Coordinate& q)
	{
		headPoint = (p.x() >= q.x()) ? p : q;
		tailPoint = (p.x() >= q.x()) ? q : p;
	}

	bool isHonrizontal() const
	{
		return headPoint.y() == tailPoint.y();
	}

	double maxY() const
	{
		return (headPoint.y() >= tailPoint.y()) ?
			headPoint.y() : tailPoint.y();
	}

	double slop() const
	{
		if (headPoint.x() == tailPoint.x())
			return 0;

		return (headPoint.y() - tailPoint.y()) / (headPoint.x() - tailPoint.x());
	}
	double rSlop() const
	{
		if (headPoint.y() == tailPoint.y())
			return headPoint.x() - tailPoint.x();

		return (headPoint.x() - tailPoint.x()) / (headPoint.y() - tailPoint.y());
	}

private:
	Coordinate headPoint;
	Coordinate tailPoint;
};

#endif // EDGE_H