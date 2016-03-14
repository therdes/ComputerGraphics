#include "PolygonScanConversion.h"
#include "../Include/Coordinate.h"
#include "../Include/Utils.h"
#include <vector>
#include <algorithm>
#include <functional>

#define USEOPENGL 1

using std::vector;
using std::find_if;
using std::unary_function;
using std::binary_function;

#if USEOPENGL
#include <GL\glut.h>

void displayHelp(const vector<Coordinate>&, double);

void z_buffer_display();
vector<Coordinate>::const_iterator findCurPoint(const vector<Coordinate>&, const Coordinate&);
#endif

void display();

int main(int argc, char** argv)
{
#if USEOPENGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Polygon ScanLine Fill");
	glutDisplayFunc(z_buffer_display);

	glClearColor(1, 1, 1, 1);
	glColor3f(1, 0, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);
	
	glutMainLoop();

#else

	display();

#endif

	return 0;
}

void display()
{
	vector<Coordinate> test_case1{
		Coordinate(2,2,0), Coordinate(2,7,0), Coordinate(5,5,0), Coordinate(11,8,0),
		Coordinate(11,3,0), Coordinate(5,1,0)
	};
	vector<Coordinate> test_case2{
		Coordinate(3,4,0), Coordinate(2,10,0), Coordinate(5,7,0), Coordinate(12,11,0),
		Coordinate(15,5,0), Coordinate(12,2,0), Coordinate(7,2,0)
	};
	vector<Coordinate> test_case3{
		Coordinate(2.5,2.5,0), Coordinate(4,6,0), Coordinate(7,9,0), Coordinate(9,8,0),
		Coordinate(7,5,0), Coordinate(9,5,0), Coordinate(11,7,0), Coordinate(11,1,0),
		Coordinate(9,3,0), Coordinate(6,1,0)
	};

	vector<Coordinate> test_case4{
		Coordinate(0,6,7), Coordinate(0,1,2), Coordinate(5,1,7)
	};

	vector<Coordinate> test_case5{
		Coordinate(3,5,0), Coordinate(9,11,0), Coordinate(11,9,0),
		Coordinate(11,2,0), Coordinate(8,5,0), Coordinate(5,3,0),
		Coordinate(6,5,0)
	};

	vector<Coordinate> test_case_rectangle{
		Coordinate(0,0,0), Coordinate(0,-5,0),
		Coordinate(5,-5,0), Coordinate(5,0,0)
	};

	vector<Coordinate> test_case_rhombus{
		Coordinate(0,4,0), Coordinate(-4,0,0),
		Coordinate(0,-5,0), Coordinate(4,0,0)
	};

#if USEOPENGL
	displayHelp(test_case5, 0.1);
#else
	Polygon polygon(test_case_rectangle, 1);
	auto ret = polygon.ScanConversion();
#endif
}

#if USEOPENGL
void displayHelp(const vector<Coordinate>& vertexes, double s)
{
	gluOrtho2D(-15, 15, -15, 15);

	Polygon polygon(vertexes, s);
	auto ret = polygon.ScanConversion();

	glPointSize(1);
	glBegin(GL_POINTS);
	for (auto iter = ret.begin(); iter != ret.end(); iter += 1)
		glVertex3f(iter->x(), iter->y(), 0);
	glEnd();
	glFlush();
}

vector<Coordinate>::const_iterator findCurPoint(const vector<Coordinate>& polygon, const Coordinate& point)
{
	return find_if(polygon.begin(), polygon.end(),
		[point](const Coordinate& p)
	{
		if (doubleEqual(p.x(), point.x(), 0.0000001) &&
			doubleEqual(p.y(), point.y(), 0.0000001))
			return true;
		else
			return false;
	});
}

void z_buffer_display()
{
	const int x_len = 32;
	const int y_len = 32;

	gluOrtho2D(0-1, x_len+1, 0-1, y_len+1);

	vector<Coordinate> rectangle_case{
		Coordinate(10,5,10), Coordinate(10,25,10),
		Coordinate(25,25,10), Coordinate(25,5,10)
	};
	vector<Coordinate> triangle_case{
		Coordinate(15,15,15), Coordinate(25,25,5), Coordinate(30,10,5)
	};

	const int background_index = 0;
	const int rectangle_index = 1;
	const int triangle_index = 2;

	const double background = 30;

	GLfloat colors[][3] = {
		{ 1, 0, 0 },
		{ 0, 1, 0 },
		{ 0, 0, 1 }
	};

	int frameBuffer[y_len][x_len];
	for (int i = 0; i < y_len; i++)
		memset(frameBuffer[i], 0, x_len * sizeof(int));

	double depthBuffer[y_len][x_len];
	for (int i = 0; i < y_len; i++)
		for (int j = 0; j < x_len; j++)
			depthBuffer[i][j] = background;

	Polygon triangle(triangle_case, 1);
	auto triPoints = triangle.ScanConversion();
	Polygon rectangle(rectangle_case, 1);
	auto recPoints = rectangle.ScanConversion();

	for (int i = 0; i < y_len; i++)
	{
		for (int j = 0; j < x_len; j++)
		{
			auto recPoint = findCurPoint(recPoints, Coordinate(i, j, 0));
			if (recPoint != recPoints.end())
			{
				if (recPoint->z() < depthBuffer[i][j])
				{
					depthBuffer[i][j] = recPoint->z();
					frameBuffer[i][j] = rectangle_index;
				}
			}
		}
	}

	for (int i = y_len - 1; i >= 0; i--)
	{
		for (int j = 0; j < x_len; j++)
		{
			printf("%5.1f", depthBuffer[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');

	for (int i = 0; i < y_len; i++)
	{
		for (int j = 0; j < x_len; j++)
		{
			auto triPoint = findCurPoint(triPoints, Coordinate(i, j, 0));
			if (triPoint != triPoints.end())
			{
				if (triPoint->z() < depthBuffer[i][j])
				{
					depthBuffer[i][j] = triPoint->z();
					frameBuffer[i][j] = triangle_index;
				}
			}
		}
	}

	for (int i = y_len - 1; i >= 0; i--)
	{
		for (int j = 0; j < x_len; j++)
		{
			printf("%5.1f", depthBuffer[j][i]);
		}
		putchar('\n');
	}
	putchar('\n');

	glPointSize(2);
	glBegin(GL_POINTS);
	for (int i = 0; i < y_len; i++)
	{
		for (int j = 0; j < x_len; j++)
		{
			glColor3fv(colors[frameBuffer[i][j]]);
			glVertex3d(i, j, 0);
		}
	}
	glEnd();
	glFlush();
}
#endif