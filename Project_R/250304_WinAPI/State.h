#pragma once
#include "config.h"

class Rocket;
class State
{
public:
	virtual void Enter(Rocket& player) {};
	virtual void Update() = 0;
	virtual void Exit(Rocket& player) {};

	State() {};
	virtual ~State() {};
};

class AttackState
{
public:
	virtual void Enter(Rocket& player) {};
	virtual void Update() = 0;
	virtual void Exit(Rocket& player) {};

	AttackState() {};
	virtual ~AttackState() {};
};

class IDLEState : public State
{
	void Enter(Rocket& player) override;
	void Update() override;
	void Exit(Rocket& player) override;
};

class DeadState : public State
{
	void Enter(Rocket& player) override;
	void Update() override;
	void Exit(Rocket& player) override;
};

class MovingState : public State
{
	void Enter(Rocket& player) override;
	void Update() override;
	void Exit(Rocket& player) override;
};

class AttackAkanState : public AttackState
{
	void Enter(Rocket& player) override;
	void Update() override;
	void Exit(Rocket& player) override;
};

class AttackCommandState : public AttackState
{
	void Enter(Rocket& player) override;
	void Update() override;
	void Exit(Rocket& player) override;
};

class AttackCivilState : public AttackState
{
	void Enter(Rocket& player) override;
	void Update() override;
	void Exit(Rocket& player) override;
};

class HitState : public State
{
	void Enter(Rocket& player) override;
	void Update() override;
	void Exit(Rocket& player) override;
};

