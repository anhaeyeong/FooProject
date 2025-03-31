#pragma once
#include "config.h"

enum class MissileOwner { ROCKET, ENEMY };
enum class MissileType { NORMAL, SIGN, LAZER };


class Missile
{
protected:
    Image* image;
    MissileOwner owner;

public:
    Missile(MissileOwner owner) : image(nullptr), owner(owner) {}
    virtual ~Missile() = default;

    virtual void Move() = 0;
    virtual void Notice() = 0;
    virtual void loadImage() = 0;

    MissileOwner GetOwner() const { return owner; }
};

class NoramlMissile : public Missile
{
private:
    virtual void Move() override;
    virtual void Notice() override;
    virtual void loadImage() override;

public:
    NoramlMissile(MissileOwner owner) : Missile(owner) { loadImage(); }
    virtual ~NoramlMissile() {}
};

class SignMissile : public Missile
{
private:
    virtual void Move() override;
    virtual void Notice() override;
    virtual void loadImage() override;

public:
    SignMissile(MissileOwner owner) : Missile(owner) { loadImage(); }
    virtual ~SignMissile() {}
};

class LazerMissile : public Missile
{
private:
    virtual void Move() override;
    virtual void Notice() override;
    virtual void loadImage() override;

public:
    LazerMissile(MissileOwner owner) : Missile(owner) { loadImage(); }
    virtual ~LazerMissile() {}
};
