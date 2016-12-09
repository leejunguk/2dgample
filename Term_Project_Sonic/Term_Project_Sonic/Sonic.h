#include "Defines.h"
#pragma once

//class Create pushmatrix
// ��ȯ 
// ��ο�
// popmatrix ������ �Լ��� ����.
class CSonic
{
private:
	CSonic::CSonic(void);
	CSonic::~CSonic(void);
private:
	float m_x;
	float m_y;
	float m_z;
	float m_Speed;
	
	
public:
	CSonic* CSonic::Create(void);
	void CSonic::Release(void);
	void CSonic::Draw(void);
	void CSonic::XMove(float speed);
	void CSonic::ZMove(float speed);
	inline void CSonic::SetSpeed(float xspeed) { m_Speed = xspeed; };
};