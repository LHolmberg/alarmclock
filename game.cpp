#include "pch.h"
#include <GL/glut.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>

#define _USE_MATH_DEFINES

using namespace std;

double AABB(float dx, float dy, float dz) {
	return sqrt(dx * dx + dy * dy + dz * dz);
}

float Xpos, Ypos, Zpos, Xrot, Yrot, Zrot, XrotRad, YRotRad,
			vel, sens, CubePositionsX[1], CubePositionsZ[1], 
				CubePositionsD[1], CubePositionsB[1], CubePos,
					dx, dy, dz, dx2, dz2, dy2, dx3, dz3, dy3;

bool colliding, f, b, r, l, x, x2, x3, x4, moveForward, moveBack,
			moveLeft, moveRight, abletojump, cube1, cube2,
				cube3, cube4, cube5, cube6;


struct Player {
	void Forward(void) {
		YRotRad = (Yrot / 180 * 3.14);
		XRotRad = (Xrot / 180 * 3.14);
		Xpos += float(sin(YRotRad)) * vel;
		Zpos -= float(cos(YRotRad)) * vel;
	}

	void Back(void) {
		YRotRad = (Yrot / 180 * 3.14);
		XRotRad = (Xrot / 180 * 3.14);
		Xpos -= float(sin(YRotRad)) * vel;
		Zpos += float(cos(YRotRad)) * vel;
	}

	void Right(void) {
		YRotRad = (Yrot / 180 * 3.14);
		Xpos += float(cos(YRotRad)) * vel;
		Zpos += float(sin(YRotRad)) * vel;
	}

	void Left(void) {
		YRotRad = (Yrot / 180 * 3.14);
		Xpos -= float(cos(YRotRad)) * vel;
		Zpos -= float(sin(YRotRad)) * vel;
	}

	void Camera(void) {

		if (moveForward)
			Forward();

		if (moveBack)
			Back();

		if (moveLeft)
			Left();

		if (moveRight)
			Right();

		glRotatef(Xrot, 1.0, 0.0, 0.0);
		glRotatef(Yrot, 0.0, 1.0, 0.0);
		glTranslated(-Xpos, -Ypos, -Zpos);

		if (Xrot <= -89) {
			Xrot = -89;
		}

		if (Xrot >= 89) {
			Xrot = 89;
		}
	}

	void input() {
		int res = glfwJoystickPresent(GLFW_JOYSTICK_1);
		int btnCount;
		const unsigned char* buttons = glfwGetJoystickButtons(GLFW_JOYSTICK_1, &btnCount);
		int count;
		const float* axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &count);
		if (glfwGetJoystickButtons)
			if (res == 1) {
				if (axes[1] <= -0.45f) {
					f = true;
				}
				else {
					f = false;
				}
				if (f == true) {
					moveForward = true;
				}
				else if (f != true) {
					moveForward = false;
				}
				if (axes[1] >= 0.45f) {
					r = true;
				}
				else {
					r = false;
				} if (r == true) {
					moveBack = true;
				}
				else if (r != true) {
					moveBack = false;
				}
				if (axes[0] <= -0.45f) {
					l = true;
				}
				else {
					l = false;
				}
				if (l == true) {
					moveLeft = true;
				}
				else if (l != true) {
					moveLeft = false;
				}
				if (axes[0] >= 0.45f) {
					r = true;
				}
				else {
					r = false;
				}
				if (r == true) {
					moveRight = true;
				}
				else if (r != true) {
					moveRight = false;
				}
				if (axes[2] >= 0.45f) {
					x = true;
				}
				else { x = false; }
				if (x == true) {
					Yrot += 8 * sens;
				}
				if (axes[2] <= -0.45f) {
					x2 = true;
				}
				else { x2 = false; }
				if (x2 == true) {
					Yrot += -8 * sens;
				}
				if (axes[3] >= 0.45f) {
					x3 = true;
				}
				else { x3 = false; }
				if (x3 == true) {
					Xrot += 8 * sens;
				}
				if (axes[3] <= -0.45f) {
					x4 = true;
				}
				else { x4 = false; }
				if (x4 == true) {
					Xrot += -8 * sens;
				}
				if (GLFW_PRESS == buttons[1] && abletojump == true) {
					Ypos += 20;
					abletojump = false;
				}
				if (GLFW_RELEASE == buttons[1]) {
					abletojump = true;
				}
				glfwPollEvents();
			}
	}
};

struct Objects {
	void DrawCube2(void) {
		glColor3f(0.1, 0.25, 0.25);
		glPushMatrix();
		glTranslated(25, Ypos - 4, -0);
		glScaled(150, 0.5f, 150);
		glutSolidCube(1);
		glPopMatrix();
	}


