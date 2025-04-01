#include "State.h"
#include "Rocket.h"

void IDLEState::Enter(Rocket& player)
{
    //IDLE �ִϸ��̼����� ����
    player.ChangeAnimation(AnimationType::IDLE);
}

void IDLEState::Update(Rocket& player)
{
    // �ִϸ��̼� ������Ʈ
}

void IDLEState::Exit(Rocket& player)
{
}

void DeadState::Enter(Rocket& player)
{
    //��� �ִϸ��̼����� ����
    player.ChangeAnimation(AnimationType::Dead);
}

void DeadState::Update(Rocket& player)
{
    //��� �ִϸ��̼� ������Ʈ
    //��� �ִϸ��̼� ���� �� ���� ������Ѿ���. player.isDead = true
}

void DeadState::Exit(Rocket& player)
{
    //���ؾߵ���
}

void MovingState::Enter(Rocket& player)
{
    //�̵� �ִϸ��̼����� ����
    player.ChangeAnimation(AnimationType::Moving);
}

void MovingState::Update(Rocket& player)
{
    // ���� Ű�Է¿� ���� ������ ������Ʈ
    // �̵� �ִϸ��̼� ������Ʈ
    player.Move();
}

void MovingState::Exit(Rocket& player)
{
}

void AttackState::Enter(Rocket& player)
{
    //���ݾִϸ��̼����� ����
    player.ChangeAnimation(AnimationType::Attack);
}

void AttackState::Update(Rocket& player)
{
    //���� ������ �̻��� �߻�
    //����Ű�� �������� üũ�ϸ鼭 ���ݻ��� ����
    player.Move(); //�̵����� �����ϵ��� �̵����� �߰�
    player.Fire();
}

void AttackState::Exit(Rocket& player)
{
    player.ChangeAnimation(AnimationType::IDLE);
}

void HitState::Enter(Rocket& player)
{
    //�ǰݾִϸ��̼�? �ֳ�?
    //�����ð� �־���ҵ� �÷��̾� �����ð� ����
    player.ChangeAnimation(AnimationType::Hit);
}

void HitState::Update(Rocket& player)
{
    //�÷��̾� ü�� ����
    //�����ð� ���� ������Ʈ
    //�����ð� ������ �ٽ� IDLE���·� ����
    zonya += TimerManager::GetInstance()->GetDeltaTime();
    if (zonya >= 0.5f)
        player.ChangeState(new IDLEState());
}

void HitState::Exit(Rocket& player)
{
}
