#ifndef _THE_FIGHTER_HEADER_H_
#define _THE_FIGHTER_HEADER_H_

#include <XEngine.h>
using namespace X;
#include "EnemyBullet.h"
#include "AnimationState.h"


class Fighter
{
public:
	Fighter() {}
	Fighter(Math::Vector2 pos, float speed, int sprite);
	~Fighter() {}

	void Update(float deltaTime);
	void Render();

	const Math::Vector2& GetPosition() const { return mPosition; }
	float GetSpeed() const { return mSpeed; }
	bool isdead() { return Dead; }
	bool OnAir() { return Air; }
	void SetPosition(const Math::Vector2 pos) { mPosition = pos; }
	void SetSpeed(float speed) { mSpeed = speed; }
	Animation GetAnimationState() { return mAnimationState; }

	void SetHealth(int hp) { Health = hp; }
	int GetHealth() { return Health; }
	void TakeDamage(int dmg) 
	{ 
		if (!isNoDmg())
		{
			NoDmg = true;
			Health -= dmg;
		}
	}

	Math::Circle GetBoundingCircle() const { return Math::Circle(mPosition, 10.0f);}
	void Kill();
	bool isNoDmg() { return NoDmg; }
	void OntheSky() 
	{ 
		if (mPosition.y < 180.0f)
		{
			Air = true;
		}
		else 
		{ 
		Air = false;  
		}
	}

private:
	Math::Vector2 mPosition;
	float mSpeed;
	int mSpriteNum;
	Animation mAnimationState;

	bool Air = false;
	bool Dead = false;
	bool NoDmg = false;
	int Health = 2;
	// add animation state variable

	float standDuration; // length of time of the animation
	int standFrameCount; // number of images in the animation
	int standFrame; // the current frame you are rendering
	float standTimer;

	float LeftmoveDuration;
	int LeftmoveFrameCount;
	int LeftmoveFrame;
	float LeftmoveTimer;

	float RightmoveDuration;
	int RightmoveFrameCount;
	int RightmoveFrame;
	float RightmoveTimer;

	float RightAttackDuration;
	int RightAttackFrameCount;
	int RightAttackFrame;
	float RightAttackTimer;

	float LeftAttackDuration;
	int LeftAttackFrameCount;
	int LeftAttackFrame;
	float LeftAttackTimer;

	float RightZDuration;
	int RightZFrameCount;
	int RightZFrame;
	float RightZtimer;

	float LeftZDuration;
	int LeftZFrameCount;
	int LeftZFrame;
	float LeftZtimer;

	float RightDeathDuration;
	int RightDeathFrameCount;
	int RightDeathFrame;
	float RightDeathTimer;

	float LeftDeathDuration;
	int LeftDeathFrameCount;
	int LeftDeathFrame;
	float LeftDeathTimer;

	int HeroStandTexture[2];
	int HeroRightTexture[2];
	int HeroLeftTexture[2];
	int HeroRightAttackTexture[6];
	int HeroLeftAttackTexture[6];
	int HeroRightZTexture[2];
	int HeroLeftZTexture[2];
	int HeroLeftDeathTexture[3];
	int HeroRightDeathTexture[3];

	float HitTimer;
	float HitRate = 2.2f;
};

#endif // !_THE_FIGHTER_HEADER_H_#pragma once
