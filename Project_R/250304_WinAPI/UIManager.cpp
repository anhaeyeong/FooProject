#include "UIManager.h"

void UIManager::Init()
{
    currMissileType = nullptr;
    
}

void UIManager::Render(HDC hdc)
{
    if (hdc == nullptr) return;

    // 이미지 UI 렌더링
    for (auto& element : imageUI) {
        element.image->Render(hdc, element.x, element.y);
    }

    // 텍스트 UI 렌더링
    for (auto& text : textUI) {
        TextOutA(hdc, text.second.x, text.second.y, text.first.c_str(), text.first.length());
    }
    // 미사일타입
    if (currMissileType)
    {
        currMissileType->FrameRender(hdc, WINSIZE_X - 50, 50, 0, 0);
    }
    for (int i = 0; i < hpBar.size(); i++)
    {
        if (hpBar[i])
        {
            hpBar[i]->FrameRender(hdc, 40 + (50 * i), WINSIZE_Y - 60, 0, 0);
        }
    }
}

void UIManager::AddImage(string key, const wchar_t* filePath, int x, int y, int width, int height, bool isTransparent, COLORREF transColor)
{
    ImageUI ui;
    ui.image = ImageManager::GetInstance()->AddImage(key, filePath, width, height, isTransparent, transColor);
    ui.x = x;
    ui.y = y;
    if (FAILED(ui.image->Init(filePath, width, height, isTransparent, transColor)))
    {
        return;
    }
    imageUI.push_back(ui);
}

void UIManager::AddText(const string& text, int x, int y)
{
    FPOINT pos = { x, y };
    textUI.push_back(make_pair(text, pos));
}

void UIManager::InitMainSceneUI()
{
    hpBar.resize(3);
    for (int i = 0; i < hpBar.size(); i++)
        hpBar[i] = nullptr;
    ImageManager::GetInstance()->AddImage("mineralType", TEXT("Image/mineral.bmp"), 14 * 3, 13 * 3, 1, 1,
        true, RGB(89, 164, 81));
    ImageManager::GetInstance()->AddImage(
        "GasType", TEXT("Image/gas.bmp"), 11 * 3, 14 * 3, 1, 1,
        true, RGB(89, 164, 81));
    ImageManager::GetInstance()->AddImage("normalType", TEXT("Image/bullet.bmp"), 21 * 2, 21 * 2, 1, 1,
        true, RGB(255, 0, 255));
    currMissileType = ImageManager::GetInstance()->FindImage("normalType");
    ImageManager::GetInstance()->AddImage("hp1", TEXT("Image/SCV_IDLE.bmp"), 35, 30, 1, 1, true, RGB(48, 64, 47));
    ImageManager::GetInstance()->AddImage("hp2", TEXT("Image/SCV_IDLE.bmp"), 35, 30, 1, 1, true, RGB(48, 64, 47));
    ImageManager::GetInstance()->AddImage("hp3", TEXT("Image/SCV_IDLE.bmp"), 35, 30, 1, 1, true, RGB(48, 64, 47));
    
    hpBar[0] = ImageManager::GetInstance()->FindImage("hp1");
    hpBar[1] = ImageManager::GetInstance()->FindImage("hp2");
    hpBar[2] = ImageManager::GetInstance()->FindImage("hp3");
}

void UIManager::ChangeMissileType(int mType)
{
    switch (mType)
    {
    case 0:
        currMissileType = ImageManager::GetInstance()->FindImage("normalType");
        break;
    case 1:
        currMissileType = ImageManager::GetInstance()->FindImage("mineralType");
        break;
    case 2:
        currMissileType = ImageManager::GetInstance()->FindImage("GasType");
        break;
    }
}

void UIManager::Hit(int hp)
{
    if (hp < 0) return;
    hpBar[hp] = nullptr;
}

void UIManager::Clear()
{
    imageUI.clear();
    textUI.clear();
    currMissileType = nullptr;
    for (int i = 0; i < hpBar.size(); i++)
    {
        hpBar[i] = nullptr;
    }
    hpBar.clear();
}

void UIManager::Release()
{
    
}
