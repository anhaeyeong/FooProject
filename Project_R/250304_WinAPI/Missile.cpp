#include "Missile.h"

void Missile::Init() {
    pos = { 0, 0 };
    isActived = false;
    moveSpeed = 3.0f;
    size = 10;
    angle = 90.0f;
}

void Missile::Release()
{
    if (image)
    {
        image->Release();
        delete image;
        image = nullptr;
    }
}

void Missile::Update() {
    Move();
    if (isActived && IsOutofScreen()) {
        isActived = false;
    }
    UpdateCollisionRect();
}

void Missile::Render(HDC hdc) {
    if (image) {
        image->Render(hdc, pos.x, pos.y);
    }
    else {
        std::cerr << "." << std::endl;
    }
}

bool Missile::IsOutofScreen()
{
    float right = pos.x + size / 2;
    float left = pos.x - size / 2;
    float top = pos.y - size / 2;
    float bottom = pos.y + size / 2;

    if (right < 0 || left > WINSIZE_X
        || bottom < 0 || top > WINSIZE_Y)
        return true;

    return false;
}

void Missile::UpdateCollisionRect()
{
    rect = GetRectAtCenter(pos.x, pos.y, size, size);
}

void NormalMissile::Render(HDC hdc) {
    if (image) {
        image->Render(hdc, pos.x, pos.y);
    }
    else {
        std::cerr << "이미지가 로드되지 않았습니다." << std::endl;
    }
}


void NormalMissile::Move() {
        pos.y -= moveSpeed * angle * TimerManager::GetInstance()->GetDeltaTime() * 100;
}

void NormalMissile::Notice() {
    if (owner == MissileOwner::PLAYER) {
        isActived = true;
        moveSpeed = 3.0f;
        size = 10;
        angle = 90.0f;
    }

}

void NormalMissile::loadImage() {  
   string imageKey = (owner == MissileOwner::PLAYER) ? "player_normal" : "enemy_normal";  
   wstring imagePath = (owner == MissileOwner::PLAYER) ? L"Image/bullet.bmp" : L"Image/.bmp";
   image = ImageManager::GetInstance()->AddImage(  
       imageKey, imagePath.c_str(), 21, 21, 1, 1,  
       true, RGB(255, 0, 255));  

   if (!image) {
       std::cerr << "Failed to load image: " << std::string(imagePath.begin(), imagePath.end()) << std::endl;
   }
}  

void SignMissile::Render(HDC hdc) {
    if (image) {
        image->Render(hdc, pos.x, pos.y);
    }
    else {
        std::cerr << "이미지가 로드되지 않았습니다." << std::endl;
    }
}

void SignMissile::Move() {

}

void SignMissile::Notice() {
    if (owner == MissileOwner::PLAYER) {
        isActived = true;
        moveSpeed = 3.0f;
        size = 10;
    }
}

void SignMissile::loadImage() {  
   string imageKey = (owner == MissileOwner::PLAYER) ? "Player_ _Missile" : "Enemy_ _Missile";  
   wstring imagePath = (owner == MissileOwner::PLAYER) ? L"Image/.bmp" : L"Image/.bmp";  
   image = ImageManager::GetInstance()->AddImage(  
       imageKey, imagePath.c_str(), 21, 21, 1, 1,  
       true, RGB(255, 0, 255));  
}

void LazerMissile::Render(HDC hdc) {
    if (image) {
        image->Render(hdc, pos.x, pos.y);
    }
    else {
        std::cerr << "이미지가 로드되지 않았습니다." << std::endl;
    }
}

void LazerMissile::Move() {

}

void LazerMissile::Notice() {
    if (owner == MissileOwner::PLAYER) {
        isActived = true;
        moveSpeed = 3.5f;
        size = 12;
    }
}

void LazerMissile::loadImage() {
    std::string imageKey = (owner == MissileOwner::PLAYER) ? "" : "";
    std::wstring imagePath = (owner == MissileOwner::PLAYER) ? L"Image/.bmp" : L"Image/.bmp";
    image = ImageManager::GetInstance()->AddImage(
        imageKey, imagePath.c_str(), 21, 21, 1, 1,
        true, RGB(255, 0, 255));
}
