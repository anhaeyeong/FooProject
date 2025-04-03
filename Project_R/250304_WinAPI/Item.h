#pragma once
#include "GameObject.h"

enum class eItemType
{
	MINERAL, GAS
};

class Item: public GameObject
{
private:
	FPOINT pos;
	RECT rect;
	int size;
	bool isActived; //아이템상자 활성화여부

	eItemType type;
	Image* image;
public:
	void Init();
	void Update();
	void Release();
	void Render(HDC hdc);

	void SpawnItem();
	void UpdateCollisionRect();

	RECT GetRect() const { return rect; }
	inline eItemType GetType() const { return type; }
	inline FPOINT GetPos() const { return pos; }
	inline RECT GetRectAtCenter(int x, int y, int width, int height)
	{
		RECT rc{ x - (width / 2), y - (height / 2),
			x + (width / 2), y + (height / 2) };
		return rc;
	}
	inline bool GetIsActived() const { return isActived; }
	inline void ActiveItem() { isActived = true; }
	inline void UnactiveItem() { isActived = false; }

	Item();
	~Item();
};

