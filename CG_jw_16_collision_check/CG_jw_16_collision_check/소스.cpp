#include <gl/glut.h>
#include <iostream>// ��� ����
using namespace std;
// �ʿ��� ���� ���� ����
int KEY = 0;
int FlagX = 0;
int FlagY = 0;
int FlagZ = 0;
int Camera = 0;
int STATE = 0;
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

const int MoveXPlus = 8;
const int MoveXMinus = 9;
const int MoveYPlus = 10;
const int MoveYMinus = 11;
const int MoveZPlus = 12;
const int MoveZMinus = 13;
const int MoveXStop = 14;
const int MoveYStop = 15;
const int MoveZStop = 15;


struct Ball 
{
	 float x;
	 float y;
	float z;
};
Ball* ball = new Ball;


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
	ball->x = 0;
	ball->y = 0;
	ball->z = 0;
}

// �������� ���� ���÷��� �ݹ� �Լ�: ��� �׸��� ����� �� �Լ����� ��κ� ó�� ��
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�

	glLoadIdentity();

	//gluPerspective(45,1, 1.0, 400.0);// �ʿ��� ��ȯ ����

	static float ratio = 0;
	static float add = 0;
	if (STATE == RESET)	{
		view = 0;
		add = 0;
		ratio = 0;
	}


	if (Camera == ZOOM)	{		if (STATE == RESET)		{			add = 0;		}		glTranslatef(0, 0, add++);	}
	if (Camera == ZOOMOUT)	{		if (STATE == RESET)		{			add = 0;		}		glTranslatef(0, 0, add--);	}
	if (KEY == KeyX)
	{
		glPushMatrix();
		glRotatef(view, 1, 0, 0);
	}
	if (KEY == KeyY)
	{
		glPushMatrix();
		glRotatef(view, 0, 1, 0);

	}
	if (KEY == KeyZ)
	{
		glPushMatrix();
		glRotatef(view, 0, 0, 1);

	}
	glPushMatrix();
	glColor3f(1.0f, 0.0f, 1.0f);
	glScalef(0.2, 2, 0.2);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(0.0f, 1.0f, 1.0f);
	glScalef(2, 0.2, 0.2);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glScalef(0.2, 0.2, 2);
	glutSolidCube(5);
	glPopMatrix();

	//��
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0, -100, 50);
	glScalef(50, 0.2, 30);
	glutSolidCube(5);
	glPopMatrix();



	// ��ǥ�� ��

	//  ���� ����
	glPushMatrix();

	glColor3f(1.0f, 0.8f, 0.9f);
	glTranslatef(-50, -100, 0);
	if (KEY == KeyLeft)
	{
		glRotatef(ratio++, 0, 1, 0);
	}
	glutSolidCube(20);


	glPopMatrix();

	glPushMatrix();
	glColor3f(0.8f, 1.0f, 0.8f);
	glTranslatef(-50, -100, 0);
	if (KEY == KeyLeft)
	{
		glRotatef(ratio++, 0, 1, 0);
	}
	glutWireCube(20);
	glPopMatrix();

	//

	//������
	
	glPushMatrix();

	static float movez = 0;
	if (STATE == RESET)	{
		movez = 0;
	}
	glTranslatef(0, -100, +30);
	if (FlagX == MoveXPlus)
	{
		ball->x += 1;
		glTranslatef(ball->x, 0, 0);
		glRotatef(ratio--, 0, 0, 1);
		if (120 <= ball->x)
			FlagX = MoveXStop;
	}
	else if (FlagX == MoveXMinus)
	{
		ball->x -= 1;
		glTranslatef(ball->x, 0, 0);
		glRotatef(ratio++, 0, 0, 1);
		if (-120 >= ball->x)
			FlagX = MoveXStop;
	}
	else if (FlagX == MoveXStop)
	{
		glTranslatef(ball->x, 0, 0);
		glRotatef(ratio++, 0, 0, 1);
	}

	static float ratioZ = 0.0f;
	static float rotz = 0;
	if (STATE == RESET)	{
		ratioZ = 0.0f;
		rotz = 0;
	}
	if (FlagZ == MoveZPlus)
	{
		ball->z += 1;
		glTranslatef(0, 0, ball->z);
		glRotatef(ratioZ--, 1, 0, 0);
		if (60 <= ball->z)
			FlagZ = MoveZStop;
	}
	else if (FlagZ == MoveZMinus)
	{
		ball->z -= 1;
		glTranslatef(0, 0, ball->z);
		glRotatef(ratioZ++, 1, 0, 0);
		if (-60 >= ball->z)
			FlagZ = MoveZStop;
	}
	else if (FlagZ == MoveZStop)
	{
		glTranslatef(0, 0, ball->z);
		glRotatef(ratioZ, 1, 0, 0);
	}

	static float ratioY = 0.0f;
	if (STATE == RESET)	{
		ratioY = 0.0f;
	}

	if (FlagY == MoveYPlus)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		glRotatef(ratioY--, 0, 1, 0);
	}
	else if (FlagY == MoveYMinus)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		glRotatef(ratioY++, 0, 1, 0);
	}
	else if (FlagY == MoveYStop)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		glRotatef(ratioY, 0, 1, 0);
	}
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(20, 20, 20);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireSphere(20, 20, 20);

	glPopMatrix();



	if (KEY == KeyX)
	{

		glPopMatrix();
	}													//--- ��ȯ�� �����ϱ� ���ؼ�
	else if (KEY == KeyY)													// glPushMatrix �Լ��� ȣ���Ͽ� ������ ��ǥ �ý����� ����
	{													// �ʿ��� ��� ��� �ʱ�ȭ ( glLoadIdentity ( ); )
		glPopMatrix();											// ��ȯ ����: �̵�, ȸ��, ���� �� �𵨿� ���� �� ��ȯ �Լ��� ȣ���Ѵ�.
	}

	else if (KEY == KeyZ)							// ��ȯ�� ���� �Ŀ��� ������ ��ǥ�ý����� �ٽ� �����ϱ� ���Ͽ� glPopMatrix �Լ� ȣ��
	{
		glPopMatrix();								// ��� ���
	}

	STATE = NORMAL;

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
	if (key == 'r' || key == 'R')
	{
		KEY = KeyRight;
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
