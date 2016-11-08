#include <gl/glut.h> // ��� ����
// �ʿ��� ���� ���� ����
int KEY = 0;

const int KeyX = 1;
const int KeyY = 2;
const int KeyZ = 3;
const int KeyLeft = 4;
const int KeyRight = 5;


void Keyboard(unsigned char key, int x, int y);
void TimerFunction(int value);
void Reshape(int w, int h);
void DrawScene();
void SetupRC();
void main()
{
	// ������ �ʱ�ȭ �� ����
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutInitWindowSize(800	, 600);
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
}

// �������� ���� ���÷��� �ݹ� �Լ�: ��� �׸��� ����� �� �Լ����� ��κ� ó�� ��
void DrawScene()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������, ���� ���� Ŭ���� �ϱ�
	
	glLoadIdentity();

	//gluPerspective(45,1, 1.0, 400.0);// �ʿ��� ��ȯ ����
	
	static float ratio = 0;
	static float view = 0;
	if (KEY == KeyX)
	{
		glPushMatrix();
		glRotatef(view++, 1, 0, 0);
	}
	else if (KEY == KeyY)
	{
		glPushMatrix();
		glRotatef(view++, 0, 1, 0);

	}
	else if (KEY == KeyZ)
	{
		glPushMatrix();
		glRotatef(view++, 0, 0, 1);

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
		glTranslatef(-50,-100,0);
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
	glColor3f(0.0f, 0.0f, 1.0f);
	glTranslatef(+50, -100, +30);
	if (KEY == KeyRight)
	{
		glRotatef(ratio++,1,0,0);
	}
		glutWireSphere(20,20,20);
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
		KEY = KeyX;
	}
	if (key == 'y' || key == 'Y')
	{
		KEY = KeyY;
	}
	if (key == 'z' || key == 'Z')
	{
		KEY = KeyZ;
	}
	if (key == 'l' || key == 'L')
	{
		KEY = KeyLeft;
	}
	if (key == 'r' || key == 'R')
	{
		KEY = KeyRight;
	}
}
void TimerFunction(int value)
{
	glutPostRedisplay(); // ȭ�� ������� ���Ͽ� ���÷��� �ݹ� �Լ� ȣ��
	glutTimerFunc(100, TimerFunction, 1);
}
