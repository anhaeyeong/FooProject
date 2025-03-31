#include "Missile.h"

void NoramlMissile::Move()
{
    std::cout << "�Ϲ� �̻��� �̵�!" << std::endl;
}

void NoramlMissile::Notice()
{
    if (owner == MissileOwner::ROCKET)
        std::cout << "�÷��̾ �Ϲ� �̻��� �߻�!" << std::endl;
    else
        std::cout << "���� �Ϲ� �̻��� �߻�!" << std::endl;
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
    std::cout << "�Ϲ� �̻��� �̵�!" << std::endl;
}

void SignMissile::Notice()
{
    if (owner == MissileOwner::ROCKET)
        std::cout << "�÷��̾ �Ϲ� �̻��� �߻�!" << std::endl;
    else
        std::cout << "���� �Ϲ� �̻��� �߻�!" << std::endl;
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
    std::cout << "�Ϲ� �̻��� �̵�!" << std::endl;
}

void LazerMissile::Notice()
{
    if (owner == MissileOwner::ROCKET)
        std::cout << "�÷��̾ �Ϲ� �̻��� �߻�!" << std::endl;
    else
        std::cout << "���� �Ϲ� �̻��� �߻�!" << std::endl;
}

void LazerMissile::loadImage()
{
    std::string imageKey = (owner == MissileOwner::ROCKET) ? "Player_Normal_Missile" : "Enemy_Normal_Missile";
    image = ImageManager::GetInstance()->AddImage(
        imageKey, TEXT("Image/normal_missile.bmp"), 530, 32, 10, 1,
        true, RGB(255, 0, 255));
}
