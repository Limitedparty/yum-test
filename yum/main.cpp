/* 
Yum-test experiment ヽ(･ω･ゞ)
OpenGL fun test. 
Created by @levohup
LP 2016.
*/

#include <iostream>
#include <GL\freeglut.h>
#include <GL\gl.h>
#include <GL\glu.h>

const int size_x = 640; // pixels count size for x
const int size_y = 640; // pixels count size for y
float cubesize = 0.003125f; // size of one pixel
int windowx = 1000; // window size
int windowy = 1000; // window size
int i[size_x][size_y]; // two dimensional matrix. array, where x, y - position on window, and value = aplha (0 - 10)

// Random intriger ruturn function. If you want best random - change it 
int random(int min, int max) {
	return min + (rand() % (int)(max - min + 1));
}

// Create new massive
void remassive() {
	for (int l = size_y; l > 0; l = l - 1) {
		for (int d = size_x; d > 0; d = d - 1) {
			i[d][l] = random(0, 10);
		}
	}
}

// Match function.
// You can change it for new fun effects
void recalc() {
	for (int l = size_y; l > 0; l = l - 1) {
		for (int d = size_x; d > 0; d = d - 1) {
				// Repeat effect
				/*i[d][l] = i[d][l - 1];
				i[1][1] = i[size_x][size_y];*/
				// Move right
				/*i[d][l] = i[d - 1][l];
				i[1][1] = i[size_x][size_y];*/
				// Move to lower right corner
				//i[d][l] = i[d - 1][l - 1];
		}
		// Random pixel remover
		i[random(1, size_x)][random(1, size_y)] = 0;
	}
	// create new cubes
	i[random(1, 160)][random(1, 160)] = 0;
}

// This function display ONE pixel (cube) on coords x y
void display_cube(float x, float y, float color) {
	glBegin(GL_QUADS);
	// set cube color
	if (color == 11) { // super color
		glColor3f(0.0f, 1.0f, 0.0f);
	}
	else { // simple color
		glColor3f(color / 10, color / 10, color / 10);
	}
	// create cube
	glVertex3f		(-1 - 0.1 + (cubesize * x), 1 + 0.1 - (cubesize * y), 0.0);
	glVertex3f(-1 - 0.1 + (cubesize * x), 0.9 + 0.1 - (cubesize * y), 0.0);
	glVertex3f(-0.9 - 0.1 + (cubesize * x), 0.9 + 0.1 - (cubesize * y), 0.0);
	glVertex3f(-0.9 - 0.1 + (cubesize * x), 1 + 0.1 - (cubesize * y), 0.0);
	glEnd();
}

// This loop display all pixels (cubes) on window from massive
void display_massive() {
	for (int l = size_y; l > 0; l = l - 1) {
		for (int d = size_x; d > 0; d = d - 1) {
			display_cube(d, l, i[d][l]);
		}
	}
}

// OpenGL function
void renderScene(void) {
	while (true) {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//remassive();
		recalc();
		display_massive();
		glutSwapBuffers();
	}
}

// MAIN.  ヘ(^0^)ヘ
int main(int argc, char **argv) {
	std::cout << "Yum experiment started" << std::endl;
	remassive();
	// init
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(windowx, windowy);
	glutCreateWindow("yum experiment");

	// Register return call
	glutDisplayFunc(renderScene);

	// Main while GLUT
	glutMainLoop();

	return 1;
}