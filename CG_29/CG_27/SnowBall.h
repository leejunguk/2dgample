#include <gl/glut.h>
#include <time.h>
#include <iostream>// 헤더 파일
#pragma once

class CSnowBall
{
public:
	CSnowBall::CSnowBall(void);
	CSnowBall::~CSnowBall(void);
private:
	float m_x;
	float m_y;
	float m_z;
	int   m_index;
	bool  m_Delete;
public:
	void CSnowBall::Draw(void);
	void CSnowBall::Move(float Speed);
	static CSnowBall* CSnowBall::Create();
	void CSnowBall::Relase(void);
	void CSnowBall::InitPosition(float x, float y, float z);
	bool CSnowBall::GetDelete(void);


};