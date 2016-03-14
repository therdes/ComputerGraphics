#ifndef EDGENODE_H
#define EDGENODE_H

#include <memory>
#include <utility>
#include "Edge.h"

class EdgeNode
{
public:
	EdgeNode(const Edge& e, double x) :
		edge(e)
	{
		_y_max = e.maxY();
		_cur_x = x;
		_k__1 = e.rSlop();
	}

	double y_max() const
	{
		return _y_max;
	}
	double y_min() const
	{
		return (edge.headPoint.y() < edge.tailPoint.y()) ? edge.headPoint.y() : edge.tailPoint.y();
	}

	double x() const
	{
		return _cur_x;
	}
	double& x()
	{
		return _cur_x;
	}
	double k_1() const
	{
		return _k__1;
	}

	double z_of_MaxY() const
	{
		return (edge.headPoint.y() > edge.tailPoint.y()) ? edge.headPoint.z() : edge.tailPoint.z();
	}
	double z_of_MinY() const
	{
		return (edge.headPoint.y() > edge.tailPoint.y()) ? edge.tailPoint.z() : edge.headPoint.z();
	}

private:
	double _y_max;
	double _cur_x;
	double _k__1;

	const Edge edge;
};

#endif // EDGENODE_H