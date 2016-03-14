#ifndef BEZIERCURVE_H
#define BEZIERCURVE_H

#include "../Include/Coordinate.h"
#include <vector>

class BezierCurve
{
public:
	BezierCurve(const std::vector<Coordinate>& v) :
		vertexSetLine(v), conType(ConstructType::LINE)
	{}
	BezierCurve(const std::vector<Coordinate>&& v) :
		vertexSetLine(v), conType(ConstructType::LINE)
	{}
	BezierCurve(const std::vector<std::vector<Coordinate>>& v) :
		vertexSetSurface(v), conType(ConstructType::SURFACE)
	{}
	BezierCurve(const std::vector<std::vector<Coordinate>>&& v) :
		vertexSetSurface(v), conType(ConstructType::SURFACE)
	{}
	~BezierCurve() = default;

	BezierCurve(const BezierCurve&) = delete;
	const BezierCurve& operator=(const BezierCurve&) = delete;

	std::vector<Coordinate> deCasteljau();

private:
	std::vector<Coordinate> vertexSetLine;
	std::vector<std::vector<Coordinate>> vertexSetSurface;

	const double stepBy = 0.039;

	enum class ConstructType
	{
		LINE,
		SURFACE
	};

	const ConstructType conType;

	std::vector<Coordinate> deCasteljauLine();
	std::vector<Coordinate> deCasteljauSurface();
};

#endif /* BEZIERCURVE_H */