#include "Collider.h"
#include "Missile.h"
#include "Rocket.h"
#include "Enemy.h"
#include "CommonFunction.h"

void Collider::Init()
{
}

void Collider::Release()
{
}

void Collider::Update()
{
}

void Collider::Render(HDC hdc)
{
    if (isActive)
    {
        //�浹 �� ������/ �ƴϸ� ���
        HPEN pen = CreatePen(PS_SOLID, 2, isCollision ? RGB(255, 0, 0) : RGB(0, 255, 0));
        HPEN oldPen = (HPEN)SelectObject(hdc, pen);
        HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, GetStockObject(NULL_BRUSH));

        Rectangle(hdc, rect.left, rect.top, rect.right, rect.bottom);
        SelectObject(hdc, oldPen);
        SelectObject(hdc, oldBrush);
        DeleteObject(pen);
    }
}

Collider::Collider()
{
}

Collider::~Collider()
{
}

