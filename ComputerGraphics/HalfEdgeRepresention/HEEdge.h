#pragma once

#include <memory>
#include "define.h"
#include "HEEdgeInitializer.h"
#include "HalfEdgeRepresent.h"

class HEEdge
{
	friend class HalfEdgeRepresent;
	friend class HEEdgeInitializer;
public:
	int getIdEnd() const
	{
		return idEnd;
	}
	const std::shared_ptr<HEVertex> getOrigin() const
	{
		return origin;
	}
	const std::shared_ptr<HEEdge> getOpposite() const
	{
		return opposite;
	}
	const std::shared_ptr<HEFace> getIncFace() const
	{
		return incFace;
	}
	const std::shared_ptr<HEEdge> getNext() const
	{
		return next;
	}

private:
	int idEnd;

	std::shared_ptr<HEVertex> origin;
	std::shared_ptr<HEEdge> opposite;
	std::shared_ptr<HEFace> incFace;
	std::shared_ptr<HEEdge> next;

	//bool constructed = false;
};
