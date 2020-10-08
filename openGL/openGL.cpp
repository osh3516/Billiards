#include <GL/glut.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <math.h>
#include<stdio.h>

GLfloat x, y, a, b, start = 0; 
GLfloat dx, da, dy, db;
GLfloat xDir, yDir, aDir, bDir; 

//흰 공 
void DrawCircle(float cx, float cy, float r)
{
	float x1, y1, x2, y2;
	float angle;
	double radius = r;
	x1 = cx, y1 = cy;
	glColor3f(1.0, 1.0, 1.0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);
	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glEnd();

}

//빨간 공
void DrawCircle2(float cx, float cy, float r)
{
	float x1, y1, x2, y2;
	float angle;
	double radius = r;
	x1 = cx, y1 = cy;
	glColor3f(1.0, 0, 0);
	glBegin(GL_TRIANGLE_FAN);
	glVertex2f(x1, y1);

	for (angle = 1.0f; angle < 361.0f; angle += 0.2)
	{
		x2 = x1 + sin(angle)*radius;
		y2 = y1 + cos(angle)*radius;
		glVertex2f(x2, y2);
	}
	glEnd();
}

//흰 공의 움직임
void moveAndDraw() {
	dx -= 0.00005;
	dy -= 0.00005;  
	x += xDir * dx; 
	y += yDir * dy;

	if ((xDir < 0 && x < -0.9) || (xDir > 0 && x > 0.9)) {
		xDir = -xDir;
	}
	if ((yDir < 0 && y < -1.9) || (yDir > 0 && y > 1.9)) { 
		yDir = -yDir;
	}
}

//빨간 공의 움직임
void moveAndDraw2() {
	da -= 0.00005;
	db -= 0.00005; 
	a += aDir * da;
	b += bDir * db;

	if ((aDir < 0 && a < -0.9) || (aDir > 0 && a > 0.9)) {
		aDir = -aDir; 
	}
	if ((bDir < 0 && b < -1.9) || (bDir > 0 && b > 1.9)) { 
		bDir = -bDir;
	}
}

void MyDisplay() {
	if (start == 1) {//적구가 움직이기 시작
		if (sqrt((x - a)*(x - a) + (y - b)*(y - b)) <= 0.21&&da < 0.025) return;

		moveAndDraw();
		moveAndDraw2();
		glClear(GL_COLOR_BUFFER_BIT); // 전에 있는 원의 흔적을 지운다.
		DrawCircle(x + dx, y + dy, 0.1);
		DrawCircle2(a + da, b + db, 0.1);
		glEnd();
		glutSwapBuffers();
	}

	else {
		moveAndDraw();
		glClear(GL_COLOR_BUFFER_BIT); // 전에 있는 원의 흔적을 지운다.
		DrawCircle(x + dx, y + dy, 0.1);
		DrawCircle2(a + da, b + db, 0.1);
		glEnd();
		glutSwapBuffers();
		if (sqrt((x - a)*(x - a) + (y - b)*(y - b)) <= 0.21) {
			start = 1;
			aDir = -0.5;
			bDir = sqrt(3) / 2;
			xDir = sqrt(3) / 2;
			yDir = 0.5;
		}
	}
}

void MyTimer(int Value) {

	glutPostRedisplay();
	glutTimerFunc(10, MyTimer, 1);
}

int main(int argc, char** argv) {

	//수구 원의 초기 위치 값
	x = 0;
	y = -1;

	//수구 원의 이동 속도
	dx = 0.03;
	dy = 0.03;

	//수구 이동 방향
	xDir = 0;
	yDir = 1;

	//적구 원의 초기 위치 값
	a = 0;
	b = 1;

	//적구 원의 이동 속도
	da = 0.03;
	db = 0.03;

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(300, 600); 
	glutInitWindowPosition(100, 0);
	glutCreateWindow("당구공 애니매이션");
	glClearColor(0.2, 0.58, 0.2, 1.0); 
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-1.0, 1.0, -2.0, 2.0, 1.0, -1.0); 
	glutDisplayFunc(MyDisplay);
	glutTimerFunc(40, MyTimer, 1);
	glutMainLoop();
	return 0;

}
