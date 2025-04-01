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

    vector<ImageUI> imageUI;                //이미지 UI 저장 벡터, 체력이나 총알 아이콘 등록
    vector<pair<string, FPOINT>> textUI;    //텍스트 UI 저장 벡터, 점수나 스테이지 표시용 
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
    //void Update(); 추후에 플레이어 체력 매핑해서 업데이트 해줘야함.
    void Release();
};

