#include "Missile.h"

void NoramlMissile::Move()
{
    std::cout << "일반 미사일 이동!" << std::endl;
}

void NoramlMissile::Notice()
{
    if (owner == MissileOwner::ROCKET)
        std::cout << "플레이어가 일반 미사일 발사!" << std::endl;
    else
        std::cout << "적이 일반 미사일 발사!" << std::endl;
}

void NoramlMissile::loadImage()
{
    std::string imageKey = (owner == MissileOwner::ROCKET) ? "Player_Normal_Missile" : "Enemy_Normal_Missile";
    image = ImageManager::GetInstance()->AddImage(
        imageKey, TEXT("Image/normal_missile.bmp"), 530, 32, 10, 1,
        true, RGB(255, 0, 255));
}

void SignMissile::Move()
{
    std::cout << "일반 미사일 이동!" << std::endl;
}

void SignMissile::Notice()
{
    if (owner == MissileOwner::ROCKET)
        std::cout << "플레이어가 일반 미사일 발사!" << std::endl;
    else
        std::cout << "적이 일반 미사일 발사!" << std::endl;
}

void SignMissile::loadImage()
{
    std::string imageKey = (owner == MissileOwner::ROCKET) ? "Player_Normal_Missile" : "Enemy_Normal_Missile";
    image = ImageManager::GetInstance()->AddImage(
        imageKey, TEXT("Image/normal_missile.bmp"), 530, 32, 10, 1,
        true, RGB(255, 0, 255));
}

void LazerMissile::Move()
{
    std::cout << "일반 미사일 이동!" << std::endl;
}

void LazerMissile::Notice()
{
    if (owner == MissileOwner::ROCKET)
        std::cout << "플레이어가 일반 미사일 발사!" << std::endl;
    else
        std::cout << "적이 일반 미사일 발사!" << std::endl;
}

void LazerMissile::loadImage()
{
    std::string imageKey = (owner == MissileOwner::ROCKET) ? "Player_Normal_Missile" : "Enemy_Normal_Missile";
    image = ImageManager::GetInstance()->AddImage(
        imageKey, TEXT("Image/normal_missile.bmp"), 530, 32, 10, 1,
        true, RGB(255, 0, 255));
}
