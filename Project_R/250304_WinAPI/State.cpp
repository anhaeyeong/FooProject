#include "State.h"
#include "Rocket.h"

void IDLEState::Enter(Rocket& player)
{
    //IDLE animation
    player.ChangeAnimation(AnimationType::IDLE);
}

void IDLEState::Update(Rocket& player)
{
    player.UpdateAnimation(1);
}

void IDLEState::Exit(Rocket& player)
{
}

void DeadState::Enter(Rocket& player)
{
    //Dead Animation
    player.ChangeAnimation(AnimationType::Dead);
}

void DeadState::Update(Rocket& player)
{
    //player.isDead = true
    player.UpdateAnimation(4);
}

void DeadState::Exit(Rocket& player)
{
}

void MovingState::Enter(Rocket& player)
{
    //Move Animation
    player.ChangeAnimation(AnimationType::Moving);
}

void MovingState::Update(Rocket& player)
{
    //Move Logic
    player.Move();
    player.UpdateAnimation(1);
}

void MovingState::Exit(Rocket& player)
{
}

void AttackState::Enter(Rocket& player)
{
    //Attack Animation
    player.ChangeAnimation(AnimationType::Attack);
}

void AttackState::Update(Rocket& player)
{
    //Move Attack
    player.Move(); //Attack while moving
    player.Fire();
    player.UpdateAnimation(1);
}

void AttackState::Exit(Rocket& player)
{
    player.ChangeAnimation(AnimationType::IDLE);
}

void HitState::Enter(Rocket& player)
{
    //Hit Animation
    player.ChangeAnimation(AnimationType::Hit);
    player.Hit();
    if (player.GetHP() <= 0)
        player.ChangeState(new DeadState());
}

void HitState::Update(Rocket& player)
{
    player.Move();
    player.UpdateAnimation(1);
    zonya += TimerManager::GetInstance()->GetDeltaTime();
    if (zonya >= 0.5f)
    {
        player.ChangeState(new IDLEState());
    }
}

void HitState::Exit(Rocket& player)
{
}
