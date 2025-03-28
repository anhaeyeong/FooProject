#pragma once
#include "Singleton.h"
#include "Collider.h"

class ColliderManager: public Singleton<typename ColliderManager>
{
	void Init();
	void Release();
	void Update();
	void Render(HDC hdc);
};

