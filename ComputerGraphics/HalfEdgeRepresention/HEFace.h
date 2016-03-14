#pragma once

#include <memory>
#include "define.h"

class HEFace
{
	friend class HalfEdgeRepresent;
public:

private:
	int faceNo;
	std::shared_ptr<HEEdge> edge;
};
