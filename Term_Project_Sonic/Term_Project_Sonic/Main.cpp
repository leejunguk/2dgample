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



//�Ҵ� Ŭ���� ����


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
	glutMouseFunc(Mouse);
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
	//glLoadIdentity();

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


	//� �׸��� ��
	
	
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

		// ��� ������ ����
		glPushMatrix();
		glColor3f(1, 0.2, 0.2);
		glTranslatef(0, -150, +20);
		glScalef(50, 20, 20);
		glMap2f(GL_MAP2_VERTEX_3, 0.0, 1.0, 3, 3, 0.0, 1.0, 9, 3, &ctrlpoints[0][0][0]);
		glEnable(GL_MAP2_VERTEX_3);

		// �׸��带 �̿��� ��� �����
		glMapGrid2f(10, 0.0, 1.0, 10, 0.0, 1.0);

		// ���� �̿��Ͽ� �׸��� ����
		glEvalMesh2(GL_LINE, 0, 10, 0, 10);
		glPointSize(2.0); glColor3f(0.0, 0.0, 1.0);


		glBegin(GL_POINTS);
		for (int i = 0; i < 3; i++)
			for (int j = 0; j < 3; j++)
				glVertex3fv(ctrlpoints[i][j]);
		glEnd();		glPopMatrix();
		//

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
	
		Sonic->Release();
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
		glTranslatef(0.0, 0.0, -350.0);
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
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
	glutTimerFunc(100, TimerFunction, 1);
}
void Mouse(int button, int state, int x, int y)
{
	
}
