#include "InputManager.h"


bool InputManager::isMoveLeft(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(/*VK_NUMPAD4*/'A')) {
        return true;
    }

    return false;
}

bool InputManager::isMoveRight(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(/*VK_NUMPAD6*/'D')) {
        return true;
    }
    return false;
}

bool InputManager::isMoveUp(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(/*VK_NUMPAD8*/'W')) {
        return true;
    }
    return false;
}

bool InputManager::isMoveDown(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(/*VK_NUMPAD5*/'S')) {
        return true;
    }
    return false;
}

bool InputManager::isFire(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(VK_SPACE)) {
        return true;
    }
    return false;
}

