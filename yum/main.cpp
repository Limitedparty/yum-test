#include <iostream>
#include <GL\freeglut.h>
#include <GL\gl.h>
#include <GL\glu.h>

const int size_x = 640;
const int size_y = 640;
float cubesize = 0.003125f;//0.003125
int windowx = 1000;
int windowy = 1000;
int i[size_x][size_y];

int random(int min, int max) {
	return min + (rand() % (int)(max - min + 1));
}

void remassive() {
	for (int l = size_y; l > 0; l = l - 1) {
		for (int d = size_x; d > 0; d = d - 1) {
			i[d][l] = random(0, 10);
		}
	}
}

void recalc() {
	for (int l = size_y; l > 0; l = l - 1) {
		for (int d = size_x; d > 0; d = d - 1) {
				//i[d][l] = i[d][l - 1];
				//i[1][1] = i[size_x][size_y];
		}
		i[random(1, size_x)][random(1, size_y)] = 0;
	}
	i[random(1, 160)][random(1, 160)] = 0;
}

void display_cube(float x, float y, float color) {
	glBegin(GL_QUADS);
	if (color == 11) {
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else {
		glColor3f(color / 10, color / 10, color / 10);
	}
	glVertex3f		(-1 - 0.1 + (cubesize * x), 1 + 0.1 - (cubesize * y), 0.0);
	glVertex3f(-1 - 0.1 + (cubesize * x), 0.9 + 0.1 - (cubesize * y), 0.0);
	glVertex3f(-0.9 - 0.1 + (cubesize * x), 0.9 + 0.1 - (cubesize * y), 0.0);
	glVertex3f(-0.9 - 0.1 + (cubesize * x), 1 + 0.1 - (cubesize * y), 0.0);
	glEnd();
}

void display_massive() {
	for (int l = size_y; l > 0; l = l - 1) {
		for (int d = size_x; d > 0; d = d - 1) {
			display_cube(d, l, i[d][l]);
		}
	}
}

void renderScene(void) {
	while (true) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//remassive();
		recalc();
		display_massive();
		glutSwapBuffers();
	}
}

int main(int argc, char **argv) {
	std::cout << "Yum experiment started" << std::endl;
	remassive();
	// инициализация
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowx, windowy);
	glutCreateWindow("yum experiment");

	// регистрация обратных вызовов
	glutDisplayFunc(renderScene);

	// Основной цикл GLUT
	glutMainLoop();

	return 1;
}