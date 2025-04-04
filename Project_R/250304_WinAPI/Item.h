#pragma once
#include "GameObject.h"

enum class eItemType
{
	MINERAL, GAS
};

class Item: public GameObject
{
protected:
	FPOINT pos;
	RECT rect;
	int size;
	bool isActived; //아이템상자 활성화여부
	float moveSpeed;
	eItemType type;
	Image* image;
public:
	virtual void Init();
	void Update();
	void Release();
	virtual void Render(HDC hdc);
	void Move();
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
	virtual ~Item();
};

class MineralItem : public Item
{
private:
public:

	virtual void Init() override;
	virtual void Render(HDC hdc) override;
	MineralItem();
	~MineralItem();
};

class GasItem : public Item
{
private:
public:
	virtual void Init() override;
	virtual void Render(HDC hdc) override;
	GasItem();
	~GasItem();
};

