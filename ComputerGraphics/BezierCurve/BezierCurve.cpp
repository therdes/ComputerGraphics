#include "BezierCurve.h"
#include <utility>

using std::vector;
using std::move;

vector<Coordinate> BezierCurve::deCasteljau()
{
	if (conType == ConstructType::LINE)
		return move(deCasteljauLine());
	else if (conType == ConstructType::SURFACE)
		return move(deCasteljauSurface());
	else
		return move(vector<Coordinate>());
}

vector<Coordinate> BezierCurve::deCasteljauLine()
{
	using IterVertex = vector<Coordinate>;
	using IterMatrix = vector<IterVertex>;

	vector<Coordinate> ret;

	IterMatrix matrix(vertexSetLine.size());
	for (size_t i = 0; i < matrix.size(); i++)
		matrix[i] = IterVertex(vertexSetLine.size());

	for (size_t i = 0; i < vertexSetLine.size(); i++)
		matrix[0][i] = vertexSetLine[i];

	for (double t = 0; t <= 1; t += stepBy)
	{
		for (size_t i = 1; i < vertexSetLine.size(); i++)
		{
			for (size_t j = 0; j < vertexSetLine.size() - i; j++)
			{
				matrix[i][j] = (1 - t) * matrix[i - 1][j] + t * matrix[i - 1][j + 1];
			}
		}
		ret.push_back(matrix[vertexSetLine.size() - 1][0]);
	}

	return move(ret);
}

vector<Coordinate> BezierCurve::deCasteljauSurface()
{
	vector<Coordinate> ret;

	using IterVertex = vector<Coordinate>;
	using IterLineMatrix = vector<IterVertex>;
	using IterSurfaceMatrix = vector<IterLineMatrix>;

	const size_t numLineOfSurface = vertexSetSurface.size();
	size_t max = 0;
	for (auto matrix : vertexSetSurface)
		if (matrix.size() > max)
			max = matrix.size();
	const size_t numPointOfLine = max;

	IterSurfaceMatrix matrix(numLineOfSurface);
	for (size_t i = 0; i < numLineOfSurface; i++)
	{
		matrix[i] = IterLineMatrix(numPointOfLine);
		for (size_t j = 0; j < numPointOfLine; j++)
			matrix[i][j] = IterVertex(numPointOfLine);
	}

	for (size_t i = 0; i < numLineOfSurface; i++)
		for (size_t j = 0; j < vertexSetSurface[i].size(); j++)
			matrix[i][0][j] = vertexSetSurface.at(i).at(j);

	for (double u = 0; u <= 1; u += stepBy)
	{
		for (double v = 0; v <= 1; v += stepBy)
		{
			for (size_t i = 0; i < numLineOfSurface; i++)
			{
				for (size_t j = 1; j < vertexSetSurface[i].size(); j++)
				{
					for (size_t k = 0; k < vertexSetSurface[i].size() - j; k++)
					{
						matrix[i][j][k] = (1 - v) * matrix[i][j - 1][k] + v * matrix[i][j - 1][k + 1];
					}
				}
			}

			IterLineMatrix matrixIR(numLineOfSurface);
			for (auto& line : matrixIR)
				line = IterVertex(numLineOfSurface);
			for (size_t i = 0; i < numLineOfSurface; i++)
				matrixIR[0][i] = matrix[i][matrix[i].size() - 1][0];

			for (size_t i = 1; i < numLineOfSurface; i++)
				for (size_t j = 0; j < numLineOfSurface - i; j++)
					matrixIR[i][j] = (1 - u) * matrixIR[i - 1][j] + u * matrixIR[i - 1][j + 1];

			ret.push_back(matrixIR[numLineOfSurface - 1][0]);
		}
	}

	return move(ret);
}