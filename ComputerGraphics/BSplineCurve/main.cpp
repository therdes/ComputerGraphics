#include "BSplineCurve.h"
#include <utility>

#define USEOPENGL 1
#define SURFACE 0

using std::vector;
using std::move;

#if USEOPENGL
#include <GL\glut.h>

#if SURFACE
void init();
void reshape(GLsizei, GLsizei);
void mouse(int, int, int, int);
void timer(int);
void motion(int, int);
bool mouseisdown = false;
bool loopr = false;
int mx, my;
int ry = 0;
int rx = 0;

GLfloat ctrlpoints[4][4][3]= {
	{
		{ -1.5, -1.5, 4.0 },{ -0.5, -1.5, 2.0 },
		{ 0.5, -1.5, -1.0 },{ 1.5, -1.5, 2.0 }
	},
	{
		{ -1.5, -0.5, 1.0 },{ -0.5, -0.5, 3.0 },
		{ 0.5, -0.5, 0.0 },{ 1.5, -0.5, -1.0 }
	},
	{
		{ -1.5, 0.5, 4.0 },{ -0.5, 0.5, 0.0 },
		{ 0.5, 0.5, 3.0 },{ 1.5, 0.5, 4.0 }
	},
	{
		{ -1.5, 1.5, -2.0 },{ -0.5, 1.5, -2.0 },
		{ 0.5, 1.5, 0.0 },{ 1.5, 1.5, -1.0 }
	}
};
#endif

template <typename BSplineType>
void displayHelp(const BSplineType&, const vector<double>&);

#endif

void display();

int main(int argc, char** argv)
{
#if USEOPENGL
	glutInit(&argc, argv);

#if SURFACE
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
#else
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
#endif

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("BSpline Curve");

#if SURFACE
	init();
	glutReshapeFunc(reshape);
	glutMouseFunc(mouse);
	glutMotionFunc(motion);
#endif

	glutDisplayFunc(display);
	glutMainLoop();

#else

	display();

#endif

	return 0;
}

void display()
{
	vector<Coordinate> test_case1{
		Coordinate(1, 1, 0), Coordinate(2, 2, 0),
		Coordinate(3, 2, 0), Coordinate(4, 1, 0)
	};
	vector<double> knot_case_1{ 0,1,2,3,4,5,6 };

	vector<Coordinate> test_case2{
		Coordinate(1, 1, 0), Coordinate(2.5, 3, 0),
		Coordinate(3.1, 1, 0), Coordinate(4.5, 2.9, 0)
	};

	vector<vector<Coordinate>> test_case_surface{
		{
			{ 1,1,0 },{ 2,1,0 },{ 3,1,0 },{ 4,1,0 }
		},
		{
			{ 0,2,0 },{ 2,2,0 },{ 3,2,0 },{ 4,2,0 }
		},
		{
			{ 1,3,0 },{ 2,3,0 },{ 3,3,0 },{ 5,3,0 }
		},
		{
			{ 1,4,0 },{ 2,4,0 },{ 3,4,0 },{ 4,4,0 }
		}
	};

	vector<vector<Coordinate>> sample{
		{
			{ -1.5, -1.5, 4.0 },{ -0.5, -1.5, 2.0 },
			{ 0.5, -1.5, -1.0 },{ 1.5, -1.5, 2.0 }
		},
		{
			{ -1.5, -0.5, 1.0 },{ -0.5, -0.5, 3.0 },
			{ 0.5, -0.5, 0.0 },{ 1.5, -0.5, -1.0 }
		},
		{
			{ -1.5, 0.5, 4.0 },{ -0.5, 0.5, 0.0 },
			{ 0.5, 0.5, 3.0 },{ 1.5, 0.5, 4.0 }
		},
		{
			{ -1.5, 1.5, -2.0 },{ -0.5, 1.5, -2.0 },
			{ 0.5, 1.5, 0.0 },{ 1.5, 1.5, -1.0 }
		}
	};

#if USEOPENGL

#if SURFACE
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glLoadIdentity();
	glRotatef(ry, 0, 1, 0);
	glRotatef(rx, 1, 0, 0);

#endif

#if SURFACE
#else
	displayHelp(test_case2, knot_case_1);
#endif

#if SURFACE

	glFlush();
	glutSwapBuffers();
#endif

#else
	BSplineCurve curve(test_case1, knot_case_1);
	auto ret = curve.deBoor();
#endif
}

#if USEOPENGL

#if SURFACE
void init()
{
	glEnable(GL_DEPTH_TEST);

	GLfloat position[] = { 1,1,1,0 };
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);

	GLfloat ambient[] = { 0,0,0,1 };
	GLfloat diffuse[] = { 0.25f,0.95f,0.5f,1.0f };
	GLfloat specular[] = { 1,1,1,1 };

	glMaterialfv(GL_FRONT, GL_AMBIENT, ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specular);
	glMaterialf(GL_FRONT, GL_SHININESS, 50);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_AUTO_NORMAL);
	glMapGrid2f(20, 0, 1, 20, 0, 1);
}

void reshape(GLsizei w, GLsizei h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-4, 4, -4 * h / w, 4 * h / w, -4, 4);
	glMatrixMode(GL_MODELVIEW);
}

void mouse(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			mouseisdown = true;
			loopr = false;
			mx = x;
			my = y;
		}
		else
			mouseisdown = false;

	}

	if (button == GLUT_RIGHT_BUTTON)
		if (state == GLUT_DOWN)
		{
			loopr = true;
			glutTimerFunc(200, timer, 0);
		}
}

void timer(int p)
{
	ry -= 5;
	glutPostRedisplay();
	if (loopr)
		glutTimerFunc(200, timer, 0);
}

void motion(int x, int y)
{
	if (mouseisdown == true)
	{
		ry += x - mx;
		rx += y - my;
		mx = x;
		my = y;
		glutPostRedisplay();
	}
}
#endif

#if !SURFACE
template <typename BSplineType>
void displayHelp(const BSplineType& vertexes, const vector<double>& knot)
{
	gluOrtho2D(0, 5, 0, 5);

	glPointSize(5);
	glBegin(GL_POINTS);
	for (auto coor : vertexes)
		glVertex3f(coor.x(), coor.y(), coor.z());
	glEnd();
	glFlush();

	BSplineCurve curve(vertexes);
	auto ret = curve.deBoor();

	glPointSize(1);
	glBegin(GL_LINE_STRIP);
	for (auto coor : ret)
		glVertex3f(coor.x(), coor.y(), coor.z());
	glEnd();
	glFlush();
}
#endif

#endif
