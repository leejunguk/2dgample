#include "Defines.h"
#include "Sonic.h"
#include "Object.h"
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
const int FirstScene = 1;
int viewScene = FirstScene;

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

CSonic* Sonic = NULL;
CObject* Ring;




GLfloat ctrlpoints[3][3][3] = {};

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



//소닉 클래스 생성


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
	glutMouseFunc(Mouse);
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
	
	srand(unsigned(time(NULL)));
}

// 렌더링을 위한 디스플레이 콜백 함수: 모든 그리기 명령은 이 함수에서 대부분 처리 함
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // 윈도우, 깊이 버퍼 클리어 하기
	glEnable(GL_DEPTH_TEST);
	//glLoadIdentity();

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


	//곡선 그리기 씬
	
	
		if (STATE == MoveXPlus)
		{
			for (int i = 0; i < 3; ++i)
			{

				ctrlpoints[i][1][1]++;
			}

		}
		if (STATE == MoveXMinus)
		{
			for (int i = 0; i < 3; ++i)
			{

				ctrlpoints[i][1][1]--;
			}

		}

		// 곡면 제어점 설정
		glPushMatrix();
		glColor3f(1, 0.2, 0.2);
		glTranslatef(0, -150, +20);
		glScalef(50, 20, 20);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);

		// 그리드를 이용한 곡면 드로잉
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);

		// 선을 이용하여 그리드 연결
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glPointSize(2.0); glColor3f(0.0, 0.0, 1.0);


		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3fv(ctrlpoints[i][j]);
		glEnd();		glPopMatrix();
		//

		//왼쪽나무
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
		//충돌체크 박스
		glutWireCube(20);
		//나뭇잎
		static float leafAng = 45.0f;
		glTranslatef(0, 4, 0);
		leafAng += 5;
		glRotatef(leafAng, 0, 1, 0);
		glColor3f(0.0f, 1.0f, 0.2f);
		glScalef(15, 1, 6);
		glutSolidCube(4);
		glPopMatrix();

		Sonic = Sonic->Create();
		Ring = Ring->Create();

		Ring->SetSpeed(5);
		Sonic->SetSpeed(5);
		
		static float speed = 0.0f;
		speed += 1;

		glPushMatrix();

		//Sonic->ZMove(speed);
		
		Sonic->Draw();

		glPopMatrix();
		
		glPushMatrix();
		Ring->ZMove(speed);
		Ring->Draw();
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
		glDisable(GL_DEPTH_TEST);
		glutSwapBuffers();
	
		Sonic->Release();
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
		glTranslatef(0.0, 0.0, -350.0);
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
	
	if (key == '1')
	{
		KEY = KeyX;
		view--;
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
	
}
void TimerFunction(int value)
{
	glutPostRedisplay(); // 화면 재출력을 위하여 디스플레이 콜백 함수 호출
	glutTimerFunc(100, TimerFunction, 1);
}
void Mouse(int button, int state, int x, int y)
{
	
}
