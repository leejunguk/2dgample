#include <gl/glut.h>
#include <time.h>
#include <vector>
#include <iostream>// ��� ����
#include "SnowBall.h"
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

CSnowBall* Snowlist = new CSnowBall[100];

static float AmbientR = 0.1;
static float AmbientG = 0.1;
static float AmbientB = 0.1;
static float AmbientA = 0.2f;

static float DiffuseR = 0.1;
static float DiffuseG = 0.1;
static float DiffuseB = 0.1;
static float DiffuseA = 0.2f;

static float SpecularR = 0.1;
static float SpecularG = 0.1;
static float SpecularB = 0.1;
static float SpecularA = 0.2f;

//�ǽ�
GLfloat AmbientLight[] = { AmbientR, AmbientG, AmbientB, AmbientA };
GLfloat DiffuseLight[] = { DiffuseR, DiffuseG, DiffuseB, DiffuseA };
GLfloat SpecularLight[] = { SpecularR, SpecularG, SpecularB, SpecularA };
GLfloat lightPos[] = { 100.0, 10.0, 10.0, 1.0 };
GLfloat lightPosLeft[] = {-100.0, 10.0,10.0,1.0};
//�����Ӽ�
GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

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

	for (int i = 0; i < 50; ++i)
	{
		Snowlist[i].InitPosition(i * 10 - 200, rand() % 50 + 150, i);
	}

	srand(unsigned(time(NULL)));
}

