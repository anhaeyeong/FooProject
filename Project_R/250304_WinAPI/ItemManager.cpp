#include "ItemManager.h"
#include "ColliderManager.h"
#include "Image.h"
#include "Item.h"

void ItemManager::Init()
{
	vecItems.clear();
	vecItems.resize(5);

	for (auto& item : vecItems)
	{
		int randNum = rand() % 2 + 3;
		switch (randNum)
		{
		case 3:
			item = new MineralItem();
			item->Init();
			ColliderManager::GetInstance()->AddItem(item);
			break;
		case 4:
			item = new GasItem();
			item->Init();
			ColliderManager::GetInstance()->AddItem(item);
			break;
		default:
			break;
		}
	}
}

void ItemManager::Update()
{
    bool allInactive = true;

    for (auto& item : vecItems)
    {
        if (item && item->GetIsActived())
        {
            allInactive = false;
            item->Update();
        }
    }

    // 모든 아이템이 비활성화되면 새로운 아이템 생성
    if (allInactive)
    {
        // 기존 아이템 정리
        for (auto& item : vecItems)
        {
            if (item)
            {
                item->Release();
                delete item;
                item = nullptr;
            }
        }
        vecItems.clear();

        // 새 아이템 생성
        vecItems.reserve(5);
        for (int i = 0; i < 5; i++)
        {
            Item* item = nullptr;
            int randNum = rand() % 2 + 3;

            switch (randNum)
            {
            case 3:
                item = new MineralItem();
                break;
            case 4:
                item = new GasItem();
                break;
            default:
                break;
            }

            if (item)
            {
                item->Init();
                vecItems.push_back(item);

                // ColliderManager에 아이템 등록
                ColliderManager::GetInstance()->AddItem(item);
            }
        }
    }
}

void ItemManager::Render(HDC hdc)
{
	for (auto& item : vecItems)
	{
        if (item)
        {
            item->Render(hdc);
        }
	}
}

void ItemManager::Release()
{
	for (auto& item : vecItems)
	{
		item->Release();
		delete item;
		item = nullptr;
	}
}

ItemManager::ItemManager()
{
}

ItemManager::~ItemManager()
{
}
