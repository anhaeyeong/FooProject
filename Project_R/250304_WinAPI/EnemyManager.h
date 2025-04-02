#pragma once
#include "GameObject.h"
#include <vector>
#include <ctime>  // �ð� ���� ���

class Enemy;
class EnemyManager :  public Singleton<EnemyManager>
{
private:
    std::vector<Enemy*> vecEnemys;
    int spawnInterval;               
    float elapsedTime;               
    int maxEnemies;                 
    int spawnPattern;                

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);
    void AddEnemy();                 
    void SetSpawnPattern(int pattern);
};
