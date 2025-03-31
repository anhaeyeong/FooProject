#include "Collider.h"
#include "CommonFunction.h"

void Collider::Init()
{
    isCollision = false;
    attackerRect = RECT{ 0, 0, 0, 0 };
    targetRect = RECT{ 0, 0, 0, 0 };
}

void Collider::Update()
{
    //충돌체크전에 플레이어,미사일,적한테 구조체(타입, 위치정보, RECT정보) 받아서 설정
    CheckCollision();
}

void Collider::Render(HDC hdc)
{
}

Collider::Collider(eColliderType attacker, eColliderType target) :
    attackerType{ attacker }, targetType{ target }, isCollision{ false }
{

}

Collider::~Collider()
{
}

bool Collider::CheckCollision()
{
    //충돌박스가 유효한지 확인 (크기가 0이 아닌지)
    if (attackerRect.left != attackerRect.right &&
        attackerRect.top != attackerRect.bottom &&
        targetRect.left != targetRect.right &&
        targetRect.top != targetRect.bottom)
    {
        isCollision = RectInRect(attackerRect, targetRect);
    }
    else
    {
        isCollision = false;
    }

    return isCollision;
}

void Collider::UpdateAttackerRect(float x, float y, float width, float height)
{
    attackerRect = GetRectAtCenter(x, y, width, height);
}

void Collider::UpdateTargetRect(float x, float y, float width, float height)
{
    targetRect = GetRectAtCenter(x, y, width, height);
}
