#pragma once
#include "Missile.h"
#include "Singleton.h"

class MissileFactory
{
protected:
    vector<Missile*> vecMissiles; // 미사일 저장
    MissileOwner ownerType;            // 플레이어 or 적 구분

public:
    MissileFactory(MissileOwner owner) : ownerType(owner) {}
    virtual ~MissileFactory();

    void AddMissile(MissileType type);
    static void Init();
    static void Release();
    void loadImage();
    void Update();
    void Render(HDC hdc);
    virtual Missile* CreateMissile(MissileType type) = 0;
};

class PlayerMissileFactory : public MissileFactory, public Singleton<PlayerMissileFactory>
{
public:
    PlayerMissileFactory() : MissileFactory(MissileOwner::PLAYER) {}
    virtual Missile* CreateMissile(MissileType type) override;
};

class EnemyMissileFactory : public MissileFactory, public Singleton<EnemyMissileFactory>
{
public:
    EnemyMissileFactory() : MissileFactory(MissileOwner::ENEMY) {}
    virtual Missile* CreateMissile(MissileType type) override;
};