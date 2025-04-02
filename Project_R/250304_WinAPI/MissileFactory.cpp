#include "MissileFactory.h"
#include "MainGame.h"
#include "ColliderManager.h"
// �̻��� ���丮 �Ҹ���
MissileFactory::~MissileFactory()
{
   for (Missile* missile : vecMissiles)
       delete missile;
   vecMissiles.clear();
}
    
// �̻��� �߰�
void MissileFactory::AddMissile(MissileType type,FPOINT pos)
{
   Missile* missile = CreateMissile(type,pos);
   if (missile)
   {
       vecMissiles.push_back(missile);
       missile->Notice();
       missile->loadImage();
       ColliderManager::GetInstance()->AddMissile(missile);
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

void MissileFactory::loadImage() {
    for (Missile* missile : vecMissiles) {
        if (missile) {
            missile->loadImage();
        }
    }
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

Missile* PlayerMissileFactory::CreateMissile(MissileType type, FPOINT pos)  
{  
  Missile* missile = 0;  
  switch (type)  
  {  
  case MissileType::NORMAL:  
      missile = new NormalMissile(MissileOwner::PLAYER );  
      missile->SetPos(pos);  
      break;  
  case MissileType::SIGN:  
      missile = new SignMissile(MissileOwner::PLAYER);  
      missile->SetPos(pos);
      break;
  case MissileType::LAZER:
      missile = new LazerMissile(MissileOwner::PLAYER);  
      missile->SetPos(pos);
      break;
  default:  
      std::cerr << "Unknown MissileType: " << static_cast<int>(type) << std::endl;  
      break;  
  }  
  if (!missile)  
      std::cerr << "Missile creation failed for type: " << static_cast<int>(type) << std::endl;  
  return missile;  
}


Missile* EnemyMissileFactory::CreateMissile(MissileType type,FPOINT pos)
{
   return new NormalMissile(MissileOwner::ENEMY);
}
