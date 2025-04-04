#pragma once
#include "GameObject.h"
#include <vector>
#include <ctime>  // 시간 관련 헤더
#include "EnemyState.h"

class MissileFactory;
class Enemy;
class EnemyState;
class EnemyManager :  public Singleton<EnemyManager>
{
private:
    std::vector<Enemy*> vecEnemys;
    int spawnInterval;               
    float elapsedTime;
    float winDelay;
    int maxEnemies;                 
    int spawnPattern;      
    int count;
    int loopCounter;
    bool isWin;
    Enemy* enemy;
    EnemyState* eState;
    MissileFactory* missileFactory;

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);
    void AddEnemy();                 
    void SetSpawnPattern(int pattern);
	inline bool GetIsWin() { return isWin; }
};
