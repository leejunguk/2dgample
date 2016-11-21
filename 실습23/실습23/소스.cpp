#include <gl/glut.h>
#include <time.h>
#include <math.h>
#include <iostream>// ��� ����
using namespace std;
// �ʿ��� ���� ���� ����
int KEY = 0;
int FlagX = 0;
int FlagY = 0;
int FlagZ = 0;
int FlagXCrane = 0;
int FlagYCrane = 0;
int FlagZCrane = 0;
int Camera = 0;
int STATE = 0;
int BOX = 0;
int TOP = 0;
int SECONDROTATE = 0;
int THIRDROTATE = 0;
int BlockRotate = 0;

struct Ball
{
	float x;
	float y;
	float z;
};


struct CollideBox
{
	float x;
	float y;
	float z;
	int size;
};
CollideBox* CollideLeftBox = new CollideBox;
CollideBox* CollideRightBox = new CollideBox;
CollideBox* CollideLEFTBOTTOMBox = new CollideBox;
CollideBox* CollideRIGHTBOTTOMBox = new CollideBox;
CollideBox* LeftTree = new CollideBox;
CollideBox* RightTree = new CollideBox;
Ball* ball = new Ball;
Ball* Crane = new Ball;

const int LEFT = 1;
const int RIGHT = 2;
const int FIRST = 1;
const int SECOND = 2;
const int THIRD = 3;
const int NORMAL = 0;
const int RESET = 77;

const int ZOOM = 1;
const int ZOOMOUT = 2;
static float view = 0;
const int KeyX = 1;
const int KeyY = 2;
const int KeyZ = 3;
const int KeyLeft = 4;
const int KeyRight = 5;
const int RotateZ = 6;
const int RotateY = 7;

const int MoveXPlus = 1;
const int MoveXMinus = 2;
const int MoveYPlus = 1;
const int MoveYMinus = 2;
const int MoveZPlus = 1;
const int MoveZMinus = 2;
const int MoveXStop = 3;
const int MoveYStop = 3;
const int MoveZStop = 3;

void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void Reshape(int w, int h);
void DrawScene();
void SetupRC();
void main()
{
	// ������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Points Drawing");
	// ���� ���� �ʱ�ȭ �Լ�
	SetupRC();
	glutDisplayFunc(DrawScene); // ��� �ݹ� �Լ�
	glutReshapeFunc(Reshape); // �ٽ� �׸��� �ݹ� �Լ�
	glutKeyboardFunc(Keyboard); // Ű���� �Է� �ݹ� �Լ�
	glutTimerFunc(100, TimerFunction, 1); // Ÿ�̸� �ݹ� �Լ�
	glutMainLoop(); // �̺�Ʈ ���� �����ϱ�
}
void SetupRC() {
	// �ʿ��� ������, ��ǥ�� ���� �ʱ�ȭ
	// ��� ���� �ʱ�ȭ
	/*ball->x = 0;
	ball->y = 0;
	ball->z = 0;*/
	Crane->x = 0; 0;
	Crane->y = 0;
	Crane->z = 0;
	/*LeftTree->x = 0;
	LeftTree->y = 0;
	LeftTree->z = 0;*/
	LeftTree->size = 0;
	srand(unsigned(time(NULL)));
}

