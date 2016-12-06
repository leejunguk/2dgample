#include "SnowBall.h"



CSnowBall::CSnowBall(void)
{
	
	
}
CSnowBall::~CSnowBall(void)
{
	
}
void CSnowBall::InitPosition(float x, float y, float z)
{

	m_x = x;
	m_y = y;
	m_z = z;
	
}
void CSnowBall::Draw(void)
{
	glColor3f(1,1,1);
	glutSolidSphere(5,30,30);
}
void CSnowBall::Move(float Speed)
{
	if (m_y - Speed <= -200)
		m_Delete = true;
	glTranslatef(m_x,m_y - Speed,m_z);
}
CSnowBall* CSnowBall::Create()
{
	
	CSnowBall*	pInstance = new CSnowBall;
	return pInstance;
}
void CSnowBall::Relase(void)
{
	delete this;
}
bool CSnowBall::GetDelete(void)
{
	return m_Delete;
}