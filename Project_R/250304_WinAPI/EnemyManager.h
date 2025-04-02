#pragma once
#include "GameObject.h"
#include <vector>
#include <ctime>  // �ð� ���� ���

class Enemy;
class EnemyManager : public GameObject
{
private:
    std::vector<Enemy*> vecEnemys;  // ���� �������� �����ϴ� ����
    int spawnInterval;               // ���� �����Ǵ� �ֱ�
    float elapsedTime;               // �ð� ������
    int maxEnemies;                  // �ִ� �����Ǵ� �� ��
    int spawnPattern;                // ���� �� ���� ����

public:
    void Init();
    void Release();
    void Update();
    void Render(HDC hdc);
    void AddEnemy();                 // ���ο� ���� �߰��ϴ� �Լ�
    void SetSpawnPattern(int pattern); // ������ �����ϴ� �Լ�
};
