#pragma once
#include "Missile.h"
#include "Singleton.h"

class MissileFactory
{
protected:
    vector<Missile*> vecMissiles; 
    vector<Missile*> missilePool;  // 비활성화된 미사일 풀
    MissileOwner ownerType;          
    const size_t MAX_MISSILES = 50;
public:
    MissileFactory(MissileOwner owner) : ownerType(owner) {}
    virtual ~MissileFactory();

    void AddMissile(MissileType type, FPOINT pos, float angle = 90.0f);
    void Init();
    void Release();
    Missile* GetMissileFromPool(MissileType type, FPOINT pos);
    void ReturnMissileToPool(Missile* missile);
    void UpdateMissilePool(); // 화면 밖으로 나간 미사일을 풀로 반환
    void loadImage();
    void Update();
    void Render(HDC hdc);
    virtual Missile* CreateMissile(MissileType type,FPOINT pos) = 0;
};

class PlayerMissileFactory : public MissileFactory, public Singleton<PlayerMissileFactory>
{
public:
    PlayerMissileFactory() : MissileFactory(MissileOwner::PLAYER) {}
    virtual Missile* CreateMissile(MissileType type,FPOINT pos) override;
};

class EnemyMissileFactory : public MissileFactory, public Singleton<EnemyMissileFactory>
{
public:
    EnemyMissileFactory() : MissileFactory(MissileOwner::ENEMY) {}
    virtual Missile* CreateMissile(MissileType type,FPOINT pos) override;
	void ClearVector()
	{
		for (auto& missile : vecMissiles)
		{
			delete missile;
		}
		vecMissiles.clear();
	}
};
