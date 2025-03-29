#include "MissileFactory.h"

// �̻��� ���丮 �Ҹ���
MissileFactory::~MissileFactory()
{
    for (Missile* missile : vecMissiles)
        delete missile;
    vecMissiles.clear();
}

// �̻��� �߰�
void MissileFactory::AddMissile(MissileType type)
{
    Missile* missile = CreateMissile(type);
    vecMissiles.push_back(missile);
    missile->Notice();
}

void MissileFactory::Init()
{
    PlayerMissileFactory::GetInstance();
    EnemyMissileFactory::GetInstance();
}

void MissileFactory::Release()
{
    PlayerMissileFactory::GetInstance()->ReleaseInstance();
    EnemyMissileFactory::GetInstance()->ReleaseInstance();
}

// MissileFactory.cpp
Missile* PlayerMissileFactory::CreateMissile(MissileType type)
{
    switch (type)
    {
    case MissileType::NORMAL:
        return new NoramlMissile(MissileOwner::PLAYER);
    case MissileType::SIGN:
        return new SignMissile(MissileOwner::PLAYER);
    case MissileType::LAZER:
        return new LazerMissile(MissileOwner::PLAYER);
    default:
        return nullptr;
    }
}

Missile* EnemyMissileFactory::CreateMissile(MissileType type)
{
    return new NoramlMissile(MissileOwner::ENEMY);
}
