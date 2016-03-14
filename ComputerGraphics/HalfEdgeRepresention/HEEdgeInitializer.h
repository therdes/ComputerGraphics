#pragma once

#include "define.h"
#include "HEVertex.h"
#include "HEFace.h"
#include "HEEdge.h"
#include "SimpleGraph.h"
#include <memory>
#include <vector>

class Wanted;

class HEEdgeInitializer
{
public:
	HEEdgeInitializer() = default;
	~HEEdgeInitializer() = default;

	void registerWant(const std::shared_ptr<HEEdge>&, int, const SimpleGraph&);
	void processWant(std::shared_ptr<HEEdge>, const std::vector<std::shared_ptr<HEEdge>>&);

private:
	std::vector<Wanted> wantList;
};

class Wanted
{
	friend class HEEdgeInitializer;
public:
	Wanted(std::shared_ptr<HEEdge> a, int s, int e) :
		agent(a), targetStart(s), targetEnd(e)
	{}

	const std::shared_ptr<HEEdge> getAgent() const
	{
		return agent;
	}

	int getTargetStart() const
	{
		return targetStart;
	}
	int getTargetEnd() const
	{
		return targetEnd;
	}

private:
	std::shared_ptr<HEEdge> agent;
	
	int targetStart;
	int targetEnd;
};

