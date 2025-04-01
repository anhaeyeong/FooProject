#pragma once
#include "Singleton.h"
#include "config.h"
#include <vector>
#include "Image.h"

class UIManager : public Singleton<UIManager>
{
private:
    struct ImageUI {
        Image image;
        int x, y;
    };

    vector<ImageUI> imageUI;                //�̹��� UI ���� ����, ü���̳� �Ѿ� ������ ���
    vector<pair<string, FPOINT>> textUI;    //�ؽ�Ʈ UI ���� ����, ������ �������� ǥ�ÿ� 
    HDC hdc;

public:
    UIManager() : hdc(nullptr) {};
    ~UIManager() { Release(); }

    void Init(HDC hdc);  
    void Render();
    void AddImage(const wchar_t* filePath, 
        int x, int y, 
        int width, int height, 
        bool isTransparent = false, COLORREF transColor = RGB(255, 0, 255));
    void AddText(const std::string& text, int x, int y);
    //void Update(); ���Ŀ� �÷��̾� ü�� �����ؼ� ������Ʈ �������.
    void Release();
};

