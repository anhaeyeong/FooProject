#include "EnemyState.h"
#include "Enemy.h"

void EnemyIDLEState::Enter(Enemy& player)
{
	player.ChangeAnimation(EnemyAnimType::EIDLE);
}

void EnemyIDLEState::Update(Enemy& player)
{
	player.UpdateAnimation(5);
	player.Move();
}

void EnemyIDLEState::Exit(Enemy& player)
{
}

void EnemyDeadState::Enter(Enemy& player)
{
	player.ChangeAnimation(EnemyAnimType::EDead);
}

void EnemyDeadState::Update(Enemy& player)
{
	player.UpdateAnimation(3);
}

void EnemyDeadState::Exit(Enemy& player)
{
}
