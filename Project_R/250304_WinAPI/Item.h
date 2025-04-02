#pragma once
#include "GameObject.h"

enum class eItemType
{
	ZONYA
};
class Item :public GameObject
{
private:
	FPOINT pos;
	int size;
	bool isActived; //아이템상자 활성화여부
	RECT rect;
public:
	
	void Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	RECT GetRect() const{ return rect; }
	inline FPOINT GetPos() const{ return pos; }
	inline RECT GetRectAtCenter(int x, int y, int width, int height)
	{
		RECT rc{ x - (width / 2), y - (height / 2),
			x + (width / 2), y + (height / 2) };
		return rc;
	}

	Item();
	~Item();
};

