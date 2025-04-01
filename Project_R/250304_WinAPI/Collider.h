#pragma once
#include "GameObject.h"
//�浹����� �ް� �浹ü 2���� ���� �浹�˻�

class Collider :public GameObject
{
private:
	RECT colliderBox;
	bool isCollision;
	bool isActived;

public:
	void Init();
	void Release();
	void Update();

	void ItemCheck();
	void DamageCheck();

	bool isColliding();
	//�浹ü �˻�
    bool CheckCollision(const Collider* other) const;

    //�浹 ���� ������Ʈ
    void UpdateRect(float x, float y, float width, float height);

    //�浹ü ������ ����,Ȯ��
   
    //�浹ü ���� Ȯ��
    RECT GetRect() const { return rect; }

    //�浹 ���� Ȯ��
    bool IsColliding() const { return isCollision; }
    void SetCollision(bool state) { isCollision = state; }

    // Ȱ��ȭ ���� ��ȸ/����
    bool IsActive() const { return isActive; }
    void SetActive(bool state) { isActive = state; }
	Collider();
	~Collider();
};

