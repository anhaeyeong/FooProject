// config.h

#pragma once
#pragma comment(lib,"winmm.lib")

#include <Windows.h>
#include <string>
#include <iostream>
#include <bitset>
#include <map>
#include <vector>
#include <mmsystem.h>


using namespace std;

#include "KeyManager.h"
#include "ImageManager.h"
#include "TimerManager.h"
#include "InputManager.h"


#define WINSIZE_X	720
#define WINSIZE_Y	1080
#define DEG_TO_RAD(degree) ((3.14 / 180.0) * degree)
#define RAD_TO_DEG(radian) ((180.0 / 3.14) * radian)

typedef struct tagFPOINT
{
	float x;
	float y;
} FPOINT;


extern HWND g_hWnd;
extern HINSTANCE g_hInstance;
