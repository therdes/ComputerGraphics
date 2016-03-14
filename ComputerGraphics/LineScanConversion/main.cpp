#include "Line.h"
#include <vector>

#define USEOPENGL 1

using std::vector;

#if USEOPENGL
#include <GL\glut.h>

void displayHelp();
#endif

void display();

Coordinate coor1(0, 0, 0);
Coordinate coor2(5, 2, 0);
Coordinate coor3(2, 5, 0);

Coordinate coor4(-2, 4, 0);
Coordinate coor5(1, 2, 0);

int main(int argc, char** argv)
{
#if USEOPENGL
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Line ScanLine Fill");
	glutDisplayFunc(display);

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
#if USEOPENGL
	displayHelp();
#else
	Line line(coor1, coor2);
	auto ret = line.scanConversion();
#endif
}

#if USEOPENGL
void displayHelp()
{
	gluOrtho2D(-6, 6, -6, 6);

	Line line(coor4, coor1);
	auto ret = line.scanConversion();

	glBegin(GL_POINTS);
	for (auto iter = ret.begin(); iter != ret.end(); iter += 1)
		glVertex3f(iter->x(), iter->y(), 0);
	glEnd();
	glFlush();
}
#endif
