#include "State.h"
#include "Rocket.h"

void IDLEState::Enter(Rocket& player)
{
    //IDLE 애니메이션으로 변경
    player.ChangeAnimation(AnimationType::IDLE);
}

void IDLEState::Update(Rocket& player)
{
    // 애니메이션 업데이트
}

void IDLEState::Exit(Rocket& player)
{
}

void DeadState::Enter(Rocket& player)
{
    //사망 애니메이션으로 변경
    player.ChangeAnimation(AnimationType::Dead);
}

void DeadState::Update(Rocket& player)
{
    //사망 애니메이션 업데이트
    //사망 애니메이션 종료 시 게임 종료시켜야함. player.isDead = true
}

void DeadState::Exit(Rocket& player)
{
    //뭐해야되지
}

void MovingState::Enter(Rocket& player)
{
    //이동 애니메이션으로 변경
    player.ChangeAnimation(AnimationType::Moving);
}

void MovingState::Update(Rocket& player)
{
    // 실제 키입력에 따른 포지션 업데이트
    // 이동 애니메이션 업데이트
    player.Move();
}

void MovingState::Exit(Rocket& player)
{
}

void AttackState::Enter(Rocket& player)
{
    //공격애니메이션으로 변경
    player.ChangeAnimation(AnimationType::Attack);
}

void AttackState::Update(Rocket& player)
{
    //현재 설정된 미사일 발사
    //공격키가 떼졌는지 체크하면서 공격상태 유지
    player.Move(); //이동공격 가능하도록 이동로직 추가
    player.Fire();
}

void AttackState::Exit(Rocket& player)
{
    player.ChangeAnimation(AnimationType::IDLE);
}

void HitState::Enter(Rocket& player)
{
    //피격애니메이션? 있나?
    //무적시간 있어야할듯 플레이어 무적시간 세팅
    player.ChangeAnimation(AnimationType::Hit);
}

void HitState::Update(Rocket& player)
{
    //플레이어 체력 감소
    //무적시간 감소 업데이트
    //무적시간 끝나면 다시 IDLE상태로 복귀
    zonya += TimerManager::GetInstance()->GetDeltaTime();
    if (zonya >= 0.5f)
        player.ChangeState(new IDLEState());
}

void HitState::Exit(Rocket& player)
{
}
