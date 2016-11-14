#include <gl/glut.h>
#include <time.h>
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
};
CollideBox* CollideLeftBox = new CollideBox;
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
	ball->x = 0;
	ball->y = 0;
	ball->z = 0;
	Crane->x = 0;
	Crane->y = 0;
	Crane->z = 0;
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






	//��
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0, -120, 50);
	glScalef(50, 0.2, 30);
	glutSolidCube(5);
	glPopMatrix();

	//���ʳ���
	glPushMatrix();
	glColor3f(1.0f, 0.8f, 0.0f);
	glTranslatef(-50, -50, 0);
	glScalef(1, 15, 1);
	glutSolidCube(10);
	glColor3f(0.0f, 1.0f, 0.0f);
	//�浹üũ �ڽ�
	glutWireCube(20);
	//������
	static float leafAng = 45.0f;
	glTranslatef(0, 4, 0);
	leafAng += 5;
	glRotatef(leafAng, 0, 1, 0);
	glColor3f(0.0f, 1.0f, 0.2f);
	glScalef(15, 1, 6);
	glutSolidCube(4);
	glPopMatrix();


	//������ ���� 
	glPushMatrix();
	glColor3f(1.0f, 0.8f, 0.0f);
	glTranslatef(50, -50, 0);
	glScalef(1, 15, 1);
	glutSolidCube(10);
	//�浹�ڽ�
	glColor3f(1.0f, 0.8f, 0.0f);
	glutWireCube(20);
	//���� ������
	static float circleleaf = 0.0f;
	static bool circlesizeup = false;
	glTranslatef(0, 5, 0);
	if (circlesizeup == true)
	{
		circleleaf += 0.1;

		if (2 <= circleleaf)
			circlesizeup = false;
	}
	if (circlesizeup == false)
	{
		circleleaf -= 0.1;

		if (circleleaf <= 0)
			circlesizeup = true;
	}

	glScalef(circleleaf, circleleaf, circleleaf);
	glColor3f(1.0f, 0.0f, 0.2f);
	glScalef(2, 1, 1);
	glutWireSphere(4, 10, 10);
	glColor3f(1.0f, 0.7f, 0.0f);
	glutSolidSphere(4, 10, 10);
	glPopMatrix();


	//���ʾƷ�����
	glPushMatrix();
	glColor3f(0.5f, 0.2f, 0.1f);
	glTranslatef(-100, -50, 80);
	glScalef(1, 15, 1);
	glutSolidCube(10);
	//�浹üũ�ڽ�
	glColor3f(0.5f, 0.2f, 0.1f);
	glutWireCube(20);
	//������

	glTranslatef(0, 4, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(0.0f, 1.0f, 0.9f);
	glScalef(1, 1, 1);
	glPushMatrix();
	static bool upAndDown = false;
	static float test4 = 0.0f;
	//
	if (upAndDown == true)
	{
		test4 += 0.2;

		if (2 <= test4)
			upAndDown = false;
	}
	if (upAndDown == false)
	{
		test4 -= 0.2;

		if (test4 <= 0)
			upAndDown = true;
	}
	//
	glTranslatef(0, 0, test4);
	glutWireTorus(2, 25, 15, 15);
	glPopMatrix();
	glPopMatrix();

	//�����ʸ𷡽ð�

	glPushMatrix();
	glTranslatef(0, -20, 0);
	glPushMatrix();
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(100, -20, 80);
	glRotatef(90, 1, 0, 0);
	static float ConeSize = 10.0f;
	static bool ConeUp = false;
	glScalef(ConeSize, ConeSize, ConeSize / 2);
	if (ConeUp == true)
	{
		ConeSize -= 0.1f;
		if (ConeSize <= 5)
			ConeUp = false;
	}
	if (ConeUp == false)
	{
		ConeSize += 0.1f;
		if (10.0f <= ConeSize)
			ConeUp = true;
	}
	glutWireCone(5, 10, 15, 15);
	//�浹üũ�ڽ�

	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireCube(10);
	glPopMatrix();

	static float ConeSize1 = 5.0f;
	glPushMatrix();
	glTranslatef(100, -95, 80);
	glRotatef(-90, 1, 0, 0);
	glColor3f(1.0f, 0.0f, 0.0f);
	glScalef(ConeSize1, ConeSize1, ConeSize1 / 2);
	static bool ConeUp1 = false;
	if (ConeUp1 == false)
	{
		ConeSize1 -= 0.1f;
		if (ConeSize1 <= 5)
			ConeUp1 = true;
	}
	if (ConeUp1 == true)
	{
		ConeSize1 += 0.1f;
		if (10.0f <= ConeSize1)
			ConeUp1 = false;
	}
	glutWireCone(5, 10, 15, 15);
	glColor3f(1.0f, 0.0f, 0.0f);
	glutWireCube(10);
	glPopMatrix();


	glPopMatrix();

	glPushMatrix();
	glTranslatef(0, 0, 0);
	if (BlockRotate == LEFT)
		glRotatef(ratio++, 0, 1, 0);

	//�߾ӹ�����
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(-20, -110, 70);
	glScalef(4, 20, 4);
	glutSolidCube(5);
	//�浹�ڽ�
	glutWireCube(6);
	glPopMatrix();

	//����
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(0, -80, 70);
	glScalef(4, 1, 1);
	glutSolidCube(5);
	glPopMatrix();

	//��������
	static float moveblock = 0.0f;
	static bool moveflag = false;
	glPushMatrix();
	glColor3f(0.8f, 0.3f, 0.3f);
	glTranslatef(10, -100, 70);
	glScalef(2, 4, 1);
	glTranslatef(moveblock, 0, 0);
	if (moveflag == true)
	{
		moveblock++;
		if (5 <= moveblock)
			moveflag = false;
	}
	if (moveflag == false)
	{
		moveblock--;
		if (0 >= moveblock)
			moveflag = true;
	}
	glutSolidCube(10);
	//�浹�ڽ�
	glutWireCube(15);
	glPopMatrix();

	//����������
	static float moveblock1 = 0.0f;
	static bool moveflag1 = true;
	glPushMatrix();
	glColor3f(0.8f, 0.3f, 0.3f);
	glTranslatef(-10, -100, 70);
	glScalef(2, 4, 1);
	glTranslatef(moveblock1, 0, 0);
	if (moveflag1 == true)
	{
		moveblock1++;
		if (0 <= moveblock1)
			moveflag1 = false;
	}
	if (moveflag1 == false)
	{
		moveblock1--;
		if (-5 >= moveblock1)
			moveflag1 = true;
	}
	glutSolidCube(10);
	//�浹�ڽ�
	glutWireCube(15);
	glPopMatrix();

	//������
	glPushMatrix();
	glColor3f(0.3f, 0.3f, 0.3f);
	glTranslatef(20, -110, 70);
	glScalef(4, 20, 4);
	glutSolidCube(5);
	//�浹�ڽ�
	glutWireCube(6);
	glPopMatrix();

	glPopMatrix();



	//��
	glPushMatrix();
	//glPushMatrix();
	//if (ball->x -50   >= Crane->x && ball->x - 150 <= Crane->x)
	//cout << "colide" << endl;
	bool CraneStop = false;
	if (ball->z + 12 >= Crane->z && ball->z - 55 <= Crane->z && ball->x - 50 >= Crane->x && ball->x - 150 <= Crane->x)
	{
		FlagXCrane = MoveXStop;
		FlagX = MoveXStop;
		FlagZCrane = MoveZStop;
		FlagZ = MoveZStop;
		CraneStop = true;
	}
	static float ratioSphere = 0.0f;
	glTranslatef(-100, -100, 10);
	if (FlagX == MoveXPlus)
	{
		ball->x += 1;
		glTranslatef(ball->x, 0, 0);
		glRotatef(ratioSphere--, 0, 0, 1);
		if (220 <= ball->x)
			FlagX = MoveXStop;
	}
	else if (FlagX == MoveXMinus)
	{
		ball->x -= 1;
		glTranslatef(ball->x, 0, 0);
		glRotatef(ratioSphere++, 0, 0, 1);
		if (-20 >= ball->x)
			FlagX = MoveXStop;
	}
	else if (FlagX == MoveXStop)
	{
		glTranslatef(ball->x, 0, 0);
		glRotatef(ratioSphere++, 0, 0, 1);
	}

	static float ratio1Z = 0.0f;
	static float rotz1 = 0;
	if (STATE == RESET)	{
		ratio1Z = 0.0f;
		rotz1 = 0;
	}
	if (FlagZ == MoveZPlus)
	{
		ball->z += 1;
		glTranslatef(0, 0, ball->z);
		glRotatef(ratio1Z--, 1, 0, 0);
		if (110 <= ball->z)
			FlagZ = MoveZStop;
	}
	else if (FlagZ == MoveZMinus)
	{
		ball->z -= 1;
		glTranslatef(0, 0, ball->z);
		glRotatef(ratio1Z++, 1, 0, 0);
		if (-40 >= ball->z)
			FlagZ = MoveZStop;
	}
	else if (FlagZ == MoveZStop)
	{
		glTranslatef(0, 0, ball->z);
		glRotatef(ratio1Z, 1, 0, 0);
	}

	static float ratio1Y = 0.0f;
	if (STATE == RESET)	{
		ratio1Y = 0.0f;
	}

	if (FlagY == MoveYPlus)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		glRotatef(ratio1Y--, 0, 1, 0);
	}
	else if (FlagY == MoveYMinus)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		glRotatef(ratio1Y++, 0, 1, 0);
	}
	else if (FlagY == MoveYStop)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		glRotatef(ratio1Y, 0, 1, 0);
	}
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(20, 20, 20);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireSphere(20, 20, 20);
	//�ڽ�
	glutWireCube(30);
	glPopMatrix();



	// ��ǥ�� ��

	//  ���� ����








	//glPushMatrix();
	//glColor3f(0.8f, 1.0f, 0.8f);
	//glTranslatef(-50, -100, 0);
	//if (KEY == KeyLeft)
	//{
	//	glRotatef(ratio++, 0, 1, 0);
	//}
	//glutWireCube(20);
	//glPopMatrix();

	//

	//if (CraneStop == true)
	//{
	//	FlagXCrane = MoveXStop;
	//	FlagZCrane = MoveZStop;
	//}
	//else
	//{//�ΰ����� ũ����
	//	if (FlagXCrane == MoveXPlus)
	//	{
	//		if (80 <= Crane->x)
	//			FlagXCrane = MoveXStop;

	//		static int XPlusCnt = 0;
	//		XPlusCnt++;
	//		if (10 <= XPlusCnt)
	//		{
	//			XPlusCnt = 0;
	//			FlagXCrane = MoveXStop;
	//		}

	//	}
	//	else if (FlagXCrane == MoveXMinus)
	//	{
	//		static int XMinusCnt = 0;
	//		XMinusCnt++;
	//		if (-60 >= Crane->x)
	//			FlagXCrane = MoveXStop;
	//		if (10 <= XMinusCnt)
	//		{
	//			XMinusCnt = 0;
	//			FlagXCrane = MoveXStop;
	//		}

	//	}
	//	else
	//	{
	//		FlagXCrane = rand() % 3 + 1;
	//	}
	//	//
	//	if (FlagZCrane == MoveZPlus)
	//	{
	//		static int ZPlusCnt = 0;
	//		ZPlusCnt++;
	//		if (60 <= Crane->z)
	//			FlagZCrane = MoveZStop;
	//		if (5 <= ZPlusCnt)
	//		{
	//			ZPlusCnt = 0;
	//			FlagZCrane = MoveZStop;
	//		}

	//	}
	//	else if (FlagZCrane == MoveZMinus)
	//	{
	//		static int ZMinusCnt = 0;
	//		ZMinusCnt++;
	//		if (-60 >= Crane->z)
	//			FlagZCrane = MoveZStop;
	//		if (5 <= ZMinusCnt)
	//		{
	//			ZMinusCnt = 0;
	//			FlagZCrane = MoveZStop;
	//		}

	//	}
	//	else
	//	{
	//		FlagZCrane = rand() % 3 + 1;
	//	}
	//}
	////�ΰ����� ��


	//ũ����
	//������
	glPushMatrix();
	glTranslatef(0, -100, +30);
	glScalef(2, 1, 1);
	static float movez = 0;
	if (STATE == RESET)	{
		movez = 0;
	}
	//�߰��ڵ�

	if (KEY == KeyLeft)
	{
		glRotatef(ratio++, 0, 1, 0);
	}
	if (FlagXCrane == MoveXPlus)
	{
		Crane->x += 1;
		glTranslatef(Crane->x, 0, 0);
		//glRotatef(ratio--, 0, 0, 1);
	}
	else if (FlagXCrane == MoveXMinus)
	{
		Crane->x -= 1;
		glTranslatef(Crane->x--, 0, 0);
		//glRotatef(ratio++, 0, 0, 1);
	}
	else if (FlagXCrane == MoveXStop)
	{
		glTranslatef(Crane->x, 0, 0);
		//glRotatef(ratio++, 0, 0, 1);
	}

	static float ratioZ = 0.0f;
	static float rotz = 0;
	if (STATE == RESET)	{
		ratioZ = 0.0f;
		rotz = 0;
	}
	if (FlagZCrane == MoveZPlus)
	{
		Crane->z += 1;
		glTranslatef(0, 0, Crane->z);
		//glRotatef(ratioZ--, 1, 0, 0);
	}
	else if (FlagZCrane == MoveZMinus)
	{
		Crane->z -= 1;
		glTranslatef(0, 0, Crane->z);
		//glRotatef(ratioZ++, 1, 0, 0);
	}
	else if (FlagZCrane == MoveZStop)
	{
		glTranslatef(0, 0, Crane->z);
		//glRotatef(ratioZ, 1, 0, 0);
	}

	static float ratioY = 0.0f;
	if (STATE == RESET)	{
		ratioY = 0.0f;
	}

	if (FlagYCrane == MoveYPlus)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		//glRotatef(ratioY--, 0, 1, 0);
	}
	else if (FlagYCrane == MoveYMinus)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		//glRotatef(ratioY++, 0, 1, 0);
	}
	else if (FlagYCrane == MoveYStop)
	{
		//static float rotz = 0;
		glTranslatef(0, 0, 0);
		//glRotatef(ratioY, 0, 1, 0);
	}
	glColor3f(0.0f, 1.0f, 1.0f);
	glutSolidCube(30);
	glColor3f(0.0f, 0.0f, 1.0f);
	glutWireCube(30);


	//�߰��ڵ� ����

	/*glPushMatrix();
	glTranslatef(-10, -20, -10);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(10,20,20);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-10, -20, 10);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(10, 20, 20);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, -20, 10);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(10, 20, 20);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(10, 20, 20);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(10, -20, -10);
	glColor3f(0.0f, 0.0f, 0.0f);
	glutSolidSphere(10, 20, 20);
	glColor3f(1.0f, 1.0f, 1.0f);
	glutWireSphere(10, 20, 20);
	glPopMatrix();
	*/

	//�߰� ��

	static float SecondYRotate = 0;
	if (SECONDROTATE == RIGHT)
	{
		SecondYRotate += 2;
		glRotatef(SecondYRotate, 0, 1, 0);

	}
	if (SECONDROTATE == LEFT)
	{
		SecondYRotate -= 2;
		glRotatef(SecondYRotate, 0, 1, 0);

	}
	static float SecondAngle = 0.0f;

	if (BOX == KeyRight)
	{

		glTranslatef(0, 0, 0);
		glRotatef(SecondAngle, 1, 0, 0);
		if (60 <= SecondAngle)
		{
			;
		}
		else
		{
			SecondAngle += 1;
		}
	}
	if (BOX == KeyLeft)
	{

		glTranslatef(0, 0, 0);
		glRotatef(SecondAngle, 1, 0, 0);
		if (-60 >= SecondAngle)
		{
			;
		}
		else
		{
			SecondAngle -= 1;
		}
	}
	glPushMatrix();
	glTranslatef(0, 35, 0);
	glScalef(1, 4, 1);
	glColor3f(0.8f, 0.4f, 0.7f);
	glutSolidCube(10);
	glColor3f(0.1f, 0.2f, 0.7f);
	glutWireCube(10);

	//������ 
	static float ThirdZRotate = 0;
	if (THIRDROTATE == RIGHT)
	{

		glRotatef(ThirdZRotate, 1, 0, 0);
		if (60 <= ThirdZRotate)
		{
			;
		}
		else
		{
			ThirdZRotate += 1;
		}

	}
	if (THIRDROTATE == LEFT)
	{

		glRotatef(ThirdZRotate, 1, 0, 0);
		if (60 <= ThirdZRotate)
		{
			;
		}
		else
		{
			ThirdZRotate += 1;
		}

	}
	static float ThirdAngle = 0.0f;
	if (TOP == RIGHT)
	{

		glTranslatef(0, 0, 0);
		glRotatef(ThirdAngle, 0, 0, 1);
		if (60 <= ThirdAngle)
		{
			;
		}
		else
		{
			ThirdAngle += 1;
		}
	}
	if (TOP == LEFT)
	{

		glTranslatef(0, 0, 0);
		glRotatef(ThirdAngle, 0, 0, 1);
		if (-60 >= ThirdAngle)
		{
			;
		}
		else
		{
			ThirdAngle -= 1;
		}
	}
	//�� ����
	glPushMatrix();
	glTranslatef(0, 10, 0);
	glScalef(1, 2, 1);
	glColor3f(0.8f, 0.4f, 0.4f);
	glutSolidCube(5);
	glColor3f(0.1f, 0.2f, 0.1f);
	glutWireCube(5);


	glPopMatrix();


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
