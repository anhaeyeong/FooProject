#pragma once
#include "Missile.h"
#include "Singleton.h"

class MissileFactory
{
protected:
    vector<Missile*> vecMissiles; 
    MissileOwner ownerType;          

public:
    MissileFactory(MissileOwner owner) : ownerType(owner) {}
    virtual ~MissileFactory();

    void AddMissile(MissileType type, FPOINT pos);
    void Init();
    void Release();
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
};
