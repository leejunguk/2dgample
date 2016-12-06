#include <gl/glut.h>
#include <windows.h>
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

float RotateYAnlge = 0;
float RoatateXAngle = 0;

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
CSnowBall* Snowlist = new CSnowBall[100];

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

void DrawCube();
void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void Reshape(int w, int h);
void DrawScene();
void SetupRC();
void textureBox();

GLubyte *pBytes; // 데이터를 가리킬 포인터
BITMAPINFO *info; // 비트맵 헤더 저장할 변수
GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info);
GLuint textures[6];


static float AmbientR = 0.5;
static float AmbientG = 0.5;
static float AmbientB = 0.5;
static float AmbientA = 0.5f;

static float DiffuseR = 0.5;
static float DiffuseG = 0.5;
static float DiffuseB = 0.5;
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
	glFrontFace(GL_CCW);   // 앞면 설정  
	glEnable(GL_CULL_FACE);  // 내부는 잘라낸다 

	for (int i = 0; i < 100; ++i)
	{
		Snowlist[i].InitPosition(rand()%400 -200, 100, i);
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
	GLfloat lightPos1[] = { 100.0, 0.0, 100.0, 1.0 };
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);



	glPopMatrix();
	glLightfv(GL_LIGHT0, GL_AMBIENT, AmbientLight);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, DiffuseLight);
	glLightfv(GL_LIGHT0, GL_SPECULAR, SpecularLight);
	glLightfv(GL_LIGHT0, GL_POSITION, lightPos1);
	glEnable(GL_LIGHT0);
	if (LeftBackLightSwtich == false)
		glDisable(GL_LIGHT0);


	

	//재질
	glPushMatrix();
	glRotatef(RotateYAnlge, 1, 0, 0);

	glRotatef(30, 1, 0, 0);
	glRotatef(45, 0, 1, 0);

	glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, gray);
	glMaterialfv(GL_FRONT, GL_SPECULAR, specref);
	glMateriali(GL_FRONT, GL_SHININESS, 128);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_NORMALIZE);
	//gluPerspective(45,1, 1.0, 400.0);// 필요한 변환 적용

	static float MoveSnow = 1.0f;
	MoveSnow += 1.0f;

	for (int i = 0; i < 100; ++i)
	{
		glPushMatrix();


		Snowlist[i].Move(MoveSnow);
		Snowlist[i].Draw();

		glPopMatrix();
	}


	//DrawCube();
	//textureBox();
	glPopMatrix();

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
	if (key=='w' || key=='W')
	{
		RotateYAnlge++;

	}
	if (key == 's' || key == 'S')
	{
		RotateYAnlge--;

	}
	if (key == 'q' || key == 'Q')
	{
		RoatateXAngle++;

	}
	if (key == 'e' || key == 'E')
	{
		RoatateXAngle--;

	}
	
	if (key == 'A')
	{
		//ambient light 높게
		AmbientR += 0.1f;
		AmbientG += 0.1f;
		AmbientB += 0.1f;
		AmbientA += 0.1f;
		cout << "1" << endl;;
	}
	if (key == 'a')
	{
		AmbientR -= 0.1f;
		AmbientG -= 0.1f;
		AmbientB -= 0.1f;
		AmbientA -= 0.1f;
		//ambient light 낮게
	}
	if (key == 'd')
	{
		DiffuseR -= 0.1f;
		DiffuseG -= 0.1f;
		DiffuseB -= 0.1f;
		DiffuseA -= 0.1f;
		//diffuse light 낮게
	}
	if (key == 'D')
	{
		DiffuseR += 0.1f;
		DiffuseG += 0.1f;
		DiffuseB += 0.1f;
		DiffuseA += 0.1f;
		//diffuse light 낮게
	}
	if (key == 'S')
	{
		SpecularR += 0.1f;
		SpecularG += 0.1f;
		SpecularB += 0.1f;
		SpecularA += 0.1f;
		//diffuse light 낮게
	}
	if (key == 's')
	{
		SpecularR -= 0.1f;
		SpecularG -= 0.1f;
		SpecularB -= 0.1f;
		SpecularA -= 0.1f;
		//diffuse light 낮게
	}

	if (key == '1')
	{
		//1번조명 킨다 / 끈다
		static int Cnt = 0;
		Cnt++;
		if (Cnt % 2 == 0)
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
void DrawCube()
{
	glPushMatrix();
	glScalef(30,30,30);
	glBegin(GL_QUADS);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // { Front }
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // { Front }
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f); // { Front }
	glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // { Front }

	glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, 1.0f); // { Right }
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f); // { Right }
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // { Right }
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f); // { Right }

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, 1.0f, -1.0f); // { Back }
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // { Back }
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // { Back }
	glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // { Back }

	glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // { Left }
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // { Left }
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // { Left }
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // { Left }

	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(-1.0f, 1.0f, 1.0f); // { Top }
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(1.0f, 1.0f, 1.0f); // { Top }
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(1.0f, 1.0f, -1.0f); // { Top }
	glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(-1.0f, 1.0f, -1.0f); // { Top }

	glColor3f(1.0f, 0.0f, 1.0f); glVertex3f(1.0f, -1.0f, 1.0f); // { Bottom }
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(-1.0f, -1.0f, 1.0f); // { Bottom }
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(-1.0f, -1.0f, -1.0f); // { Bottom }
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(1.0f, -1.0f, -1.0f); // { Bottom }
	glEnd();
	glPopMatrix();

}

