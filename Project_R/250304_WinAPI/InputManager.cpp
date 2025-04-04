#include "InputManager.h"


bool InputManager::isMoveLeft(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(0x41)) {
        return true;
    }

    return false;
}

bool InputManager::isMoveRight(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(0x44)) {
        return true;
    }
    return false;
}

bool InputManager::isMoveUp(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(0x57)) {
        return true;
    }
    return false;
}

bool InputManager::isMoveDown(void)
{
    if (KeyManager::GetInstance()->IsStayKeyDown(0x53)) {
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

