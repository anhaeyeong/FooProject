#include "State.h"
#include "Rocket.h"

void IDLEState::Enter(Rocket& player)
{
    //IDLE 애니메이션으로 변경
}

void IDLEState::Update()
{
    // 애니메이션 업데이트
}

void IDLEState::Exit(Rocket& player)
{
}

void DeadState::Enter(Rocket& player)
{
    //사망 애니메이션으로 변경
}

void DeadState::Update()
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
}

void MovingState::Update()
{
    // 실제 키입력에 따른 포지션 업데이트
    // 이동 애니메이션 업데이트
}

void MovingState::Exit(Rocket& player)
{
}

void AttackAkanState::Enter(Rocket& player)
{
    //공격애니메이션으로 변경
}

void AttackAkanState::Update()
{
    //아칸 발사
    //공격키가 떼졌는지 체크하면서 공격상태 유지
}

void AttackAkanState::Exit(Rocket& player)
{
}

void AttackCommandState::Enter(Rocket& player)
{
    //공격애니메이션으로 변경
}

void AttackCommandState::Update()
{
    
}

void AttackCommandState::Exit(Rocket& player)
{
}

void AttackCivilState::Enter(Rocket& player)
{
    //공격애니메이션으로 변경
}

void AttackCivilState::Update()
{
    
}

void AttackCivilState::Exit(Rocket& player)
{
}

void HitState::Enter(Rocket& player)
{
    //피격애니메이션? 있나?
    //무적시간 있어야할듯 플레이어 무적시간 세팅
}

void HitState::Update()
{
    //무적시간 감소 업데이트
    //무적시간 끝나면 다시 IDLE상태로 복귀
}

void HitState::Exit(Rocket& player)
{
}
