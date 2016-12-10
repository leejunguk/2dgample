#include "Sonic.h"
#pragma once
CSonic::CSonic(void)
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_Speed = 0;
	collideCheck = false;
}
CSonic::~CSonic(void)
{

}
void CSonic::XMove(float speed)
{
	m_x = m_x + speed;
	//glPushMatrix();
		glTranslatef(m_x ,0,0);
	//glPopMatrix();
}
void CSonic::ZMove(float speed)
{
	m_z = m_z + speed;
	//cout << m_z << endl;
	//glPushMatrix();
	glTranslatef(m_x, m_y, m_z );
	//glPopMatrix();
}
CSonic* CSonic::Create(void)
{
	CSonic*	pInstance = new CSonic;

	
	return pInstance;
}

void CSonic::Release(void)
{

	delete this;
}
void CSonic::Draw(void)
{

	//��ü �ܹ��� ǥ��
	glPushMatrix();

	

	if (collideCheck == true)
	{
		cout << " check" << endl;
	}
	else
	{
		static int RUNFRAME = 0;
		static int RUNCNT = 0;
		RUNFRAME++;
		if (4 <= RUNFRAME)
		{
			RUNCNT++;
			RUNFRAME = 0;
		}
		if (RUNCNT % 2 == 1)
			glTranslatef(10, 0, 0);
		if (RUNCNT % 2 == 0)
			glTranslatef(-10,0 , 0);

		//�Ӹ�
		glPushMatrix();
		glTranslatef(0, -65, 0);
		glColor3f(0, 0, 0.8);
		glutSolidSphere(30, 30, 30);

		glColor3f(0, 0, 0); //���̾� 
	//	glutWireSphere(30, 15, 15);
		glPopMatrix();

		//����

		glPushMatrix();
		glTranslatef(0, -65, 0);
		glColor3f(0, 0.1, 0.7);
		glutSolidSphere(35, 30, 30);
		glColor3f(0, 0, 0);
		//	glutWireSphere(35, 30, 30);
		glPopMatrix();

		//�� ����

		glPushMatrix();
		glTranslatef(0, -65, 0);

		static float MoveArm = 60.0f;
		static bool isSwinglast = false;
		if (90 <= MoveArm)
		{
			isSwinglast = false;
		}
		if (30 >= MoveArm)
		{
			isSwinglast = true;
		}
		if (isSwinglast == true)
		{
			MoveArm += 10.0f;
		}
		if (isSwinglast == false)
		{
			MoveArm -= 10.0f;
		}

		glRotatef(MoveArm, 1, 0, 0);
		glTranslatef(35, 0, 20);
		glColor3f(0, 0, 0);
		glScalef(1, 1, 3);
		glutSolidCube(10);
		glColor3f(0, 0, 0);
		//	glutWireCube(10);
		glPopMatrix();



		//������
		glPushMatrix();


		glTranslatef(0, -65, 0); //������� trans


		static float MoveArm1 = 60.0f;
		static bool isSwinglast1 = false;
		if (90 <= MoveArm1)
		{
			isSwinglast1 = true;
		}
		if (30 >= MoveArm1)
		{
			isSwinglast1 = false;
		}
		if (isSwinglast1 == true)
		{
			MoveArm1 -= 10.0f;
		}
		if (isSwinglast1 == false)
		{
			MoveArm1 += 10.0f;
		}


		glRotatef(MoveArm1, 1, 0, 0);
		glTranslatef(-35, 0, 20); //������

		glScalef(1, 1, 3);
		glColor3f(0, 0, 0);
		//glScalef(1, 1, 6);
		glutSolidCube(10);
		glColor3f(0, 0, 0);
		//	glutWireCube(10);

		glPopMatrix();


		//���ʴٸ�
		glPushMatrix();
		static float Moveleg = 0.0f;
		static bool isSwinglastleg = false;
		if (30 <= Moveleg)
		{
			isSwinglastleg = true;
		}
		if (-30 >= Moveleg)
		{
			isSwinglastleg = false;
		}
		if (isSwinglastleg == true)
		{
			Moveleg -= 15.0f;
		}
		if (isSwinglastleg == false)
		{
			Moveleg += 15.0f;
		}


		glTranslatef(0, -65, 0); //���� �߽� 
		glRotatef(Moveleg, 1, 0, 0);
		glTranslatef(0, -30, 0);


		glTranslatef(15, 0, 0); //����

		glRotatef(90, 1, 0, 0);
		glColor3f(0, 0, 0);
		glScalef(1, 1, 6);
		glutSolidCube(10);

		//�ٸ� �� ����
		glColor3f(1, 0, 0);
		glTranslatef(0, 0, 5.5);
		glScalef(1, 1, 0.1);
		glutSolidCube(10);


		glPopMatrix();

		//�ݴ� �� 
		glPushMatrix();

		glTranslatef(0, -65, 0); //���� �߽� 
		glRotatef(-Moveleg, 1, 0, 0);
		glTranslatef(0, -30, 0);
		glTranslatef(-15, 0, 0); //����
		glRotatef(90, 1, 0, 0);
		glColor3f(0, 0, 0);
		glScalef(1, 1, 6);
		glutSolidCube(10);

		//�ٸ� �� ����
		glColor3f(1, 0, 0);
		glTranslatef(0, 0, 5.5);
		glScalef(1, 1, 0.1);
		glutSolidCube(10);


		glPopMatrix();



		//�Ӹ����� �ٸ� ����

		//��������

		glPushMatrix();
		glTranslatef(0, -65, 0);

		//glPushMatrix();
		//glTranslatef(0, 50, 0);
		//glRotatef(90, 1, 0, 0);
		//glColor3f(1.0, 0.0, 0);
		////glutSolidCone(10, 10, 5, 5);
		//glColor3f(0, 0, 0);
		////glutWireCone(10, 10, 5, 5);
		//glPopMatrix();

		glPushMatrix();
		glRotatef(-60, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-40, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-20, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(0, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-80, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();


		//������ ��

		glPushMatrix();
		glRotatef(25, 0, 1, 0);

		glPushMatrix();
		glTranslatef(0, 50, 0);
		glRotatef(90, 1, 0, 0);
		/*glColor3f(1.0, 0.0, 0);
		glutSolidCone(10, 10, 5, 5);*/
		glColor3f(0, 0, 0);
		//glutWireCone(10, 10, 5, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-60, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-40, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-20, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(0, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-80, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPopMatrix();

		//���ʻ�

		glPushMatrix();
		glRotatef(-25, 0, 1, 0);

		glPushMatrix();
		glTranslatef(0, 50, 0);
		glRotatef(90, 1, 0, 0);
	/*	glColor3f(1.0, 0.0, 0);
		glutSolidCone(10, 10, 5, 5);*/
		glColor3f(0, 0, 0);
		//glutWireCone(10, 10, 5, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-60, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-40, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-20, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(0, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();

		glPushMatrix();
		glRotatef(-80, 1, 0, 0);
		glTranslatef(0, 30, 0);
		glRotatef(270, 1, 0, 0);
		glColor3f(0.0, 0.0, 1);
		glutSolidCone(10, 15, 15, 5);
		glColor3f(0, 0, 0);
		//glutWireCone(10, 15, 15, 5);
		glPopMatrix();


		//�Ը�������
		glPopMatrix();


		//��Ʈ pop

		glPopMatrix();
	}

	//��ü �ܹ��� ǥ��
	glPopMatrix();
}