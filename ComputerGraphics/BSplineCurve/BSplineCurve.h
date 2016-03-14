#ifndef BSPLINECURVE_H
#define BSPLINECURVE_H

#include "../Include/Coordinate.h"
#include <vector>

class BSplineCurve
{
public:
	BSplineCurve(const std::vector<Coordinate>&);
	BSplineCurve(const std::vector<std::vector<Coordinate>>&);
	~BSplineCurve() = default;

	BSplineCurve(const BSplineCurve&) = delete;
	const BSplineCurve& operator=(const BSplineCurve&) = delete;

	std::vector<Coordinate> deBoor();

private:
	std::vector<Coordinate> vertexesLine;
	std::vector<std::vector<Coordinate>> vertexesSurface;
	std::vector<double> knot;

	size_t numOfPoint;
	const size_t order = 3;

	const double stepBy = 0.01;

	enum class Type
	{
		LINE,
		SURFACE
	};

	Type type;

	std::vector<Coordinate> deBoorLine();
	std::vector<Coordinate> deBoorSurface();
};

#endif /* BSPLINECURVE_H */