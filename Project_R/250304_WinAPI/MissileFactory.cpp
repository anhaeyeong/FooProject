#include "MissileFactory.h"
#include "MainGame.h"

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
   if (missile)
   {
       vecMissiles.push_back(missile);
       missile->Notice();
       
   }
   else
   {
       std::cerr << "Failed to add missile: " << static_cast<int>(type) << std::endl;
   }
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

void MissileFactory::Update() {
    for (Missile* missile : vecMissiles) {
        if (missile) {
            missile->Update();
        }
    }
}

void MissileFactory::Render(HDC hdc) {
    for (Missile* missile : vecMissiles) {
        if (missile) {
            missile->Render(hdc);
        }
    }
}

// MissileFactory.cpp
Missile* PlayerMissileFactory::CreateMissile(MissileType type)
{
   Missile* missile = 0;
   switch (type)
   {
   case MissileType::NORMAL:
       missile = new NormalMissile(MissileOwner::PLAYER);
       break;
   case MissileType::SIGN:
       missile = new SignMissile(MissileOwner::PLAYER);
       break;
   case MissileType::LAZER:
       missile = new LazerMissile(MissileOwner::PLAYER);
       break;
   default:
       std::cerr << "Unknown MissileType: " << static_cast<int>(type) << std::endl;
       break;
   }
   if (!missile)
       std::cerr << "Missile creation failed for type: " << static_cast<int>(type) << std::endl;
   return missile;
}


Missile* EnemyMissileFactory::CreateMissile(MissileType type)
{
   return new NormalMissile(MissileOwner::ENEMY);
}