GLubyte * LoadDIBitmap(const char *filename, BITMAPINFO **info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;
	// 바이너리 읽기 모드로 파일을 연다
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;
	// 비트맵 파일 헤더를 읽는다.
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}
	// 파일이 BMP 파일인지 확인한다.
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}
	// BITMAPINFOHEADER 위치로 간다.
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);
	// 비트맵 이미지 데이터를 넣을 메모리 할당을 한다.
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}
	// 비트맵 인포 헤더를 읽는다.
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵의 크기 설정
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth *
		(*info)->bmiHeader.biBitCount + 7) / 8.0 *
		abs((*info)->bmiHeader.biHeight);
	// 비트맵의 크기만큼 메모리를 할당한다.
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}
	// 비트맵 데이터를 bit(GLubyte 타입)에 저장한다.
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info); free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}
void textureBox()
{
	glGenTextures(6, textures);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	pBytes = LoadDIBitmap("Sponge3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[1]);
	pBytes = LoadDIBitmap("Sponge3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[2]);
	pBytes = LoadDIBitmap("Sponge3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[3]);
	pBytes = LoadDIBitmap("Sponge3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[4]);
	pBytes = LoadDIBitmap("Sponge3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, textures[5]);
	pBytes = LoadDIBitmap("Sponge3.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, 100, 100, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_COLOR, GL_MODULATE);


	glEnable(GL_TEXTURE_2D);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	//glDisable (GL_CULL_FACE);
	glPushMatrix();
	glLoadIdentity();
	glRotatef(RoatateXAngle, 1.0f, 0.0f, 0.0f);
	glRotatef(RotateYAnlge, 0.0f, 1.0f, 0.0f);
	glRotatef(0, 0.0f, 0.0f, 1.0f);
	glBindTexture(GL_TEXTURE_2D, textures[0]);
	glBegin(GL_QUADS);
	{
		glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
		//앞면
		//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
		glTexCoord2f(1, 1);
		glVertex3f(50.0, 50.0, 50.0f);
		//  glColor3f(1.0f,0.0,1.0f);  // Magenta
		glTexCoord2f(0, 1);
		glVertex3f(-50.0, 50.0, 50.0f);
		//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
		glTexCoord2f(0, 0);
		glVertex3f(-50.0, -50.0, 50.0f);
		//  glColor3f(0.0f,0.0f,1.0f);  // Blue
		glTexCoord2f(1, 0);
		glVertex3f(50.0, -50.0, 50.0f);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[1]);
	glBegin(GL_QUADS);
	{
		//뒷면
		//  glColor3f(1.0f,1.0f,1.0f);  // White
		glTexCoord2f(1, 1);
		glVertex3f(-50.0, 50.0, -50.0);
		//  glColor3f(0.0f,1.0f,0.0f);  // Green
		glTexCoord2f(0, 1);
		glVertex3f(50.0, 50.0, -50.0);
		//  glColor3f(1.0f,0.0f,0.0f);  // Red
		glTexCoord2f(0, 0);
		glVertex3f(50.0f, -50.0f, -50.0f);
		//  glColor3f(0.0f,0.0f,0.0f);  // Black
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, -50.0, -50.0);

	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[2]);
	glBegin(GL_QUADS);
	{
		//윗면
		//  glColor3f(1.0f,0.0,1.0f);  // Magenta
		glTexCoord2f(1, 1);
		glVertex3f(-50.0, 50.0, 50.0f);
		//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
		glTexCoord2f(0, 1);
		glVertex3f(50.0, 50.0, 50.0f);
		//  glColor3f(0.0f,1.0f,0.0f);  // Green
		glTexCoord2f(0, 0);
		glVertex3f(50.0, 50.0, -50.0);
		//  glColor3f(1.0f,1.0f,1.0f);  // White
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, 50.0, -50.0);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[3]);
	glBegin(GL_QUADS);
	{
		//아랫면
		//  glColor3f(1.0f,0.0f,0.0f);  // Red
		glTexCoord2f(1, 1);
		glVertex3f(50.0f, -50.0f, -50.0f);
		//  glColor3f(0.0f,0.0f,0.0f);  // Black
		glTexCoord2f(0, 1);
		glVertex3f(50.0, -50.0, 50.0f);
		//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
		glTexCoord2f(0, 0);
		glVertex3f(-50.0, -50.0, 50.0f);
		//  glColor3f(0.0f,0.0f,1.0f);  // Blue
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, -50.0, -50.0);

	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[4]);
	glBegin(GL_QUADS);
	{
		//왼면
		//  glColor3f(1.0f,0.0,1.0f);  // Magenta
		glTexCoord2f(1, 1);
		glVertex3f(-50.0, 50.0, 50.0f);
		//  glColor3f(1.0f,1.0f,1.0f);  // White
		glTexCoord2f(0, 1);
		glVertex3f(-50.0, 50.0, -50.0);
		//  glColor3f(0.0f,0.0f,0.0f);  // Black
		glTexCoord2f(0, 0);
		glVertex3f(-50.0, -50.0, -50.0);
		//  glColor3f(0.0f,1.0f,1.0f);  // Cyan
		glTexCoord2f(1, 0);
		glVertex3f(-50.0, -50.0, 50.0f);
	}
	glEnd();
	glBindTexture(GL_TEXTURE_2D, textures[5]);
	glBegin(GL_QUADS);
	{
		//오른면
		//  glColor3f(0.0f,1.0f,0.0f);  // Green
		glTexCoord2f(1, 1);
		glVertex3f(50.0, 50.0, -50.0);
		//  glColor3f(1.0f,1.0f,0.0f);  // Yellow
		glTexCoord2f(0, 1);
		glVertex3f(50.0, 50.0, 50.0f);
		//  glColor3f(0.0f,0.0f,1.0f);  // Blue
		glTexCoord2f(0, 0);
		glVertex3f(50.0, -50.0, 50.0f);
		//  glColor3f(1.0f,0.0f,0.0f);  // Red
		glTexCoord2f(1, 0);
		glVertex3f(50.0f, -50.0f, -50.0f);
	}
	glEnd();
	glPopMatrix();
	
}

