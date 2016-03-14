#include "Line.h"

using std::vector;

vector<Coordinate> Line::scanConversion()
{
	vector<Coordinate> ret;

	/* Step By One */
	/*double x = _start.x();
	double y = _start.y();

	double dx = _end.x() - _start.x();
	double dy = _end.y() - _start.y();

	double k = (doubleEqual(dx, 0, 0.000001)) ? dy : dy / dx;

	double e = -0.5;

	for (int i = 0; i <= dx; i++)
	{
		ret.push_back(Coordinate(x, y, 0));

		x += 1;
		e += k;

		if (e >= 0)
		{
			y += 1;
			e -= 1;
		}
	}*/

	double dx = _end.x() - _start.x();
	double dy = _end.y() - _start.y();

	double k = (doubleEqual(dx, 0, diffDouble)) ? dy : dy / dx;

	double max = (abs(k) < 1) ? abs(dx) : abs(dy);

	double e = (k > 0) ? -(stepBy / 2) : (stepBy / 2);

	double x = _start.x();
	double y = _start.y();

	double xInc = stepBy;
	double yInc = (k > 0) ? stepBy : -stepBy;
	double eInc = (k > 0) ? stepBy : -stepBy;

	for (double i = 0; i <= max; i += stepBy)
	{
		ret.push_back(Coordinate(x, y, 0));

		if (abs(k) < 1)
		{
			x += xInc;
			e += k * stepBy;
		}
		else
		{
			y += yInc;
			e += (1 / k) * stepBy;
		}

		bool cond = (k > 0) ? (e >= 0) : (e <= 0);
		if (cond)
		{
			if (abs(k) < 1)
				y += yInc;
			else
				x += xInc;
			e -= eInc;
		}
	}

	return ret;
}