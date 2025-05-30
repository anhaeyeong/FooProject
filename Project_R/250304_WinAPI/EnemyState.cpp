#include "EnemyState.h"  
#include "Enemy.h"  
#include "EnemyManager.h"  
#include "MissileFactory.h"

void EnemyIDLEState::Enter(Enemy& enemy)  
{  
   enemy.ChangeAnimation(EnemyAnimType::EIDLE);  
}  

void EnemyIDLEState::Update(Enemy& enemy)  
{
   enemy.UpdateAnimation(5);  
   enemy.Move();  
}  

void EnemyIDLEState::Exit(Enemy& enemy)  
{  
}  

void EnemyDeadState::Enter(Enemy& enemy)  
{  
   enemy.ChangeAnimation(EnemyAnimType::EDead);  
   if (enemy.GetName() == "BossEnemy") {
       EnemyMissileFactory::GetInstance()->DeactivateMissilesByType(MissileType::BOSS);
   }
}  

void EnemyDeadState::Update(Enemy& enemy)  
{  
   enemy.UpdateAnimation(9);   
   
}  

void EnemyDeadState::Exit(Enemy& enemy)  
{  
}
