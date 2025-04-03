#pragma once
#include "GameObject.h"
#include <vector>
#include <ctime>

class Item;
class ItemManager :public GameObject
{
private:
	Item* item;
	vector<Item*> vecItems;

public:

	void Init();
	void Update();
	void Render();
	void Release();
	
	void SetSpawnItem();

	ItemManager();
	~ItemManager();
};

