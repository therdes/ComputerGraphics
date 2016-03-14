#include "HEEdgeInitializer.h"
#include <algorithm>

using std::shared_ptr;
using std::vector;
using std::find_if;

void HEEdgeInitializer::registerWant(const std::shared_ptr<HEEdge>& agent, int faceNo, const SimpleGraph& graph)
{
	auto edges = graph.edgeOf(agent->idEnd);
	for (auto edge : edges)
	{
		if (edge.faceNo() == faceNo ||
			edge.endVertex() == agent->origin->vertexNo)
		{
			wantList.push_back(Wanted(agent, edge.startVertex(), edge.endVertex()));
		}
	}
}

void HEEdgeInitializer::processWant(std::shared_ptr<HEEdge> agent, const std::vector<std::shared_ptr<HEEdge>>& tmpEdge)
{
	for (auto wantIter = wantList.begin(); wantIter != wantList.end(); )
	{
		if (wantIter->agent->origin->vertexNo == agent->origin->vertexNo &&
			wantIter->agent->idEnd == agent->idEnd)
		{
			auto target = *find_if(tmpEdge.begin(), tmpEdge.end(),
				[wantIter](const std::shared_ptr<HEEdge>& targetEdge) {
				if (wantIter->getTargetStart() == targetEdge->getOrigin()->getVertexNo() &&
					wantIter->getTargetEnd() == targetEdge->getIdEnd())
					return true;
				return false;
			});

			if (target->idEnd == agent->origin->vertexNo)
				agent->opposite = target;
			else
				agent->next = target;

			wantIter = wantList.erase(wantIter);
		}
		else
		{
			wantIter += 1;
		}
	}
}