#ifndef POLYGONSCANCONVERSION_H
#define POLYGONSCANCONVERSION_H

#include "../Include/Coordinate.h"
#include "EdgeNode.h"
#include <vector>
#include <list>
#include <set>
#include <memory>

class Polygon
{
public:
	Polygon(const std::vector<Coordinate>& v) :
		vertexSet(v), stepBy(1)
	{}
	Polygon(const std::vector<Coordinate>& v, double s) :
		vertexSet(v), stepBy(s)
	{}

	~Polygon() = default;

	using EdgeList = std::vector<std::shared_ptr<EdgeNode>>;

	std::vector<Coordinate> ScanConversion();

private:
	std::vector<Coordinate> vertexSet;

	double stepBy;

	const double offset = 0.000001;

	double calculateZ(double, double, double, double, double);
};

#endif // POLYGONSCANCONVERSION_H