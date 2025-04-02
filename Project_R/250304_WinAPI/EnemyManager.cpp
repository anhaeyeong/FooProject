#include "EnemyManager.h"
#include "Enemy.h"
#include "ColliderManager.h"

void EnemyManager::Init()
{
	// 1. 배열
	//enemys = new Enemy[10];
	//for (int i = 0; i < 10; i++)
	//{
	//	enemys[i].Init();
	//}

	// 2. vector
	/*
		push_back() 함수의 단점 : 
	*/
	//for (int i = 0; i < 10; i++)
	//{
	//	vecEnemys.push_back(new Enemy);
	//	vecEnemys[i]->Init();
	//}

	vecEnemys.resize(10);
	for (int i = 0; i < 10; i++)
	{
		vecEnemys[i] = new Enemy();
		vecEnemys[i]->Init(10.0f + 60.0f * (i % 5) , 
			80.0f + 90.0f * (i / 5));
		// 초기 충돌 박스 설정
		vecEnemys[i]->UpdateCollisionRect();
		ColliderManager::GetInstance()->AddEnemy(vecEnemys[i]);
		
	}
}

void EnemyManager::Release()
{
	for (int i = 0; i < 10; i++)
	{
		delete vecEnemys[i];
	}
	vecEnemys.clear();	// 원소가 모두 제거되고 capacity는 유지된다.
}

void EnemyManager::Update()
{

	for (int i = 0; i < vecEnemys.size(); i++)
	{
		vecEnemys[i]->Update();
	}
}

void EnemyManager::Render(HDC hdc)
{
	for (int i = 0; i < vecEnemys.size(); i++)
	{
		vecEnemys[i]->Render(hdc);
	}
}

void EnemyManager::AddEnemy(int size)
{
	for (int i = 0; i < size; i++)
	{
		vecEnemys.push_back(new Enemy());
		vecEnemys.back()->Init();
		vecEnemys.back()->UpdateCollisionRect(); 
		ColliderManager::GetInstance()->AddEnemy(vecEnemys.back());
	}
}
