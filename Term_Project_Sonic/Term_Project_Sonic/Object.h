
#include "Defines.h"
#pragma once

//class Create pushmatrix
// 변환 
// 드로우
// popmatrix 순으로 함수를 쓴다.
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