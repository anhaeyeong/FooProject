#include "InputManager.h"


bool InputManager::isMoveLeft(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_NUMPAD4)) {
        return true;
    }

    return false;
}

bool InputManager::isMoveRight(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_NUMPAD6)) {
        return true;
    }
    return false;
}

bool InputManager::isMoveUp(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_NUMPAD8)) {
        return true;
    }
    return false;
}

bool InputManager::isMoveDown(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_NUMPAD5)) {
        return true;
    }
    return false;
}

bool InputManager::isFire(void)
{
    if (KeyManager::GetInstance()->IsOnceKeyDown(VK_SPACE)) {
        return true;
    }
    return false;
}

