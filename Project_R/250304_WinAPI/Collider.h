#pragma once
#include "GameObject.h"
//충돌명령을 받고 충돌체 2개에 대한 충돌검사

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
	//충돌체 검사
    bool CheckCollision(const Collider* other) const;

    //충돌 영역 업데이트
    void UpdateRect(float x, float y, float width, float height);

    //충돌체 소유자 설정,확인
   
    //충돌체 영역 확인
    RECT GetRect() const { return rect; }

    //충돌 여부 확인
    bool IsColliding() const { return isCollision; }
    void SetCollision(bool state) { isCollision = state; }

    // 활성화 상태 조회/설정
    bool IsActive() const { return isActive; }
    void SetActive(bool state) { isActive = state; }
	Collider();
	~Collider();
};

