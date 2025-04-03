#include "Item.h"
#include "ColliderManager.h"
#include "Image.h"

void Item::Init()
{
	pos = { pos.x, pos.y };
	int size{ 10 };
	isActived = true;
	type = {};
	ImageManager::GetInstance()->AddImage(
		"A_missile", TEXT("Image/mineral.bmp"), 14, 13,
		true, RGB(82, 163, 87));
	ImageManager::GetInstance()->AddImage(
		"B_missile", TEXT("Image/gas.bmp"), 11, 14,
		true, RGB(97, 167, 81));
	image = ImageManager::GetInstance()->FindImage("A_missile");
	image = ImageManager::GetInstance()->FindImage("B_missile");

}

void Item::Update()
{
	if (isActived)
	{
		UpdateCollisionRect();
	}
}

void Item::Release()
{
}

void Item::Render(HDC hdc)
{
	if (isActived)
	{
		if (type == eItemType::GAS)
		{
			image->Render(hdc, pos.x, pos.y);
		}
		else if (type == eItemType::MINERAL)
		{
			image->Render(hdc, pos.x, pos.y);
		}
	}
}

void Item::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x, pos.y, size, size);
}

void Item::SpawnItem()
{
    //WINSIZEX, WINSIZEY안에 랜덤한위치에 랜덤하게 아이템 생성
	pos.x = rand() % (WINSIZE_X - 30);
	pos.y = rand() % (WINSIZE_Y - 30);
}

Item::Item()
{
}

Item::~Item()
{
}
