#include "UIManager.h"

void UIManager::Init()
{
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
}

void UIManager::AddImage(string key, const wchar_t* filePath, int x, int y, int width, int height, bool isTransparent, COLORREF transColor)
{
    ImageUI ui;
    ui.image = ImageManager::GetInstance()->AddImage(key, filePath, x, y, width, height, isTransparent, transColor);
    ui.x = x;
    ui.y = y;
    if (FAILED(ui.image->Init(filePath, x, y, width, height, isTransparent, transColor)))
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

void UIManager::Clear()
{
    imageUI.clear();
    textUI.clear();
}

void UIManager::Release()
{
    
}
