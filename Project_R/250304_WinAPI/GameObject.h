#pragma once
#include "config.h"
enum class MissileOwner { PLAYER, ENEMY };
enum class MissileType { NORMAL, SIGN, LAZER, BOSS };

class GameObject
{
public:
	void Init();		// 멤버 변수의 초기화, 메모리 할당
	void Release();		// 메모리 해제
	void Update();		// 프레임 단위로 게임 로직 실행(데이터 계산)
	void Render(HDC hdc);	// 프레임 단위로 출력(이미지, 텍스트 등)

	GameObject();
	~GameObject();
};

