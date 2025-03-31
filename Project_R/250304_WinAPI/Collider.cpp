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
    //실제 충돌검사는 collidermanager에서 
}

void Collider::Render(HDC hdc)
{
    if (isActive)
    {
        //충돌 시 빨간색/ 아니면 녹색
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

    // 두 충돌 영역이 유효한지 확인
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