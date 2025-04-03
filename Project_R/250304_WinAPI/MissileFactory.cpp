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
void MissileFactory::AddMissile(MissileType type,FPOINT pos, float angle)
{
   // 활성화된 미사일 + 풀의 미사일 수가 최대치에 도달했는지 확인
   if (vecMissiles.size() >= MAX_MISSILES)
   {
       // 풀 업데이트를 통해 비활성화된 미사일 회수
       UpdateMissilePool();

       // 여전히 공간이 없는 경우
       if (vecMissiles.size() >= MAX_MISSILES)
       {
           std::cerr << "Max missile count reached. Cannot add more missiles." << std::endl;
           return;
       }
   }

   // 풀에서 미사일 가져오기
   Missile* missile = GetMissileFromPool(type, pos);

   if (missile)
   {
       vecMissiles.push_back(missile);
       missile->Notice();

       if (type == MissileType::SIGN)
       {
           missile->SetAngle(0.0f);
       }

       missile->loadImage();
       ColliderManager::GetInstance()->AddMissile(missile);
   }
}



void MissileFactory::Init()  
{  
    vecMissiles.clear();
    missilePool.clear();

    // 초기 풀 생성 (사전에 일부 미사일 생성)
    // 각 타입별로 미사일 미리 생성
    for (int i = 0; i < 5; i++) {
        // NORMAL 타입 미사일
        Missile* normalMissile = CreateMissile(MissileType::NORMAL, { 0, 0 });
        if (normalMissile) {
            normalMissile->isActived = false;
            missilePool.push_back(normalMissile);
        }

        // SIGN 타입 미사일
        Missile* signMissile = CreateMissile(MissileType::SIGN, { 0, 0 });
        if (signMissile) {
            signMissile->isActived = false;
            // 여기서 미리 이미지 로드를 시도해볼 수 있음
            signMissile->loadImage();
            missilePool.push_back(signMissile);
        }

        // LAZER 타입 미사일 
        Missile* lazerMissile = CreateMissile(MissileType::LAZER, { 0, 0 });
        if (lazerMissile) {
            lazerMissile->isActived = false;
            missilePool.push_back(lazerMissile);
        }
    }

    PlayerMissileFactory::GetInstance();
    EnemyMissileFactory::GetInstance();  
}

void MissileFactory::Release()
{
   PlayerMissileFactory::GetInstance()->ReleaseInstance();
   EnemyMissileFactory::GetInstance()->ReleaseInstance();
}

Missile* MissileFactory::GetMissileFromPool(MissileType type, FPOINT pos)
{
    // 풀에서 적합한 미사일 찾기
    for (size_t i = 0; i < missilePool.size(); i++)
    {
        if (missilePool[i] && missilePool[i]->GetType() == type)
        {
            Missile* missile = missilePool[i];
            missilePool.erase(missilePool.begin() + i);
            missile->SetPos(pos);
            missile->isActived = true;
            return missile;
        }
    }

    // 적합한 미사일이 없으면 새로 생성
    if (vecMissiles.size() + missilePool.size() < MAX_MISSILES)
    {
        return CreateMissile(type, pos);
    }
    // 한계에 도달하면 null 반환
    return nullptr;
}

void MissileFactory::ReturnMissileToPool(Missile* missile)
{
    if (missile)
    {
        missile->isActived = false;
        missilePool.push_back(missile);
    }
}

void MissileFactory::UpdateMissilePool()
{
 // 화면 밖으로 나간 미사일이나 비활성화된 미사일을 풀로 반환
    for (auto it = vecMissiles.begin(); it != vecMissiles.end();)
    {
        if (*it && ((*it)->GetIsOutOfScreen() || !(*it)->isActived))
        {
            ReturnMissileToPool(*it);
            it = vecMissiles.erase(it);
        }
        else
        {
            ++it;
        }
    }
}

void MissileFactory::loadImage() 
{
    for (Missile* missile : vecMissiles) 
    {
        if (missile) 
        {
            missile->loadImage();
        }
    }
}

void MissileFactory::Update()
{
    // 화면 밖으로 나간 미사일 회수
    UpdateMissilePool();

    // 활성화된 미사일만 업데이트
    for (auto& missile : vecMissiles)
    {
        if (missile && missile->isActived)
        {
            missile->Update();
        }
    }
}

void MissileFactory::Render(HDC hdc) 
{
    for (Missile* missile : vecMissiles) 
    {
        if (missile) 
        {
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
