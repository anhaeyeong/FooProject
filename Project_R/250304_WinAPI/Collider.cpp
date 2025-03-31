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
    //�浹üũ���� �÷��̾�,�̻���,������ ����ü(Ÿ��, ��ġ����, RECT����) �޾Ƽ� ����
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
    //�浹�ڽ��� ��ȿ���� Ȯ�� (ũ�Ⱑ 0�� �ƴ���)
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
