#include "State.h"
#include "Rocket.h"

void IDLEState::Enter(Rocket& player)
{
    //IDLE �ִϸ��̼����� ����
}

void IDLEState::Update()
{
    // �ִϸ��̼� ������Ʈ
}

void IDLEState::Exit(Rocket& player)
{
}

void DeadState::Enter(Rocket& player)
{
    //��� �ִϸ��̼����� ����
}

void DeadState::Update()
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
}

void MovingState::Update()
{
    // ���� Ű�Է¿� ���� ������ ������Ʈ
    // �̵� �ִϸ��̼� ������Ʈ
}

void MovingState::Exit(Rocket& player)
{
}

void AttackAkanState::Enter(Rocket& player)
{
    //���ݾִϸ��̼����� ����
}

void AttackAkanState::Update()
{
    //��ĭ �߻�
    //����Ű�� �������� üũ�ϸ鼭 ���ݻ��� ����
}

void AttackAkanState::Exit(Rocket& player)
{
}

void AttackCommandState::Enter(Rocket& player)
{
    //���ݾִϸ��̼����� ����
}

void AttackCommandState::Update()
{
    
}

void AttackCommandState::Exit(Rocket& player)
{
}

void AttackCivilState::Enter(Rocket& player)
{
    //���ݾִϸ��̼����� ����
}

void AttackCivilState::Update()
{
    
}

void AttackCivilState::Exit(Rocket& player)
{
}

void HitState::Enter(Rocket& player)
{
    //�ǰݾִϸ��̼�? �ֳ�?
    //�����ð� �־���ҵ� �÷��̾� �����ð� ����
}

void HitState::Update()
{
    //�����ð� ���� ������Ʈ
    //�����ð� ������ �ٽ� IDLE���·� ����
}

void HitState::Exit(Rocket& player)
{
}
