#ifndef UTILS_H
#define UTILS_H

#include <cmath>
inline bool doubleEqual(double x, double y, double offset)
{
	return abs(x - y) < offset;
}

#endif