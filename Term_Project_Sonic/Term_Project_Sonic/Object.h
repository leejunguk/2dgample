
#include "Defines.h"
#pragma once

//class Create pushmatrix
// ��ȯ 
// ��ο�
// popmatrix ������ �Լ��� ����.
class CObject
{
private:
	CObject::CObject(void);
	CObject::~CObject(void);
private:
	float m_x;
	float m_y;
	float m_z;
	float m_Speed;


public:
	CObject* CObject::Create(void);
	void CObject::Release(void);
	void CObject::Draw(void);
	void CObject::XMove(float speed);
	void CObject::ZMove(float speed);
	inline void CObject::SetSpeed(float xspeed) { m_Speed = xspeed; };
};