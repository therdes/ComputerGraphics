#include "PolygonScanConversion.h"
#include "EdgeNode.h"
#include "Edge.h"
#include <climits>
#include <list>
#include <algorithm>
#include <memory>
#include <vector>
#include <set>
#include "NewEdgeTable.h"
#include "../Include/Utils.h"
#include <utility>

using std::list;
using std::vector;
using std::shared_ptr;
using std::make_shared;
using std::find_if;
using std::set;
using std::abs;
using std::move;

vector<Coordinate> Polygon::ScanConversion()
{
	vector<Coordinate> ret;
	NewEdgeTable net(vertexSet);

	int maxScanNo = INT_MIN;
	int minScanNo = INT_MAX;
	for (auto coor : vertexSet)
	{
		if (coor.y() > maxScanNo)
			maxScanNo = static_cast<int>(coor.y());
		if (coor.y() < minScanNo)
			minScanNo = static_cast<int>(coor.y());
	}

	EdgeList activeEdgeList;
	for (double i = minScanNo; i <= maxScanNo; i += stepBy)
	{
		for (const auto item : *net[i])
		{
			const auto off = offset;
			activeEdgeList.insert(find_if(activeEdgeList.begin(), activeEdgeList.end(),
				[item, off](const shared_ptr<EdgeNode>& curNode)
			{
				return curNode->x() > item->x() ||
					(doubleEqual(curNode->x(), item->x(), off) && curNode->k_1() > item->k_1());
			}), item);
		}

		if (!doubleEqual(i, maxScanNo, offset))
			for (auto iter = activeEdgeList.begin(); iter != activeEdgeList.end();)
				if (doubleEqual((*iter)->y_max(), i, offset))
					iter = activeEdgeList.erase(iter);
				else
					iter += 1;

		for (size_t j = 0; j < activeEdgeList.size(); j += 2)
		{
			auto leftSideEdge = activeEdgeList[j];
			auto rightSideEdge = activeEdgeList[j + 1];

			auto zOfLeftMost = calculateZ(leftSideEdge->z_of_MinY(), leftSideEdge->z_of_MaxY(),
				leftSideEdge->y_min(), leftSideEdge->y_max(), i);
			auto zOfRightMost = calculateZ(rightSideEdge->z_of_MinY(), rightSideEdge->z_of_MaxY(),
				rightSideEdge->y_min(), rightSideEdge->y_max(), i);

			ret.push_back(Coordinate(leftSideEdge->x(), i, zOfLeftMost));
			for (auto k = leftSideEdge->x() + stepBy; k < rightSideEdge->x(); k += stepBy)
			{
				ret.push_back(Coordinate(k, i,
					calculateZ(zOfLeftMost, zOfRightMost, leftSideEdge->x(), rightSideEdge->x(), k)));
			}
			ret.push_back(Coordinate(rightSideEdge->x(), i, zOfRightMost));
		}

		for (auto iter = activeEdgeList.begin(); iter != activeEdgeList.end();)
		{
			if ((*iter)->y_max() > i)
			{
				(*iter)->x() += (*iter)->k_1() * stepBy;
				iter += 1;
			}
			else
			{
				iter = activeEdgeList.erase(iter);
			}
		}
	}

	/*for (auto iter = vertexSet.cbegin(); iter != vertexSet.cend(); iter += 1)
		ret.push_back(*iter);*/

	return move(ret);
}

double Polygon::calculateZ(double zMin, double zMax, double min, double max, double cur)
{
	if (doubleEqual(min, max, offset))
		return (zMin + zMax) / 2;
	else
		return zMin + (zMax - zMin) * (min - cur) / (min - max);
}