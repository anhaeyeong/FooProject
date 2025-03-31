#pragma once
#include "Singleton.h"
#include <vector>

class ColliderManager : public Singleton<typename ColliderManager>
{
private:
	std::vector<Collider*> colliders;

public:
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};