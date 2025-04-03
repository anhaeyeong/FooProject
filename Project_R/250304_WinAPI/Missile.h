#pragma once  
#include "config.h"  
#include "Image.h"
#include "GameObject.h"

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

   void Init();  
   void Release();
   void Update();
   virtual void Render(HDC hdc) = 0;
   virtual void Move() = 0;  
   virtual void Notice() = 0;  
   virtual void loadImage() = 0;  

   bool IsOutofScreen();
   bool isActived;  
   float moveSpeed;  
   int size;
   float angle;
   FPOINT pos;  
   Image* image;
   RECT rect;

   virtual void UpdateCollisionRect();
   inline bool GetIsOutOfScreen() { return IsOutofScreen(); }
   inline FPOINT GetPos() { return pos; }
   inline int GetSize() { return size; }
   MissileOwner GetOwner() const { return owner; }  
   MissileType GetType() const { return type; }
   inline void SetPos(FPOINT pos) { this->pos = pos; }
   inline void SetAngle(float angle) { this->angle = angle; }
   inline RECT GetRectAtCenter(int x, int y, int width, int height)
   {
	   RECT rc{ x - (width / 2), y - (height / 2),
		   x + (width / 2), y + (height / 2) };
	   return rc;
   }
   RECT GetRect() { return rect; }
};  

class NormalMissile : public Missile  
{  
private:  
   virtual void Render(HDC hdc);
   virtual void Move() override;
   virtual void Notice() override;  
   virtual void loadImage() override;  

public:  
    NormalMissile(MissileOwner owner) : Missile(owner, MissileType::NORMAL) {}
   virtual ~NormalMissile() {}  
};  

class SignMissile : public Missile  
{  
public:

private:
   virtual void Render(HDC hdc);
   virtual void Move() override;  
   virtual void Notice() override;  
   virtual void loadImage() override;  
   void SignUpdate();

   int initialPosX;
   int currFrame;          // 현재 프레임
   float animElapsedTime;  // 애니메이션 타이머

public:  
   SignMissile(MissileOwner owner) : Missile(owner, MissileType::SIGN) ,currFrame(0),animElapsedTime(0.0f) {}
   virtual ~SignMissile() {}  
};  

class LazerMissile : public Missile  
{  
private:
   virtual void Render(HDC hdc);
   virtual void Move() override;  
   virtual void Notice() override;  
   virtual void loadImage() override;  
   void UpdateCollisionRect() override;

   int animationFrame;
   float elapsedTime;
   float remainTime;

   void UpdateAnim();

public:  
   LazerMissile(MissileOwner owner) : Missile(owner, MissileType::LAZER), animationFrame(0), elapsedTime(0.0f), remainTime(0.5f) {}  
   virtual ~LazerMissile() {}  
};
