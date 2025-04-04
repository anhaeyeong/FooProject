#include "Item.h"

void Item::Init()
{	
}

void Item::Update()
{
	if (pos.x > WINSIZE_X || pos.y > WINSIZE_Y || pos.x < 0 || pos.y <0)
	{
		pos = { static_cast<float>(rand() % (WINSIZE_X - 50)),
			static_cast<float>(rand() % (WINSIZE_Y - 50)) }; 
	}
	else
	{
		Move();
	}

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
}

void Item::Move()
{
	pos.x += (rand() % 2 == 0 ? moveSpeed : -moveSpeed) * TimerManager::GetInstance()->GetDeltaTime() * 500;
	pos.y += moveSpeed * TimerManager::GetInstance()->GetDeltaTime() * 500;

}

void Item::UpdateCollisionRect()
{
	rect = GetRectAtCenter(pos.x, pos.y, size, size);
}

Item::Item()
{
}

Item::~Item()
{
}

void MineralItem::Init()
{
	moveSpeed = 0.1f;
	pos = { static_cast<float> (rand() % (WINSIZE_X - 100)),
			static_cast<float> (rand() % (WINSIZE_Y - 100)) };
	size = 30;
	isActived = true;
	type = eItemType::MINERAL;
	ImageManager::GetInstance()->AddImage(
		"A_missile", TEXT("Image/mineral.bmp"), 14 * 2, 13 * 2,1,1,
		true, RGB(89, 164, 81));
	image = ImageManager::GetInstance()->FindImage("A_missile");

}

void MineralItem::Render(HDC hdc)
{
	if (image && isActived == true)
	{
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
	}
}

MineralItem::MineralItem()
{
}

MineralItem::~MineralItem()
{
}

void GasItem::Init()
{
	moveSpeed = 0.1f;
	pos = { static_cast<float> (rand() % (WINSIZE_X - 100)), 
			static_cast<float> (rand() % (WINSIZE_Y - 100)) };
	size = 30;
	isActived = true;
	type = eItemType::GAS;
	if (isActived)
	{
		ImageManager::GetInstance()->AddImage(
			"B_missile", TEXT("Image/gas.bmp"), 11 * 2, 14 * 2, 1, 1,
			true, RGB(89, 164, 81));
		image = ImageManager::GetInstance()->FindImage("B_missile");
	}
}

void GasItem::Render(HDC hdc)
{
	if (image && isActived == true)
	{
		image->FrameRender(hdc, pos.x, pos.y, 0, 0);
	}
}

GasItem::GasItem()
{
}

GasItem::~GasItem()
{
}
