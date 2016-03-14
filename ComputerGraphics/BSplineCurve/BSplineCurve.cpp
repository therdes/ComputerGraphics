#include "BSplineCurve.h"

using std::vector;

BSplineCurve::BSplineCurve(const vector<Coordinate>& v)
{
	vertexesLine = v;
	numOfPoint = vertexesLine.size();

	for (size_t i = 0; i < numOfPoint + order; i++)
		knot.push_back(i);

	type = Type::LINE;
}

BSplineCurve::BSplineCurve(const vector<vector<Coordinate>>& v)
{
	vertexesSurface = v;

	type = Type::SURFACE;
}

vector<Coordinate> BSplineCurve::deBoor()
{
	switch (type)
	{
	case BSplineCurve::Type::LINE:
		return deBoorLine();
		break;

	case BSplineCurve::Type::SURFACE:
		return deBoorSurface();
		break;

	default:
		return vector<Coordinate>();
		break;
	}
}

vector<Coordinate> BSplineCurve::deBoorLine()
{
	vector<Coordinate> ret;

	using IterVertex = vector<Coordinate>;
	using IterMatrix = vector<IterVertex>;

	IterMatrix matrix(order);
	for (auto& v : matrix)
		v = IterVertex(numOfPoint + order);

	auto iter = matrix.at(0).begin();
	for (auto coor : vertexesLine)
		*iter++ = coor;

	for (size_t j = order - 1; j < numOfPoint; j++)
	{
		for (double t = knot[j]; t < knot[j + 1]; t += stepBy)
		{
			for (size_t r = 1; r < order; r++)
			{
				for (size_t i = j - order + r + 1; i <= j; i++)
				{
					matrix[r][i] = ((t - knot[i]) / (knot[i + order - r] - knot[i]))*matrix[r - 1][i] +
						((knot[i + order - r] - t) / (knot[i + order - r] - knot[i]))*matrix[r - 1][i - 1];
				}
			}

			ret.push_back(matrix[order - 1][j]);
		}
	}

	return ret;
}

vector<Coordinate> BSplineCurve::deBoorSurface()
{
	vector<Coordinate> ret;

	/*using IterVertex = vector<Coordinate>;
	using IterLineMatrix = vector<IterVertex>;
	using IterSurfaceMatrix = vector<IterLineMatrix>;

	const size_t numLineOfSurface = vertexesSurface.size();
	size_t max = 0;
	for (auto matrix : vertexesSurface)
		if (matrix.size() > max)
			max = matrix.size();
	const size_t numPointOfLine = max;

	IterSurfaceMatrix matrix(numLineOfSurface);
	for (auto& lineMatrix : matrix)
	{
		lineMatrix = IterLineMatrix(order);
		for (auto& vertexMatrix : lineMatrix)
			vertexMatrix = IterVertex(numPointOfLine + order);
	}

	for (size_t i = 0; i < numLineOfSurface; i++)
		for (size_t j = 0; j < vertexesSurface.at(i).size(); j++)
			matrix[i][0][j] = vertexesSurface[i][j];

	int lineIter = 0;
	for (size_t k = order - 1; k < numLineOfSurface; k++)
	{
		for (size_t j = order - 1; j < vertexesSurface[lineIter].size(); j++)
		{
			vector<double> curKnot;
			for (size_t i = 0; i < vertexesSurface[lineIter].size() + order; i++)
				curKnot.push_back(i);

			for (double t = curKnot[j]; t < curKnot[j + 1]; t += stepBy)
			{
				for (size_t r = 1; r < order; r++)
				{
					for (size_t i = j - order + r + 1; i <= j; i++)
					{
						matrix[lineIter][r][i] = ((t - knot[i]) / (knot[i + order - r] - knot[i]))*matrix[lineIter][r - 1][i] +
							((knot[i + order - r] - t) / (knot[i + order - r] - knot[i]))*matrix[lineIter][r - 1][i - 1];
					}
				}
			}


		}
	}*/
	return ret;
}