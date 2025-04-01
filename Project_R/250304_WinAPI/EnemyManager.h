#pragma once
#include "GameObject.h"
#include <vector>
#include <ctime>  // 시간 관련 헤더

class Enemy;
class EnemyManager : public GameObject
{
private:
    std::vector<Enemy*> vecEnemys;  // 적을 동적으로 관리하는 벡터
    int spawnInterval;               // 적이 생성되는 주기
    float elapsedTime;               // 시간 측정용
    int maxEnemies;                  // 최대 생성되는 적 수
    int spawnPattern;                // 현재 적 생성 패턴

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);
    void AddEnemy();                 // 새로운 적을 추가하는 함수
    void SetSpawnPattern(int pattern); // 패턴을 설정하는 함수
};
