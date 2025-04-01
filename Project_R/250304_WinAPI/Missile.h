#pragma once  
#include "config.h"  
#include "Image.h"
#include "GameObject.h"

enum class MissileOwner { PLAYER, ENEMY };  
enum class MissileType { NORMAL, SIGN, LAZER };  

class Missile : public GameObject
{  
protected:  
   MissileOwner owner;  
   MissileType type;  

public:  
   Missile(MissileOwner owner, MissileType type)  
       : image(nullptr), owner(owner), type(type), isActived(false), moveSpeed(3.0f), size(10), angle(90.0f), pos({0, 0}) {  
   }  

   virtual ~Missile() = default;  

   virtual void Init();  
   virtual void Release();
   virtual void Update();
   virtual void Render(HDC hdc);
   virtual void Move() = 0;  
   virtual void Notice() = 0;  
   virtual void loadImage() = 0;  

   bool IsOutofScreen();
   bool isActived;  
   float moveSpeed;  
   int size;  
   FPOINT pos;  
   Image* image;  
   float angle;  

   MissileOwner GetOwner() const { return owner; }  
   MissileType GetType() const { return type; }  
};  

class NormalMissile : public Missile  
{  
private:  
   virtual void Move() override;  
   virtual void Notice() override;  
   virtual void loadImage() override;  

public:  
   NormalMissile(MissileOwner owner) : Missile(owner, MissileType::NORMAL) {}  
   virtual ~NormalMissile() {}  
};  

class SignMissile : public Missile  
{  
private:  
   virtual void Move() override;  
   virtual void Notice() override;  
   virtual void loadImage() override;  

public:  
   SignMissile(MissileOwner owner) : Missile(owner, MissileType::SIGN) {}  
   virtual ~SignMissile() {}  
};  

class LazerMissile : public Missile  
{  
private:  
   virtual void Move() override;  
   virtual void Notice() override;  
   virtual void loadImage() override;  

public:  
   LazerMissile(MissileOwner owner) : Missile(owner, MissileType::LAZER) {}  
   virtual ~LazerMissile() {}  
};
