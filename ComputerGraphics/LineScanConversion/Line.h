#ifndef LINE_SCANCONVERSION_H
#define LINE_SCANCONVERSION_H

#include "../Include/Coordinate.h"
#include "../Include/Utils.h"
#include <vector>

class Line
{
public:
	Line(const Coordinate& s, const Coordinate& e) :
		_start(s), _end(e)
	{}

	std::vector<Coordinate> scanConversion();

private:
	Coordinate _start;
	Coordinate _end;

	const double stepBy = 0.01;

	const double diffDouble = 0.0000001;
};

#endif /* LINE_SCANCONVERSION_H */