#include <GL\glut.h>
#include <random>
#include <Windows.h>
#include <float.h>
#include <cmath>
#include <utility>

const int dimension = 2;
const float init_speed = 10;
const int x_dimension = 0;
const int y_dimension = 1;
const bool gravity = false;

#if dimension == 3
const int z_dimension = 2;
#endif

const float coef = 0.9;

const int particle_size = 5;
struct Particle
{
	int color;
	float position[dimension];
	float velocity[dimension];

	float mass;
};

const GLfloat colors[][3] = {
	{ 0,0,0 },
	{ 0,0,1 },
	{ 0,1,0 },
	{ 0,1,1 },
	{ 1,0,0 },
	{ 1,0,1 },
	{ 1,1,0 },
	{ 1,1,1 }
};

const int num_particle = 5;
const int space_size = 10;
Particle particles[num_particle];

//double distances[num_particle][num_particle];

float last_time = 0;
float present_time;

void myInit();
void myDisplay();
void myIdle();
float forces(int, int);
void collision(int);
//void collision_between_particles();
//void update_distance();
//double distance(const float*, const float*);

int main(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

	glutInitWindowSize(500, 500);
	glutInitWindowPosition(0, 0);

	glutCreateWindow("Particle System");

	glutDisplayFunc(myDisplay);
	glutIdleFunc(myIdle);

	myInit();

	glutMainLoop();

	return 0;
}

void myInit()
{
	glPointSize(particle_size);

	gluOrtho2D(-space_size, space_size, -space_size, space_size);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glMatrixMode(GL_MODELVIEW);

	for (int i = 0; i < num_particle; i++)
	{
		particles[i].mass = 1;
		particles[i].color = i % 8;

		for (int j = 0; j < dimension; j++)
		{
			particles[i].position[j] = 20 * ((float)rand() / RAND_MAX) - 10;
			particles[i].velocity[j] = init_speed *  2 * ((float)rand() / RAND_MAX) - 1;
		}
	}

	//update_distance();
}

void myDisplay()
{
	glClear(GL_COLOR_BUFFER_BIT);

	glBegin(GL_POINTS);
	for (int i = 0; i < num_particle; i++)
	{
		glColor3fv(colors[particles[i].color]);
		glVertex2fv(particles[i].position);
	}
	glEnd();

	glFlush();
}

void myIdle()
{
	present_time = glutGet(GLUT_ELAPSED_TIME);
	float dt = 0.001 * (present_time - last_time);

	Sleep(1);
	//collision_between_particles();
	for (int i = 0; i < num_particle; i++)
	{
		for (int j = 0; j < dimension; j++)
		{
			particles[i].position[j] += dt * particles[i].velocity[j];
			particles[i].velocity[j] += dt * forces(i, j) / particles[i].mass;
		}
		collision(i);
	}
	//update_distance();	

	last_time = present_time;

	glutPostRedisplay();
}

void collision(int n)
{
	for (int j = 0; j < dimension; j++)
	{
		if (particles[n].position[j] >= space_size)
		{
			particles[n].velocity[j] = -coef * particles[n].velocity[j];
			particles[n].position[j] =
				coef * (particles[n].position[j] - (/*1 * 0.001 * particles[n].velocity[j]*/0.001));
		}
		if (particles[n].position[j] <= -space_size)
		{
			particles[n].velocity[j] = -coef * particles[n].velocity[j];
			particles[n].position[j] =
				coef * (particles[n].position[j] + (/*1 * 0.001 * particles[n].velocity[j]*/0.001));
		}
	}
}

//void collision_between_particles()
//{
//	for (int i = 0; i < num_particle - 1; i++)
//	{
//		for (int j = i + 1; j < num_particle; j++)
//		{
//			if (distances[i][j] < particle_size)
//			{
//				std::swap(particles[i].velocity, particles[j].velocity);
//			}
//		}
//	}
//}

float forces(int i, int j)
{
	if (!gravity)
		return(0.0);
	else if (j == y_dimension)
		return (-1);
	else return(0, 0);
}

//double distance(const float* a, const float* b)
//{
//	float x_diff = pow(b[x_dimension] - a[x_dimension], 2);
//	float y_diff = pow(b[y_dimension] - a[y_dimension], 2);
//
//	return sqrt(x_diff + y_diff);
//}
//
//void update_distance()
//{
//	for (int i = 0; i < num_particle - 1; i++)
//	{
//		for (int j = i + 1; j < num_particle; j++)
//		{
//			distances[i][j] = distance(particles[i].position, particles[j].position);
//		}
//	}
//}