// �������� ���� ���÷��� �ݹ� �Լ�: ��� �׸��� ����� �� �Լ����� ��κ� ó�� ��
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�
	glEnable(GL_DEPTH_TEST);
	glLoadIdentity();

	//gluPerspective(45,1, 1.0, 400.0);// �ʿ��� ��ȯ ����

	static float ratio = 0;
	static float add = 0;
	
	glRotatef(20, 1, 0, 0);

	
	
	glPushMatrix();
	
	glColor3f(1,0,0);
	glScalef(1, 20, 1);
	glutSolidCube(5);
	
		glPushMatrix();
		glTranslatef(0,-5,0);
			glColor3f(1, 1, 0);
			glScalef(50, 1, 20);
			glutSolidCube(5);
		glPopMatrix();
	glPopMatrix();

	//cos(angle)*radius), (sin(angle)* radius
	//1����
	glPushMatrix();
	glTranslatef(0,ratio,0);
	glTranslatef(cos(add) * 15, 0, sin(add)* 15);
	glColor3f(0, 1, 0);
	glRotatef(90, 1, 0, 0);
	glutWireTorus(4,25,25,25);
	if (-40 >= ratio)
	{
		
	}
	else
	{
		add += 0.5f;
		ratio--;
	}
	glPopMatrix();

	//2��°

	static float ratio1 = 0.0f;
	static float add1 = 0.0f;
	static float drop1 = 100.0f;
	glPushMatrix();
	
	if (drop1 >= 80)
	{
		glTranslatef(0, drop1--, 0);
		
	}
	else
	{
		glTranslatef(0, drop1--, 0);
		glTranslatef(0, ratio1, 0);
		glTranslatef(cos(add1) * 15, 0, sin(add1) * 15);
	}
		glColor3f(0, 1, 0);
		glRotatef(90, 1, 0, 0);
		glutWireTorus(4, 25, 25, 25);
	if (-40 -20 -10  >= ratio1)
	{
		drop1++;
	}
	else
	{
		add1 += 0.5f;
		ratio1--;
	}
	glPopMatrix();



	
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();

}
void Reshape(int w, int h)
{
	// ����Ʈ ��ȯ ����: ��� ȭ�� ����
	glViewport(0, 0, w, h);
	// Ŭ���� ��ȯ ����: ����ϰ��� �ϴ� ���� ����
	// �Ʒ� 3���� ������ �����ϴ� �Լ�
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ���� ������ ����ϴ� ���:
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// �𵨸� ��ȯ ����: ���÷��� �ݹ� �Լ����� �� ��ȯ �����ϱ� ���Ͽ� Matrix mode ����
	glMatrixMode(GL_MODELVIEW);
	// ���� ��ȯ: ī�޶��� ��ġ ���� (�ʿ��� ���, �ٸ� ���� ���� ����)
	gluLookAt(0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0, 1.0, 0.0);
}
void Keyboard(unsigned char key, int x, int y)
{
	if (key == 'x' || key == 'X')
	{

		static int Xcnt = 0;
		if (STATE == RESET)
			Xcnt = 0;
		++Xcnt;
		if (1 == Xcnt % 4)
			FlagX = MoveXPlus;
		if (2 == Xcnt % 4)
			FlagX = MoveXStop;
		if (3 == Xcnt % 4)
			FlagX = MoveXMinus;
		if (0 == Xcnt % 4)
			FlagX = MoveXStop;

	}
	if (key == 'y' || key == 'Y')
	{
		static int Ycnt = 0;
		if (STATE == RESET)
			Ycnt = 0;
		++Ycnt;
		if (1 == Ycnt % 4)
			FlagY = MoveYPlus;
		if (2 == Ycnt % 4)
			FlagY = MoveYStop;
		if (3 == Ycnt % 4)
			FlagY = MoveYMinus;
		if (0 == Ycnt % 4)
			FlagY = MoveYStop;

	}
	if (key == 'z' || key == 'Z')
	{
		static int Zcnt = 0;
		if (STATE == RESET)
			Zcnt = 0;
		++Zcnt;
		if (1 == Zcnt % 4)
			FlagZ = MoveZPlus;
		if (2 == Zcnt % 4)
			FlagZ = MoveZStop;
		if (3 == Zcnt % 4)
			FlagZ = MoveZMinus;
		if (0 == Zcnt % 4)
			FlagZ = MoveZStop;

	}
	if (key == 'l' || key == 'L')
	{
		KEY = KeyLeft;
	}
	if (key == 'r')
	{
		BOX = KeyRight;
	}
	if (key == 'R')
	{
		BOX = KeyLeft;
	}
	if (key == 's')
	{
		SECONDROTATE = RIGHT;
	}
	if (key == 'S')
	{
		SECONDROTATE = LEFT;
	}
	if (key == 't')
	{
		TOP = RIGHT;
	}
	if (key == 'k')
	{
		THIRDROTATE = RIGHT;
	}
	if (key == 'K')
	{
		THIRDROTATE = LEFT;
	}
	if (key == 'T')
	{
		TOP = LEFT;
	}
	if (key == '1')
	{
		KEY = KeyX;
		view++;
	}
	if (key == '2')
	{
		KEY = KeyY;
		view++;
	}
	if (key == '3')
	{
		KEY = KeyZ;
		view++;
	}
	if (key == 'b')
	{
		BlockRotate = LEFT;
	}
	if (key == '+' || key == '=')
	{
		Camera = ZOOM;
	}
	if (key == '-' || key == '_')
	{
		Camera = ZOOMOUT;
	}
	if (key == 'i' || key == 'I')
	{
		KEY = 0;
		FlagX = 0;
		FlagY = 0;
		FlagZ = 0;
		Camera = 0;
		view = 0;
		STATE = RESET;
		glLoadIdentity();
	}
}
void TimerFunction(int value)
{
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
	glutTimerFunc(100, TimerFunction, 1);
}
