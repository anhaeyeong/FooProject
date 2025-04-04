#pragma once
#include "config.h"

class Rocket;
class State
{
protected:
	string StateName;
public:
	virtual void Enter(Rocket& player) {};
	virtual void Update(Rocket& player) = 0;
	virtual void Exit(Rocket& player) {};

	inline string GetName() { return StateName; }
	State() {};
	virtual ~State() {};
};

class IDLEState : public State
{
public:
	void Enter(Rocket& player) override;
	void Update(Rocket& player) override;
	void Exit(Rocket& player) override;

	IDLEState() {
		StateName = "IDLE";
	};
	virtual ~IDLEState() {};
};

class DeadState : public State
{
public:
	void Enter(Rocket& player) override;
	void Update(Rocket& player) override;
	void Exit(Rocket& player) override;
	DeadState() {
		StateName = "Dead";
	};
	virtual ~DeadState() {};
};

class MovingState : public State
{
public:
	void Enter(Rocket& player) override;
	void Update(Rocket& player) override;
	void Exit(Rocket& player) override;
	MovingState() {
		StateName = "Moving";
	};
	virtual ~MovingState() {};
};

class AttackState : public State
{
private:
	float cooltime;
public:
	void Enter(Rocket& player) override;
	void Update(Rocket& player) override;
	void Exit(Rocket& player) override;
	AttackState() {
		cooltime = 0.0f;
		StateName = "Attack";
	};
	virtual ~AttackState() {};
};

class HitState : public State
{
private:
	float zonya{0.0f};
public:
	void Enter(Rocket& player) override;
	void Update(Rocket& player) override;
	void Exit(Rocket& player) override;
	HitState() {
		StateName = "Hit";
	};
	virtual ~HitState() {};
};

