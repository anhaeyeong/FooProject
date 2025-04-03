#pragma once
#include "config.h"

class Enemy;
class EnemyState
{
protected:
	string StateName;
public:
	virtual void Enter(Enemy& enemy) {};
	virtual void Update(Enemy& enemy) = 0;
	virtual void Exit(Enemy& enemy) {};

	inline string GetName() { return StateName; }

	EnemyState() {};
	virtual ~EnemyState() {};
};

class EnemyIDLEState : public EnemyState
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy) override;
	void Exit(Enemy& enemy) override;

	EnemyIDLEState() {
		StateName = "IDLE";
	};
	virtual ~EnemyIDLEState() {};
};

class EnemyDeadState : public EnemyState
{
public:
	void Enter(Enemy& enemy) override;
	void Update(Enemy& enemy) override;
	void Exit(Enemy& enemy) override;

	EnemyDeadState() {
		StateName = "Dead";
	};
	virtual ~EnemyDeadState() {};
};