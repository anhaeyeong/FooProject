#include "Item.h"

void Item::Init()
{	
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
	pos = { static_cast<float> (rand() % (WINSIZE_X - 100)),
			static_cast<float> (rand() % (WINSIZE_Y - 100)) };
	size = 30;
	isActived = true;
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
	pos = { static_cast<float> (rand() % (WINSIZE_X - 100)), 
			static_cast<float> (rand() % (WINSIZE_Y - 100)) };
	size = 30;
	isActived = true;

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
