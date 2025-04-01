#pragma once
#include "GameObject.h"
#include "ImageManager.h"

class Enemy : public GameObject
{
private:
    FPOINT pos;
    float moveSpeed;
    bool isAlive;
    int size;
    int animationFrame;
    int elapsedFrame;
    int hp;
    RECT rect;

    // 추가된 패턴 변수
    int spawnPattern;  // 패턴 번호 (0: 일렬, 1: 랜덤, 2: 지그재그)

    Image* image;

public:
    void Init(float posX, float posY, int pattern = 0);  // 패턴을 추가한 Init 함수
    void Release();
    void Update();
    void Render(HDC hdc);

    void Move();

    inline void SetIsAlive(bool isAlive) { this->isAlive = isAlive; }
    inline bool GetIsAlive() { return isAlive; }
    RECT GetRect() const { return rect; }
    inline FPOINT GetPos() { return pos; }
    inline int GetSize() { return size; }

    Enemy();
    ~Enemy();
};
