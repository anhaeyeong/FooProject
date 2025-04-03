#pragma once
#include "GameObject.h"

class Image;
class KOF_Iori;
class EnemyManager;
class Rocket;
class ItemManager;

enum SceneState
{
	Lobby,
	Start,
	Main,
	End
};

class MainGame : public GameObject
{
private:
	HDC hdc;
	PAINTSTRUCT ps;
	int mousePosX = 0, mousePosY = 0;
	FPOINT mousePos;
	wchar_t szText[128];
	SceneState sceneState;
	float elapsedTime;
	int lobbyFrame;
	int mainFrame;

	Image* backBuffer;
	Image* Lobby;
	Image* startMenu;
	Image* backGround;
	EnemyManager* enemyManager;
	Rocket* rocket;
	ItemManager* itemManager;

public:
	void Init();	// override (�θ�Ŭ������ ���� �Լ��̸�, ������ �ٸ��� �����ϰ� ���� ��)
	// <-> overload (���� �Լ� �̸�, �Ű����� Ÿ�԰� ������ �ٸ��� �ٸ� �Լ��� ó��)
	void Release();
	void Update();
	void Render();

	LRESULT MainProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam);

	MainGame();
	~MainGame();
};

