#include "Object.h"
#pragma once
CObject::CObject(void)
{
	m_x = 0;
	m_y = 0;
	m_z = 0;
	m_Speed = 0;

}
CObject::~CObject(void)
{

}
void CObject::XMove(float speed)
{

	//glPushMatrix();
	glTranslatef(m_x + speed, 0, 0);
	//glPopMatrix();
}
void CObject::ZMove(float speed)
{

	//glPushMatrix();
	glTranslatef(0, 0, m_z -speed);
	//glPopMatrix();
}
CObject* CObject::Create(void)
{
	CObject*	pInstance = new CObject;


	return pInstance;
}

void CObject::Release(void)
{

	delete this;
}
void CObject::Draw(void)
{

	//전체 뜀박질 표현
	glPushMatrix();
	static int RUNFRAME = 0;
	static int RUNCNT = 0;
	RUNFRAME++;
	if (4 <= RUNFRAME)
	{
		RUNCNT++;
		RUNFRAME = 0;
	}
	if (RUNCNT % 2 == 1)
		glTranslatef(0, 10, 0);
	if (RUNCNT % 2 == 0)
		glTranslatef(0, -10, 0);

	glColor3f(1,1,0);
	glTranslated(100,0,0);
	glutSolidTorus(5,10,10,10);

	//전체 뜀박질 표현
	glPopMatrix();
}