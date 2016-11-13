#include <gl/glut.h>
#include <iostream>// 헤더 파일
using namespace std;
// 필요한 전역 변수 선언
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
	ball->x = 0;
	ball->y = 0;
	ball->z = 0;
}

// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기

	glLoadIdentity();

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

	//땅
	glPushMatrix();
	glColor3f(1.0f, 1.0f, 0.0f);
	glTranslatef(0, -100, 50);
	glScalef(50, 0.2, 30);
	glutSolidCube(5);
	glPopMatrix();



	// 좌표계 끝

	//  왼쪽 도형
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

	//오른쪽
	
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
	}													//--- 변환을 적용하기 위해서
	else if (KEY == KeyY)													// glPushMatrix 함수를 호출하여 기존의 좌표 시스템을 저장
	{													// 필요한 경우 행렬 초기화 ( glLoadIdentity ( ); )
		glPopMatrix();											// 변환 적용: 이동, 회전, 신축 등 모델에 적용 할 변환 함수를 호출한다.
	}

	else if (KEY == KeyZ)							// 변환이 끝난 후에는 원래의 좌표시스템을 다시 저장하기 위하여 glPopMatrix 함수 호출
	{
		glPopMatrix();								// 결과 출력
	}

	STATE = NORMAL;

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
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
	glutTimerFunc(100, TimerFunction, 1);
}