	void DrawCubes(void) {
		if (cube1) {
			glColor3f(1, 0.5, 0);
			glPushMatrix();
			glTranslated(12, 3, -25);
			glScaled(1, 9, 1);
			glutSolidCube(3);
			glPopMatrix();
			glColor3f(0.04f, 0.7, 0.6);
		}
		glutSolidCube(0);

	}
	
	void DrawCube3(void) {
		if (cube2) {
			glColor3d(0.67, 0.21, 0.5);
			glPushMatrix();
			glTranslated(10, 0, 4);
			glutSolidCube(4);
			glPopMatrix();
		}
		glutSolidCube(0);
	}
	void DrawCube4(void) {
		if (cube3) {
			glColor3f(0.2, 0.5, 0);
			glPushMatrix();
			glTranslated(23, 0, 8);
			glScaled(1, 3, 1);
			glutSolidCube(3);
			glPopMatrix();
			glColor3f(0.04f, 0.7, 0.6);
		}
		glutSolidCube(0);
	}

	void DrawCube5(void) {
		if (cube4) {
			glColor3f(0.2, 0.333, 0);
			glPushMatrix();
			glTranslated(45, 0, 25);
			glScaled(2, 1, 2);
			glutSolidCube(3);
			glPopMatrix();
			glColor3f(0.04f, 0.7, 0.6);
		}
		glutSolidCube(0);

	}

	void DrawCube6(void) {
		if (cube5) {
			glColor3f(1, 0.333, 0.2);
			glPushMatrix();
			glTranslated(73, 0, -35);
			glScaled(2, 12, 2);
			glutSolidCube(3);
			glPopMatrix();
			glColor3f(0.04f, 0.7, 0.6);
		}
		glutSolidCube(0);
	}

	void DrawCube7(void) {
		if (cube6) {
			glColor3f(1, 1, 0.5);
			glPushMatrix();
			glTranslated(90, 0, -55);
			glScaled(3, 2, 3);
			glutSolidCube(3);
			glPopMatrix();
			glColor3f(0.04f, 0.7, 0.6);
		}
		glutSolidCube(0);
	}
};

void exit() {
	if (!cube1 && !cube2 && !cube3 && !cube4 && !cube5 && !cube6) {
		glutDestroyWindow(glutGetWindow());
	}
}

Objects obj;
Player pl;
void Physics() {
	float distance2 = AABB(Xpos - 10, Ypos - 0, Zpos - 4);

	if (distance2 <= (2.5 + 2.5) && time > 2) {
		cout << "Colliding" << endl;
		cube2 = false;
	}

	float distance = AABB(Xpos - 12, Ypos - 3, Zpos - (-25));
	if (distance <= (2.5 + 2.5) && time > 2) {
		cout << "Colliding" << endl;
		cube1 = false;
	}
	float distance3 = AABB(Xpos - 23, Ypos - 0, Zpos - 8);
	if (distance3 <= (2.5 + 2.5)) {
		cout << "col" << endl;
		cube3 = false;
	}

	float distance4 = AABB(Xpos - 45, Ypos - 0, Zpos - 25);
	if (distance4 <= (2.5 + 3.5)) {
		cout << "col" << endl;
		cube4 = false;
	}

	float distance5 = AABB(Xpos - 73, Ypos - 0, Zpos - (-35));
	if (distance5 <= (2.5 + 2.5)) {
		cout << "col" << endl;
		cube5 = false;
	}

	float distance6 = AABB(Xpos - 90, Ypos - 0, Zpos - (-55));
	if (distance6 <= (4 + 4)) {
		cout << "col" << endl;
		cube6 = false;
	}
}

void Enables(void) {
	glEnable(GL_DEPTH_TEST);
	//glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_COLOR_MATERIAL);
}


void Render(void) {
	glMatrixMode(GL_MODELVIEW);
	glClearColor(0.20, 0.20, 0.20, 1.0);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	pl.Camera();
	Enables();
	exit();
	Physics();
	obj.DrawCube6();
	obj.DrawCube7();
	obj.DrawCubes();
	obj.DrawCube3();
	obj.DrawCube4();
	obj.DrawCube5();
	time += glfwGetTime();
	obj.DrawCube2();
	pl.input();
	glutSwapBuffers();
}

void Window(int w, int h) {
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60, (GLfloat)w / (GLfloat)h, 1.0, 10000.0);
	glMatrixMode(GL_MODELVIEW);
}

int main(int argc, char** argv) {
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH);
	glutInitWindowSize(1500, 900);
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OPENGLGAME");

	glfwInit();
	Xrot = 0;
	Yrot = 765;
	Xpos = -23;
	Ypos = 2;
	Zpos = 30;
	while (true) {
		glutDisplayFunc(Render);
		glutIdleFunc(Render);
		glutReshapeFunc(Window);
		glutMainLoop();
	}
	return 0;
}
