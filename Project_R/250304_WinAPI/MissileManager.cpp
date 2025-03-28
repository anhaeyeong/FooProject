#include "MissileManager.h"
#include "Missile.h"
#include "CommonFunction.h"
#include "Rocket.h"

void MissileManager::Init()
{
	//vecMissiles.reserve(30);
	vecMissiles.resize(30);
	for (iterMissiles = vecMissiles.begin();
		iterMissiles != vecMissiles.end();
		iterMissiles++) {
		(*iterMissiles) = new Missile();
		(*iterMissiles)->Init();

	}

	EnemyMissiles.resize(1);

	for (iterEnemyMissiles = EnemyMissiles.begin();
		iterEnemyMissiles != EnemyMissiles.end();
		iterEnemyMissiles++) {
		(*iterEnemyMissiles) = new Missile();
		(*iterEnemyMissiles)->Init();

	}
}

void MissileManager::Release()
{
	for (iterMissiles = vecMissiles.begin();
		iterMissiles != vecMissiles.end();
		iterMissiles++)
	{
		(*iterMissiles)->Release();
	}

	for (iterEnemyMissiles = EnemyMissiles.begin();
		iterEnemyMissiles != EnemyMissiles.end();
		iterEnemyMissiles++)
	{
		(*iterEnemyMissiles)->Release();
	}

}

void MissileManager::Update()
{
	for (iterMissiles = vecMissiles.begin();
		iterMissiles != vecMissiles.end();
		iterMissiles++)
	{
		(*iterMissiles)->Update();
	}
	for (iterEnemyMissiles = EnemyMissiles.begin();
		iterEnemyMissiles != EnemyMissiles.end();
		iterEnemyMissiles++)
	{
		(*iterEnemyMissiles)->Update();
	}

}

void MissileManager::Render(HDC hdc)
{
	for (iterMissiles = vecMissiles.begin();
		iterMissiles != vecMissiles.end();
		iterMissiles++)
	{
		(*iterMissiles)->Render(hdc);
	}

	for (iterEnemyMissiles = EnemyMissiles.begin();
		iterEnemyMissiles != EnemyMissiles.end();
		iterEnemyMissiles++)
	{
		(*iterEnemyMissiles)->Render(hdc);
	}
}

void MissileManager::Fire(FPOINT StartPos, float angle)
{
    for (iterMissiles = vecMissiles.begin();
		iterMissiles != vecMissiles.end();
		iterMissiles++)
    {
        if ((*iterMissiles)->GetIsActived()==false)  // 비활성화된 미사일만 발사
        {
			(*iterMissiles)->SetIsActived(true);
			(*iterMissiles)->SetPos(StartPos); // 플레이어 위치에서 발사
			(*iterMissiles)->SetAngle(angle); // 특정 방향으로 발사
			break;
        }
    }
}

void MissileManager::EnemyFire(FPOINT StartPos, float angle)
{
	for (iterEnemyMissiles = EnemyMissiles.begin();
		iterEnemyMissiles != EnemyMissiles.end();
		iterEnemyMissiles++)
	{
		if ((*iterEnemyMissiles)->GetIsActived() == false)  // 비활성화된 미사일만 발사
		{
			(*iterEnemyMissiles)->SetIsActived(true);
			(*iterEnemyMissiles)->SetPos(StartPos); // 플레이어 위치에서 발사
			(*iterEnemyMissiles)->SetAngle(angle); // 특정 방향으로 발사
			break;
		}
	}
}

