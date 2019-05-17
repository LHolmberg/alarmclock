#include <GL/glut.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
#include <vector>

#define _USE_MATH_DEFINES

using namespace std;

float Xposition;
float Yposition;
float Zposition;
float Xrotation;
float Yrotation;
float Zraotaion;
float XRotationRadius;
float YRotationRadius;
float vel = 0.03f;
float sens = 0.026f;
float CubePositionsX[1];
float CubePositionsZ[1];
float CubePositionsD[1];
float CubePositionsB[1];
float CubePos;

float dx;
float dy;
float dz;
float dx2;
float dz2;
float dy2;
float dx3;
float dz3;
float dy3;
float time;

bool colliding;
bool f = false;
bool b = false;
bool r = false;
bool l = false;
bool x = false;
bool x2 = false;
bool x3 = false;
bool x4 = false;
bool moveForward = false;
bool moveBack = false;
bool moveLeft = false;
bool moveRight = false;
bool abletojump;
bool cube1 = true;
bool cube2 = true;
bool cube3 = true;
bool cube4 = true;
bool cube5 = true;
bool cube6 = true;

typedef vector<vector<vector<double>>> Vector3D;


struct Math {
	float x;
	float y;
	float z;
	float dx;
	float dy;
	float dz;

	//vector 3
	Math(float _x, float _y, float _z) {
		_x = x;
		_y = y;
		_z = z;
	}
	//vector 2
	Math(float _x, float _y) {
		_x = x;
		_y = y;
	}

	//sqrt(dx * dx + dy * dy + dz * dz);                   roten ur dx^2 + dy^2 + dz^2  dx + dy + dz

};

double AABB(float dx, float dy, float dz) {
	return sqrt(dx * dx + dy * dy + dz * dz);
}

struct Player {
	void Forward(void) {

		YRotationRadius = (Yrotation / 180 * 3.14);
		XRotationRadius = (Xrotation / 180 * 3.14);

		Xposition += float(sin(YRotationRadius)) * vel;
		Zposition -= float(cos(YRotationRadius)) * vel;
	}

	void Back(void) {
		YRotationRadius = (Yrotation / 180 * 3.14);
		XRotationRadius = (Xrotation / 180 * 3.14);
		Xposition -= float(sin(YRotationRadius)) * vel;
		Zposition += float(cos(YRotationRadius)) * vel;
	}

	void Right(void) {

		YRotationRadius = (Yrotation / 180 * 3.14);

		Xposition += float(cos(YRotationRadius)) * vel;
		Zposition += float(sin(YRotationRadius)) * vel;

	}

	void Left(void) {

		YRotationRadius = (Yrotation / 180 * 3.14);
		Xposition -= float(cos(YRotationRadius)) * vel;
		Zposition -= float(sin(YRotationRadius)) * vel;

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

		glRotatef(Xrotation, 1.0, 0.0, 0.0);
		glRotatef(Yrotation, 0.0, 1.0, 0.0);
		glTranslated(-Xposition, -Yposition, -Zposition);

		if (Xrotation <= -89) {
			Xrotation = -89;
		}

		if (Xrotation >= 89) {
			Xrotation = 89;
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
					Yrotation += 8 * sens;
				}
				if (axes[2] <= -0.45f) {
					x2 = true;
				}
				else { x2 = false; }
				if (x2 == true) {
					Yrotation += -8 * sens;
				}
				if (axes[3] >= 0.45f) {
					x3 = true;
				}
				else { x3 = false; }
				if (x3 == true) {
					Xrotation += 8 * sens;
				}
				if (axes[3] <= -0.45f) {
					x4 = true;
				}
				else { x4 = false; }
				if (x4 == true) {
					Xrotation += -8 * sens;

				}
				if (GLFW_PRESS == buttons[1] && abletojump == true) {
					Yposition += 20;
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
	void DrawCube2(void) {
		glColor3f(0.1, 0.25, 0.25);
		glPushMatrix();
		glTranslated(25, Yposition - 4, -0);
		glScaled(150, 0.5f, 150);
		glutSolidCube(1);
		glPopMatrix();
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
	float distance2 = AABB(Xposition - 10, Yposition - 0, Zposition - 4);

	if (distance2 <= (2.5 + 2.5) && time > 2) {
		cout << "Colliding" << endl;
		cube2 = false;
	}

	float distance = AABB(Xposition - 12, Yposition - 3, Zposition - (-25));
	if (distance <= (2.5 + 2.5) && time > 2) {
		cout << "Colliding" << endl;
		cube1 = false;
	}
	float distance3 = AABB(Xposition - 23, Yposition - 0, Zposition - 8);
	if (distance3 <= (2.5 + 2.5)) {
		cout << "col" << endl;
		cube3 = false;
	}

	float distance4 = AABB(Xposition - 45, Yposition - 0, Zposition - 25);
	if (distance4 <= (2.5 + 3.5)) {
		cout << "col" << endl;
		cube4 = false;
	}

	float distance5 = AABB(Xposition - 73, Yposition - 0, Zposition - (-35));
	if (distance5 <= (2.5 + 2.5)) {
		cout << "col" << endl;
		cube5= false;
	}

	float distance6 = AABB(Xposition - 90, Yposition - 0, Zposition - (-55));
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
	Xrotation = 0;
	Yrotation = 765;
	Xposition = -23;
	Yposition = 2;
	Zposition = 30;
	while (true) {
		glutDisplayFunc(Render);
		glutIdleFunc(Render);
		glutReshapeFunc(Window);
		glutMainLoop();
	}
	return 0;
}

//SAKER ATT FIXA:
//collision
//jump
