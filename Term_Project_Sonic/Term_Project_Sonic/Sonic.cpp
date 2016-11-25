#include "Sonic.h"
#pragma once
CSonic::CSonic(void)
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_Speed = 0;

}
CSonic::~CSonic(void)
{

}
void CSonic::XMove(float speed)
{
	
	//glPushMatrix();
		glTranslatef(m_x + speed,0,0);
	//glPopMatrix();
}
void CSonic::ZMove(float speed)
{

	//glPushMatrix();
	glTranslatef(0, 0, m_z + speed);
	//glPopMatrix();
}
CSonic* CSonic::Create(void)
{
	CSonic*	pInstance = new CSonic;

	glPushMatrix();
	return pInstance;
}

void CSonic::Release(void)
{

	delete this;
}
void CSonic::Draw(void)
{
	//머리
	glPushMatrix();
	glColor3f(0, 0, 0.8);
	glutSolidSphere(30,30,30);

	glColor3f(0, 0, 0); //와이어 
	glutWireSphere(30, 15, 15);

	//몸통
	glTranslatef(0,-65,0);
	glColor3f(0, 0.1, 0.7);
	glutSolidSphere(35, 30, 30);
	glColor3f(0, 0,0);
	glutWireSphere(35, 30, 30);
	
	//팔 왼쪽
	static float MoveArm = 75.0f;
	//MoveArm += 3.0f;
	glRotatef(MoveArm, 1, 0, 0);
	glTranslatef(35, 0, 20);
	
	glColor3f(1, 1, 1);
	glScalef(1,1,6);
	glutSolidCube(10);
	glColor3f(0, 0, 0);
	glutWireCube(10);

	

	glPopMatrix(); //머리 원점
	
	glPushMatrix();
	static float MoveRightArm = 75.0f;
		//MoveRightArm -= 3.0f;
		glTranslatef(0, -75, 0);
		glTranslatef(35, 0, 20);
		//팔오른쪽
		glTranslatef(-70, 0, 0);
		glRotatef(MoveRightArm,1,0,0);
		glScalef(1, 1, 6);
		glColor3f(1, 1, 1);
		//glScalef(1, 1, 6);
		glutSolidCube(10);
		glColor3f(0, 0, 0);
		glutWireCube(10);

	glPopMatrix();
	
	glPushMatrix();
	
	glTranslatef(0, -65, 0); //몸통 중심 
	glTranslatef(0, -30, 0);
	glTranslatef(15, 0, 0); //왼쪽
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	glScalef(1, 1, 10);
	glutSolidCube(10);

	//다리 발 시작
	glColor3f(0,1,1);
	glTranslatef(0,0,5.5);
	glScalef(1, 1, 0.1);
	glutSolidCube(10);


	glPopMatrix();

	//반댓 발 
	glPushMatrix();

	glTranslatef(0, -65, 0); //몸통 중심 
	glTranslatef(0, -30, 0);
	glTranslatef(-15, 0, 0); //왼쪽
	glRotatef(90, 1, 0, 0);
	glColor3f(0, 0, 0);
	glScalef(1, 1, 10);
	glutSolidCube(10);

	//다리 발 시작
	glColor3f(0, 1, 1);
	glTranslatef(0, 0, 5.5);
	glScalef(1, 1, 0.1);
	glutSolidCube(10);


	glPopMatrix();

	

	//머리부터 다리 까지

	//헤어디자인
	glPushMatrix();
	glTranslatef(0,50,0);
	glRotatef(90,1,0,0);
	glColor3f(1.0,0.0,0);
	glutSolidCone(10,10,5,5);
	glColor3f(0,0,0);
	glutWireCone(10, 10, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-40, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-80, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();


	//오른쪽 뿔

	glPushMatrix();
	glRotatef(25, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 50, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(1.0, 0.0, 0);
	glutSolidCone(10, 10, 5, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 10, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-40, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-80, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPopMatrix();

	//왼쪽뿔

	glPushMatrix();
	glRotatef(-25, 0, 1, 0);

	glPushMatrix();
	glTranslatef(0, 50, 0);
	glRotatef(90, 1, 0, 0);
	glColor3f(1.0, 0.0, 0);
	glutSolidCone(10, 10, 5, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 10, 5, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-60, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-40, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-20, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(0, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPushMatrix();
	glRotatef(-80, 1, 0, 0);
	glTranslatef(0, 30, 0);
	glRotatef(270, 1, 0, 0);
	glColor3f(0.0, 0.0, 1);
	glutSolidCone(10, 15, 15, 5);
	glColor3f(0, 0, 0);
	glutWireCone(10, 15, 15, 5);
	glPopMatrix();

	glPopMatrix();


	//라스트 pop
	glPopMatrix();

	glPopMatrix();
}