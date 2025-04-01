#include "UIManager.h"

void UIManager::Init(HDC hdc)
{
	this->hdc = hdc;
}

void UIManager::Render()
{
    if (hdc == nullptr) return;

    // 이미지 UI 렌더링
    for (auto& element : imageUI) {
        element.image.Render(hdc, element.x, element.y);
    }

    // 텍스트 UI 렌더링
    for (auto& text : textUI) {
        TextOutA(hdc, text.second.x, text.second.y, text.first.c_str(), text.first.length());
    }
}

void UIManager::AddImage(const wchar_t* filePath, int x, int y, int width, int height, bool isTransparent, COLORREF transColor)
{
    ImageUI ui;
    ui.x = x;
    ui.y = y;
    if (FAILED(ui.image.Init(filePath, x, y, width, height, isTransparent, transColor)))
    {
        return;
    }
}

void UIManager::AddText(const string& text, int x, int y)
{
    FPOINT pos = { x, y };
    textUI.push_back(make_pair(text, pos));
}

void UIManager::Release()
{
    imageUI.clear();
    textUI.clear();
}
