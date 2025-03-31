#include "Collider.h"
#include "CommonFunction.h"

void Collider::Init()
{
    isCollision = false;
    isActive = true;
    rect = RECT{ 0, 0, 0, 0 };
    owner = nullptr;
    type = eColliderType::ROCKET;
}

void Collider::Update()
{
    //���� �浹�˻�� collidermanager���� 
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

bool Collider::CheckCollision(const Collider* other) const
{
    if (other == nullptr) return false;

    // �� �浹 ������ ��ȿ���� Ȯ��
    if (rect.left != rect.right &&
        rect.top != rect.bottom &&
        other->rect.left != other->rect.right &&
        other->rect.top != other->rect.bottom)
    {
        return RectInRect(rect, other->rect);
    }
    return false;
}

void Collider::UpdateRect(float x, float y, float width, float height)
{
    rect = GetRectAtCenter(x, y, width, height);
}