#include "NewEdgeTable.h"
#include "../Include/Utils.h"

using std::shared_ptr;
using std::make_shared;
using std::ostream;

shared_ptr<Polygon::EdgeList>
NewEdgeTable::operator[](double i)
{
	if (i == scanLineIndex)
		return net;

	scanLineIndex = i;

	net.reset(new Polygon::EdgeList());

	auto iter = vertexSet.begin();
	decltype(iter) forwardIter, backwardIter;

	while (iter != vertexSet.end())
	{
		double off = offset;
		iter = find_if(iter, vertexSet.end(),
			[i, off](Coordinate coor)
		{
			return doubleEqual(coor.y(), i, off);
		});

		if (iter == vertexSet.end())
			break;

		if (iter == vertexSet.begin())
		{
			forwardIter = iter + 1;
			backwardIter = vertexSet.end() - 1;
		}
		else if (iter == vertexSet.end() - 1)
		{
			forwardIter = vertexSet.begin();
			backwardIter = iter - 1;
		}
		else
		{
			forwardIter = iter + 1;
			backwardIter = iter - 1;
		}

		if (forwardIter->y() > iter->y())
		{
			Edge edge(*forwardIter, *iter);
			net->push_back(make_shared<EdgeNode>(edge, iter->x()));
		}
		if (backwardIter->y() > iter->y())
		{
			Edge edge(*iter, *backwardIter);
			net->push_back(make_shared<EdgeNode>(edge, iter->x()));
		}

		iter++;
	}

	return net;
}