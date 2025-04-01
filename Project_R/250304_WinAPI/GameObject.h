#pragma once
#include "config.h"

enum class MissileOwner { PLAYER, ENEMY };
enum class MissileType { NORMAL, SIGN, LAZER };

class GameObject
{
public:
	void Init();		// ��� ������ �ʱ�ȭ, �޸� �Ҵ�
	void Release();		// �޸� ����
	void Update();		// ������ ������ ���� ���� ����(������ ���)
	void Render(HDC hdc);	// ������ ������ ���(�̹���, �ؽ�Ʈ ��)

	GameObject();
	~GameObject();
};

