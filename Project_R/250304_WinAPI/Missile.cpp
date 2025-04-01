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
}

void Missile::Render(HDC hdc) {
    if (image) {
        image->Render(hdc, pos.x, pos.y);
    }
}

bool Missile::IsOutofScreen()
{
    return false;
}



void NormalMissile::Move() {
        pos.y -= moveSpeed * angle * TimerManager::GetInstance()->GetDeltaTime() * 100;
}

void NormalMissile::Notice() {
    if (owner == MissileOwner::PLAYER) {
        pos = { 0, 0 };
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

void SignMissile::Move() {

}

void SignMissile::Notice() {
    if (owner == MissileOwner::PLAYER) {
        pos = { 0, 0 };
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

void LazerMissile::Move() {

}

void LazerMissile::Notice() {
    if (owner == MissileOwner::PLAYER) {
        pos = { 0, 0 };
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