// �������� ���� ���÷��� �ݹ� �Լ�: ��� �׸��� ����� �� �Լ����� ��κ� ó�� ��
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLoadIdentity();

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//�ǽ�
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos);
	glEnable(GL_LIGHT0);

	//����
	glLightfv(GL_LIGHT1, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT1, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT1, GL_POSITION, lightPosLeft);
	glEnable(GL_LIGHT1);

	//����

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glShadeModel(GL_FLAT);
	glEnable(GL_NORMALIZE);
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
	static float MoveSnow = 1.0f;
	MoveSnow += 1.0f;
	
	CSnowBall* SnowTemp = new CSnowBall[20];
	
	
	//���׸����ڵ�
	for (int i = 0; i < 50; ++i)
	{
		glPushMatrix();

		
		Snowlist[i].Move(MoveSnow);
		Snowlist[i].Draw();

		glPopMatrix();
	}
	
	//for (int i = 0; i < 50; ++i)
	//{
	//	if(true == Snowlist[i].GetDelete())
	//		delete Snowlist;
	//}
	//vector<CSnowBall*>	VecSnow;
	//VecSnow.reserve(100);
	//// test the Snow
	//for (int i = 0; i < 20; i)
	//{
	//	VecSnow.push_back(CSnowBall::Create());
	//}
	//for (int i = 0; i < 20; i)
	//{
	//	VecSnow[i]->Draw();
	//}
	//for (int i = 0; i < 20; i)
	//{
	//	VecSnow[i]->Relase();
	//}
	//VecSnow.clear();
		//CSnowBall * snow = new CSnowBall;
		//Snowlist[i] = snow->Create(i);
		//Snowlist[i]->InitPosition(i+2, 200, 0);
		////Snowlist[i]->Move(MoveSnow);
		////Snowlist[i]->Draw();
	
	//snow->Relase();
	//
	/*for (int i = 0; i < 20; ++i)
	{
		Snowlist[i]->Relase();
	}*/


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

	LeftTree->x = -50;
	LeftTree->y = -50;
	LeftTree->z = 0;
	LeftTree->size = 20;

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
	RightTree->x = 50;
	RightTree->y = -50;
	RightTree->z = 0;
	RightTree->size = 10;
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

	//test
	glPushMatrix();


	
	// ���� �ﰢ�� �׸���
	glTranslatef(0, -90, 30);
	glScalef(30, 30, 30);

	glBegin(GL_TRIANGLES);
	
	
	glColor3f(0.5f, 0.0f, 0.0f);

	glNormal3f(0.0, 1.0, 0.0);
	
	glVertex3f(0.0f, 1.0f, 0.0f); // { Right }
	glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
	glVertex3f(1.0f, -1.0f, -1.0f); // { Right }


	//glColor3f(0.5f, 0.0f, 0.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 1.0f, 0.0f); // { Front }
	glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
	glVertex3f(1.0f, -1.0f, 1.0f); // { Front }
	
	//glColor3f(0.5f, 0.0f, 0.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 1.0f, 0.0f); // { Back }
	glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
	glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }


	
	//glColor3f(0.5f, 0.0f, 0.0f);
	glNormal3f(0.0, 1.0, 0.0);
	glVertex3f(0.0f, 1.0f, 0.0f); // { Left }
	glVertex3f(-1.0f, -1.0f, -1.0f); // { Left }
	glVertex3f(-1.0f, -1.0f, 1.0f); // { Left }

	glEnd();

	//
	//glPopMatrix();

	static float Earth_Rotate_angle = 0.0f;
	Earth_Rotate_angle += 3.0f;
	//glPushMatrix();
	glRotatef(Earth_Rotate_angle, 0, 1, 0);
	glTranslatef(1, 1, 0);

	glColor3f(0, 1, 0);
	glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(3, 10, 10);

	glPushMatrix();
	//glTranslatef(5, 1, 0);
	static float MOON_Rotate_angle = 0.0f;
	MOON_Rotate_angle += 15.0f;
	glRotatef(MOON_Rotate_angle, 0, 1, 0);
	glTranslatef(5, 1, 0);

	glColor3f(0, 0, 1);
	//glScalef(0.1, 0.1, 0.1);
	glutSolidSphere(1, 10, 10);

	glPopMatrix();

	glPopMatrix();

	//



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

	

	//glTranslatef(0, 0, -60);
	//if (BlockRotate == LEFT)
	//	glRotatef(ratio++, 0, 1, 0);

	////�߾ӹ�����
	//glPushMatrix();
	//glColor3f(0.3f, 0.3f, 0.3f);
	//glTranslatef(-20, -110, 70);
	//glScalef(4, 20, 4);
	//glutSolidCube(5);
	////�浹�ڽ�
	//glutWireCube(6);
	//glPopMatrix();

	////����
	//glPushMatrix();
	//glColor3f(0.3f, 0.3f, 0.3f);
	//glTranslatef(0, -80, 70);
	//glScalef(4, 1, 1);
	//glutSolidCube(5);
	//glPopMatrix();

	////��������
	//static float moveblock = 0.0f;
	//static bool moveflag = false;
	//glPushMatrix();
	//glColor3f(0.8f, 0.3f, 0.3f);
	//glTranslatef(10, -100, 70);
	//glScalef(2, 4, 1);
	//glTranslatef(moveblock, 0, 0);
	//if (moveflag == true)
	//{
	//	moveblock++;
	//	if (5 <= moveblock)
	//		moveflag = false;
	//}
	//if (moveflag == false)
	//{
	//	moveblock--;
	//	if (0 >= moveblock)
	//		moveflag = true;
	//}
	//glutSolidCube(10);
	////�浹�ڽ�
	//glutWireCube(15);
	//glPopMatrix();

	////����������
	//static float moveblock1 = 0.0f;
	//static bool moveflag1 = true;
	//glPushMatrix();
	//glColor3f(0.8f, 0.3f, 0.3f);
	//glTranslatef(-10, -100, 70);
	//glScalef(2, 4, 1);
	//glTranslatef(moveblock1, 0, 0);
	//if (moveflag1 == true)
	//{
	//	moveblock1++;
	//	if (0 <= moveblock1)
	//		moveflag1 = false;
	//}
	//if (moveflag1 == false)
	//{
	//	moveblock1--;
	//	if (-5 >= moveblock1)
	//		moveflag1 = true;
	//}
	//glutSolidCube(10);
	////�浹�ڽ�
	//glutWireCube(15);
	//glPopMatrix();

	////������
	//glPushMatrix();
	//glColor3f(0.3f, 0.3f, 0.3f);
	//glTranslatef(20, -110, 70);
	//glScalef(4, 20, 4);
	//glutSolidCube(5);
	////�浹�ڽ�
	//glutWireCube(6);
	//glPopMatrix();

	//glPopMatrix();



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
	static float XFoward = 0;

	glTranslatef(-100, -100, 10);
	ball->x = -100;
	ball->y = -100;
	ball->z = 10;
	if (FlagX == MoveXPlus)
	{
		static int plusint = 0;
		plusint++;
		ball->x = ball->x + plusint;
		glTranslatef(XFoward++, 0, 0);
		glRotatef(ratioSphere--, 0, 0, 1);
		if (220 <= ball->x)
			FlagX = MoveXStop;
	}
	else if (FlagX == MoveXMinus)
	{
		static int minusint = 0;
		minusint++;
		ball->x = ball->x - minusint;

		glTranslatef(XFoward--, 0, 0);
		glRotatef(ratioSphere++, 0, 0, 1);
		if (-20 >= ball->x)
			FlagX = MoveXStop;
	}
	else if (FlagX == MoveXStop)
	{
		glTranslatef(XFoward, 0, 0);
		glRotatef(ratioSphere++, 0, 0, 1);
	}

	static float ratio1Z = 0.0f;
	static float rotz1 = 0;
	static float MoveZFoward = 0.0f;
	if (STATE == RESET)	{
		ratio1Z = 0.0f;
		rotz1 = 0;
	}
	if (FlagZ == MoveZPlus)
	{
		static int plusint1 = 0;
		plusint1++;
		ball->z = ball->z + plusint1;
		glTranslatef(0, 0, MoveZFoward++);
		glRotatef(ratio1Z--, 1, 0, 0);
		if (110 <= ball->z)
			FlagZ = MoveZStop;
	}
	else if (FlagZ == MoveZMinus)
	{
		static int minusint1 = 0;
		minusint1++;
		ball->z = ball->z - minusint1;
		glTranslatef(0, 0, MoveZFoward--);
		glRotatef(ratio1Z++, 1, 0, 0);
		if (-40 >= ball->z)
			FlagZ = MoveZStop;
	}
	else if (FlagZ == MoveZStop)
	{
		glTranslatef(0, 0, MoveZFoward);
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

	if (ball->x >= LeftTree->x - LeftTree->size && ball->x <= LeftTree->x + LeftTree->size
		&&ball->z >= LeftTree->z - LeftTree->size && ball->z <= LeftTree->z + LeftTree->size)
		cout << "collide" << endl;
	if (ball->x >= RightTree->x - RightTree->size && ball->x <= RightTree->x + RightTree->size
		&&ball->z >= RightTree->z - RightTree->size && ball->z <= RightTree->z + RightTree->size)
		cout << "collide" << endl;




	



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
	if (key == 'q')
	{
		KEY = KeyX;
		view++;
	}
	if (key == 'w')
	{
		KEY = KeyY;
		view++;
	}
	if (key == 'e')
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
	if (key == 'A')
	{
		//ambient light ����
		AmbientR += 0.1f;
		AmbientG += 0.1f;
		AmbientB += 0.1f;
		AmbientA += 0.1f;
		cout << "1"<<endl;;
	}
	if (key == 'a')
	{
		AmbientR-= 0.1f;
		AmbientG-= 0.1f;
		AmbientB-= 0.1f;
		AmbientA-= 0.1f;
		//ambient light ����
	}
	if (key == 'd')
	{
		DiffuseR-= 0.1f;
		DiffuseG-= 0.1f;
		DiffuseB-= 0.1f;
		DiffuseA-= 0.1f;
		//diffuse light ����
	}
	if (key == 'D')
	{
		DiffuseR+= 0.1f;
		DiffuseG+= 0.1f;
		DiffuseB+= 0.1f;
		DiffuseA+= 0.1f;
		//diffuse light ����
	}
	if (key == 'S')
	{
		SpecularR+= 0.1f;
		SpecularG+= 0.1f;
		SpecularB+= 0.1f;
		SpecularA+= 0.1f;
		//diffuse light ����
	}
	if (key == 's')
	{
		SpecularR-= 0.1f;
		SpecularG-= 0.1f;
		SpecularB-= 0.1f;
		SpecularA-= 0.1f;
			//diffuse light ����
	}

	if (key == '1')
	{
		//1������ Ų�� / ����
	}
	if (key == '2')
	{
		//2 ������ Ų�� / ����
	}
}
void TimerFunction(int value)
{
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
	glutTimerFunc(100, TimerFunction, 1);
}
