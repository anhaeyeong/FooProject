#pragma once
#include "GameObject.h"
#include <vector>
#include <ctime>  // 시간 관련 헤더
#include "EnemyState.h"

class Enemy;
class EnemyState;
class EnemyManager :  public Singleton<EnemyManager>
{
private:
    std::vector<Enemy*> vecEnemys;
    int spawnInterval;               
    float elapsedTime;               
    int maxEnemies;                 
    int spawnPattern;      
    Enemy* enemy;
    EnemyState* eState;

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);
    void AddEnemy();                 
    void SetSpawnPattern(int pattern);
};
