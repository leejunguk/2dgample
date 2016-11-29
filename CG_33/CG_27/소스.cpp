#include <gl/glut.h>
#include <time.h>
#include <vector>
#include <iostream>// 헤더 파일
#include "SnowBall.h"
using namespace std;
// 필요한 전역 변수 선언
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
bool LeftBackLightSwtich = true;
bool RightBackLightSwtich = true;
bool LeftFrontLightSwtich = true;
bool RightFrontLightSwtich = true;
bool Animation = false;
bool CartBackWard = false;

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

//실습

//재질속성
GLfloat gray[] = { 0.75f, 0.75f, 0.75f, 1.0f };
GLfloat  specref[] = { 1.0f, 1.0f, 1.0f, 1.0f };

void main()
{
	// 윈도우 초기화 및 생성
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800, 600);
	glutCreateWindow("Points Drawing");
	// 상태 변수 초기화 함수
	SetupRC();
	glutDisplayFunc(DrawScene); // 출력 콜백 함수
	glutReshapeFunc(Reshape); // 다시 그리기 콜백 함수
	glutKeyboardFunc(Keyboard); // 키보드 입력 콜백 함수
	glutTimerFunc(100, TimerFunction, 1); // 타이머 콜백 함수
	glutMainLoop(); // 이벤트 루프 실행하기
}
void SetupRC() {
	// 필요한 변수들, 좌표값 등의 초기화
	// 기능 설정 초기화
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

	for (int i = 0; i < 100; ++i)
	{
		Snowlist[i].InitPosition(rand() % 500 -250, rand() % 600 + 150, i);
	}

	srand(unsigned(time(NULL)));
}

// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glLoadIdentity();

	GLfloat AmbientLight[] = { AmbientR, AmbientG, AmbientB, AmbientA };
	GLfloat DiffuseLight[] = { DiffuseR, DiffuseG, DiffuseB, DiffuseA };
	GLfloat SpecularLight[] = { SpecularR, SpecularG, SpecularB, SpecularA };

	GLfloat lightPos2[] = { 100.0, 0.0,-100.0,1.0 };
	GLfloat lightPos3[] = { -100.0, 0.0,100.0,1.0 };
	GLfloat lightPos4[] = { -100.0, 0.0,-100.0,1.0 };

	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);

	//실습
	static float RoatateLight = 0.0f;
	glPushMatrix();
	

		glTranslatef(100,0,100);
		glutSolidCube(5);
		
	glPopMatrix();
	

	
	
	//재질

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	//gluPerspective(45,1, 1.0, 400.0);// 필요한 변환 적용


	

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
	if (Animation == true)
	{
		static float AnimationZcnt = 0;
		glPushMatrix();
		static float AnimationRotate = 0;
		if (50 <= AnimationZcnt && 1440<= AnimationRotate)
		{
			glTranslatef(0, 0, AnimationZcnt--);
		}
		else if (50 <= AnimationZcnt)
		{
			glRotatef(AnimationRotate++, 0, 1, 0);
		}
		else
		{
			glTranslatef(0, 0, AnimationZcnt++);
		}

	}

	glPushMatrix();
		glTranslatef(100, 10, 10);
		glRotatef(-90, 1, 0, 0);
		glColor3f(0.5, 0.5, 0);
		glutSolidCone(5, 10, 15, 15);

	glPopMatrix();


	glPushMatrix();
	glTranslatef(-100, 10, 10);
	glRotatef(-90, 1, 0, 0);
	glColor3f(0.5, 0.5, 0);
	glutSolidCone(5, 10, 15, 15);

	glPopMatrix();


	static float MoveSnow = 1.0f;
	MoveSnow += 1.0f;
	
	CSnowBall* SnowTemp = new CSnowBall[20];
	
	
	//눈그리고코드
	for (int i = 0; i < 100; ++i)
	{
		glPushMatrix();

		
		Snowlist[i].Move(MoveSnow);
		Snowlist[i].Draw();

		glPopMatrix();
	}
	

	//땅
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(-150, -120, 50);
	glScalef(20, 0.2, 200);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0, -120, 50);
	glScalef(20, 0.2, 200);
	glutSolidCube(5);
	glPopMatrix();

	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(150, -120, 50);
	glScalef(20, 0.2, 200);
	glutSolidCube(5);
	glPopMatrix();

	//Cart
	static float CartZFoward = 0.0f;
	if (CartBackWard == false)
		CartZFoward -= 2;
	else
		CartZFoward += 2;
	if(CartZFoward <= -200)
		CartBackWard = true;
	if(30<= CartZFoward)
		CartBackWard = false;

	glPushMatrix();
	glColor3f(0,0.3,0);
	glTranslatef(0, -80, 50);
	glTranslatef(0,0, CartZFoward);
	glScalef(10,10,10);
	glutSolidCube(5);


	//조명
	glPushMatrix();
		GLfloat lightPos1[] = { 0, 0.0, 0.0, 1.0 };
		glScalef(0.1, 0.1, 0.1);
		glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
		glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
		glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
		glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
		glEnable(GL_LIGHT0);
		if (LeftBackLightSwtich == false)
			glDisable(GL_LIGHT0);
	glPopMatrix();

	//바퀴
	glPushMatrix();
		glColor3f(0,0,1);
		glTranslatef(-1,-3,-2);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(10,15,15);
	
	glPopMatrix();

	glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(1, -3, -2);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(10, 15, 15);

	glPopMatrix();

	glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(1, -3, 2);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(10, 15, 15);

	glPopMatrix();

	glPushMatrix();
		glColor3f(0, 0, 1);
		glTranslatef(-1, -3, 2);
		glScalef(0.1, 0.1, 0.1);
		glutSolidSphere(10, 15, 15);

	glPopMatrix();

	glPopMatrix();

	//Cart

	if (KEY == KeyX)
	{

		glPopMatrix();
	}													//--- 변환을 적용하기 위해서
	else if (KEY == KeyY)													// glPushMatrix 함수를 호출하여 기존의 좌표 시스템을 저장
	{													// 필요한 경우 행렬 초기화 ( glLoadIdentity ( ); )
		glPopMatrix();											// 변환 적용: 이동, 회전, 신축 등 모델에 적용 할 변환 함수를 호출한다.
	}

	else if (KEY == KeyZ)							// 변환이 끝난 후에는 원래의 좌표시스템을 다시 저장하기 위하여 glPopMatrix 함수 호출
	{
		glPopMatrix();								// 결과 출력
	}
	else if (Animation == true)
	{
		glPopMatrix();
		

	}

	STATE = NORMAL;
	glDisable(GL_DEPTH_TEST);
	glutSwapBuffers();

}
void Reshape(int w, int h)
{
	// 뷰포트 변환 설정: 출력 화면 결정
	glViewport(0, 0, w, h);
	// 클리핑 변환 설정: 출력하고자 하는 공간 결정
	// 아래 3줄은 투영을 설정하는 함수
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// 원근 투영을 사용하는 경우:
	gluPerspective(60.0, 1.0, 1.0, 1000.0);
	glTranslatef(0.0, 0.0, -300.0);
	// glOrtho (0.0, 800.0, 0.0, 600.0, -1.0, 1.0);
	// 모델링 변환 설정: 디스플레이 콜백 함수에서 모델 변환 적용하기 위하여 Matrix mode 저장
	glMatrixMode(GL_MODELVIEW);
	// 관측 변환: 카메라의 위치 설정 (필요한 경우, 다른 곳에 설정 가능)
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
		//ambient light 높게
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
		//ambient light 낮게
	}
	if (key == 'd')
	{
		DiffuseR-= 0.1f;
		DiffuseG-= 0.1f;
		DiffuseB-= 0.1f;
		DiffuseA-= 0.1f;
		//diffuse light 낮게
	}
	if (key == 'D')
	{
		DiffuseR+= 0.1f;
		DiffuseG+= 0.1f;
		DiffuseB+= 0.1f;
		DiffuseA+= 0.1f;
		//diffuse light 낮게
	}
	if (key == 'S')
	{
		SpecularR+= 0.1f;
		SpecularG+= 0.1f;
		SpecularB+= 0.1f;
		SpecularA+= 0.1f;
		//diffuse light 낮게
	}
	if (key == 's')
	{
		SpecularR-= 0.1f;
		SpecularG-= 0.1f;
		SpecularB-= 0.1f;
		SpecularA-= 0.1f;
			//diffuse light 낮게
	}

	if (key == '1')
	{
		//1번조명 킨다 / 끈다
		static int Cnt= 0;
		Cnt++;
		if(Cnt % 2 ==0)
			LeftBackLightSwtich = false;
		if (Cnt % 2 == 1)
			LeftBackLightSwtich = true;
	}
	if (key == '2')
	{
		static int Cnt = 0;
		Cnt++;
		if (Cnt % 2 == 0)
			RightBackLightSwtich = false;
		if (Cnt % 2 == 1)
			RightBackLightSwtich = true;
	}
	if (key == '3')
	{
		static int Cnt = 0;
		Cnt++;
		if (Cnt % 2 == 0)
			LeftFrontLightSwtich = false;
		if (Cnt % 2 == 1)
			LeftFrontLightSwtich = true;
	}
	if (key == '4')
	{
		static int Cnt = 0;
		Cnt++;
		if (Cnt % 2 == 0)
			RightFrontLightSwtich = false;
		if (Cnt % 2 == 1)
			RightFrontLightSwtich = true;
	}
	if (key == '0')
	{
		Animation = true;
	}
}
void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
	glutTimerFunc(100, TimerFunction, 1);
}
