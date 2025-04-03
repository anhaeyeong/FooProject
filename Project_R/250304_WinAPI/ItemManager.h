#pragma once
#include "GameObject.h"
#include "Item.h"
#include <vector>
#include <ctime>


class ItemManager :public GameObject
{
private:
	vector<Item*> vecItems;
public:
	void Init();
	void Update();
	void RegenerateItems();
	void Render(HDC hdc);
	void Release();

	ItemManager();
	~ItemManager();
};

