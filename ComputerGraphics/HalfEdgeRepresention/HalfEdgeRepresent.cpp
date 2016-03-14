#include "HalfEdgeRepresent.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include "SimpleGraph.h"
#include "HEEdgeInitializer.h"

using std::string;
using std::ifstream;
using std::getline;
using std::vector;
using std::move;
using std::shared_ptr;
using std::make_shared;

HalfEdgeRepresent::HalfEdgeRepresent(ifstream& is)
{
	vector<Coordinate> tmpVertex;
	auto graph = objToGraph(is, tmpVertex);
	buildHE(graph, tmpVertex);
}

SimpleGraph HalfEdgeRepresent::objToGraph(ifstream& is, vector<Coordinate>& tmpVertex)
{
	SimpleGraph graph;
	bool hasResize = false;
	int faceCount = 0;

	while (!is.eof())
	{
		string line;
		getline(is, line);

		vector<string> splited;
		switch (line.front())
		{
		case '#':
			continue;

		case 'v':
			splited = split(line, ' ');
			tmpVertex.push_back(Coordinate(atof(splited[1].c_str()),
				atof(splited[2].c_str()), atof(splited[3].c_str())));
			break;

		case 'f':
			if (!hasResize)
			{
				graph.setSize(tmpVertex.size());
				hasResize = true;
			}
			splited = split(line, ' ');
			for (auto iter = splited.begin() + 1; iter != splited.end() - 1; iter++)
				graph.addEdge(atoi(iter->c_str()), atoi((iter + 1)->c_str()), faceCount);
			graph.addEdge(atoi(splited.back().c_str()), atoi((splited.begin() + 1)->c_str()), faceCount);

			faceCount += 1;
			break;
		}
	}

	return move(graph);
}

void HalfEdgeRepresent::buildHE(const SimpleGraph& graph, const vector<Coordinate>& tmpVertex)
{
	HEEdgeInitializer heInit;

	std::vector<shared_ptr<HEEdge>> tmpEdge;
	for (size_t i = 0; i < tmpVertex.size(); i++)
	{
		auto edges = graph.edgeOf(i);
		for (auto edge : edges)
		{
			shared_ptr<HEEdge> curEdge(new HEEdge());

			shared_ptr<HEVertex> startVertex = constructedVertex(edge.startVertex());
			if (!startVertex)
			{
				startVertex.reset(new HEVertex());
				startVertex->vertexNo = edge.startVertex();
				startVertex->point = tmpVertex[i];
				startVertex->edges.push_back(curEdge);
				vertexList.push_back(startVertex);
			}
			else
			{
				startVertex->edges.push_back(curEdge);
			}

			/*shared_ptr<HEVertex> startVertex(new HEVertex());
			startVertex->vertexNo = edge.startVertex();
			startVertex->point = tmpVertex[i];
			startVertex->edges.push_back(curEdge);
			if (!hasConstructVertex(startVertex->vertexNo))
				vertexList.push_back(startVertex);*/

			shared_ptr<HEFace> incFace(new HEFace());
			incFace->faceNo = edge.faceNo();
			incFace->edge = curEdge;
			if (!hasConstructFace(incFace->faceNo))
				faceList.push_back(incFace);

			curEdge->idEnd = edge.endVertex();
			curEdge->origin = startVertex;
			curEdge->incFace = incFace;
			tmpEdge.push_back(curEdge);

			heInit.registerWant(curEdge, curEdge->incFace->faceNo, graph);
		}
	}

	for (auto edge : tmpEdge)
	{
		heInit.processWant(edge, tmpEdge);
	}

	edgeList = tmpEdge;
}

void HalfEdgeRepresent::LoopTessellate(int iterCount)
{
	if (iterCount <= 0)
		return;


}

vector<string> HalfEdgeRepresent::split(const string& str, char ch)
{
	vector<string> ret;

	size_t preIndex = 0;
	size_t curIndex = 0;
	while (preIndex < str.size())
	{
		curIndex = str.find_first_of(ch, preIndex);
		if (curIndex == string::npos)
			break;
		ret.push_back(str.substr(preIndex, curIndex - preIndex));
		preIndex = curIndex + 1;
	}
	ret.push_back(str.substr(preIndex, str.size() - preIndex));

	for (auto iter = ret.begin(); iter != ret.end();)
	{
		if (iter->empty())
			iter = ret.erase(iter);
		else
			++iter;
	}

	return move(ret);
}

shared_ptr<HEVertex> HalfEdgeRepresent::constructedVertex(int v)
{
	for (auto vertex : vertexList)
	{
		if (vertex->getVertexNo() == v)
			return vertex;
	}

	return shared_ptr<HEVertex>(nullptr);
}

bool HalfEdgeRepresent::hasConstructFace(int f)
{
	for (auto face : faceList)
	{
		if (face->faceNo == f)
			return true;
	}

	return false;
}

//bool HalfEdgeRepresent::hasConstructEdge(int s, int p, shared_ptr<HEEdge> out)
//{
//	for (auto edge : edgeList)
//	{
//		if (edge->origin->vertexNo == s &&
//			edge->next->origin->vertexNo == p &&
//			edge->constructed == true)
//		{
//			out = edge;
//			return true;
//		}
//	}
//
//	return false;
//}