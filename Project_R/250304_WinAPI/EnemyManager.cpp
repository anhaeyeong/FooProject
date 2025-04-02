#include "EnemyManager.h"
#include "Enemy.h"
#include "ColliderManager.h"

void EnemyManager::Init()
{
    spawnInterval = 2;       // �� ���� �ֱ� (�� ����)
    elapsedTime = 0.0f;      // ���� �ð�
    maxEnemies = 10;         // �ִ� �����Ǵ� �� ��
    spawnPattern = 0;        // �⺻������ �Ϸķ� ����

	// 2. vector
	/*
		push_back() �Լ��� ���� : 
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
		// �ʱ� �浹 �ڽ� ����
		vecEnemys[i]->UpdateCollisionRect();
		ColliderManager::GetInstance()->AddEnemy(vecEnemys[i]);
		
	}

     //for (int i = 0; i < maxEnemies; i++)
     //{
     //    AddEnemy();  // �� �߰�
     //}
}

void EnemyManager::Release()
{
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        delete vecEnemys[i];
    }
    vecEnemys.clear();
}

void EnemyManager::Update()
{
    elapsedTime += 0.016f;

    if (elapsedTime >= spawnInterval)
    {
        elapsedTime = 0.0f;  // Ÿ�̸� ����
        if (vecEnemys.size() < maxEnemies)  // �ִ� �� ������ ���� ����
        {
            AddEnemy();
        }
    }

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

void EnemyManager::AddEnemy()
{
    float spawnX = 0.0f;
    float spawnY = 0.0f;

    spawnX = 10.0f + (rand() % 5) * 60.0f;  // X ��ǥ ����ȭ (���� ����)
    spawnY = 80.0f + (rand() % 3) * 90.0f; // Y ��ǥ ����ȭ (���� ����)

	for (int i = 0; i < vecEnemys.size(); i++)
	{
		vecEnemys.push_back(new Enemy());
		vecEnemys.back()->Init(spawnX, spawnY);
		vecEnemys.back()->UpdateCollisionRect(); 
		ColliderManager::GetInstance()->AddEnemy(vecEnemys.back());
	}
}

void EnemyManager::SetSpawnPattern(int pattern)
{
    // ���� ���� ����
    for (int i = 0; i < vecEnemys.size(); i++)
    {
        delete vecEnemys[i];
    }
    vecEnemys.clear();

    // ���Ͽ� �´� �� ����
    switch (pattern)
    {
    case 0:  // �Ϸķ� ����
        for (int i = 0; i < 10; i++)
        {
            vecEnemys.push_back(new Enemy());
            vecEnemys[i]->Init(10.0f + 60.0f * (i % 5), 80.0f + 90.0f * (i / 5), 0); // �Ϸ� ����
        }
        break;

    case 1:  // ���� ����
        for (int i = 0; i < 10; i++)
        {
            vecEnemys.push_back(new Enemy());
            vecEnemys[i]->Init(rand() % WINSIZE_X, rand() % WINSIZE_Y, 1); // ���� ����
        }
        break;

    case 2:  // ������� ����
        for (int i = 0; i < 10; i++)
        {
            vecEnemys.push_back(new Enemy());
            vecEnemys[i]->Init(50.0f * (i % 5), 100.0f + 50.0f * (i / 5), 2); // ������� ����
        }
        break;
    }
}


