#include "Boss.h"
#include "AnimationState.h"

BOSS::BOSS(Math::Vector2 pos, float speed, int sprite):
	mPosition{ pos },
	mSpeed{speed},
	mSpriteNum{sprite},
	mAnimationState{ Animation::RightStand },
	standTimer{standDuration},
	LeftmoveTimer{LeftmoveDuration},
	RightmoveTimer{RightmoveDuration},
	DeadTimer{DeadDuration}
	{
	EnemyStandTexture[0] = X::LoadTexture("StandRight.png");
	EnemyStandTexture[1] = X::LoadTexture("StandLeft.png");

	EnemyLeftTexture[0] = X::LoadTexture("LeftMove1.png");
	EnemyLeftTexture[1] = X::LoadTexture("LeftMove2.png");

	EnemyRightTexture[0] = X::LoadTexture("RightMove1.png");
	EnemyRightTexture[1] = X::LoadTexture("RightMove2.png");

	EnemyDeadTexture[0] = X::LoadTexture("Death1.png");
	EnemyDeadTexture[1] = X::LoadTexture("Death2.png");
	EnemyDeadTexture[2] = X::LoadTexture("Death3.png");
	EnemyDeadTexture[3] = X::LoadTexture("Death4.png");
	EnemyDeadTexture[4] = X::LoadTexture("Death5.png");
	EnemyDeadTexture[5] = X::LoadTexture("Death6.png");
	EnemyDeadTexture[6] = X::LoadTexture("Death7.png");
	}


void BOSS::Update(float deltaTime, X::Math::Vector2 targetPos, Fighter *p)
{
	Collision(p);
	// What should the enemy do?
	// Move the enemy to the player.
	// You to tell him where the player is.
	// then move him towards the player.

	// is the target on my right?
	if (!Dead)
	{
		if (mPosition.x <= targetPos.x)
		{
			mAnimationState = Animation::Right;
			mPosition.x += mSpeed * deltaTime;
		}
		if (mPosition.x >= targetPos.x)
		{
			mAnimationState = Animation::Left;
			mPosition.x -= mSpeed * deltaTime;
		}

	}

	if (!Dead)
	{
		if (Health < 0)
		{
			mAnimationState = Animation::Death;
		}
	}

	// switch on animation state
	switch (mAnimationState)
	{
	case Animation::Left:
		LeftmoveFrameCount = 2;
		LeftmoveDuration = 1.0f;
		LeftmoveTimer -= deltaTime;
		if (LeftmoveTimer <= 0.0f)
		{
			LeftmoveTimer = LeftmoveDuration;
			LeftmoveFrame = (LeftmoveFrame + 1) % LeftmoveFrameCount;
		}
		break;
	case Animation::Right:
		RightmoveFrameCount = 2;
		RightmoveDuration = 1.0f;
		RightmoveTimer -= deltaTime;
		if (RightmoveTimer <= 0.0f)
		{
			RightmoveTimer = RightmoveDuration;
			RightmoveFrame = (RightmoveFrame + 1) % RightmoveFrameCount;
		}
		break;
	case Animation::Death:
		DeadFrameCount = 7;
		DeadDuration = 0.25f;
		DeadTimer -= deltaTime;
		if (DeadTimer <= 0.0f)
		{
			DeadTimer = DeadDuration;
			DeadFrame = (DeadFrame + 1) % DeadFrameCount;
		}
	}

	// update the image index in the array to render.
}

void BOSS::Render()
{
	switch (mAnimationState)
	{
	case Animation::LeftStand:
		X::DrawSprite(EnemyStandTexture[1], mPosition);
		break;
	case Animation::RightStand:
		X::DrawSprite(EnemyStandTexture[0], mPosition);
		break;
	case Animation::Left:
		X::DrawSprite(EnemyLeftTexture[LeftmoveFrame], mPosition);
		break;
	case Animation::Right:
		X::DrawSprite(EnemyRightTexture[RightmoveFrame], mPosition);
		break;
	case Animation::Death:
		X::DrawSprite(EnemyDeadTexture[DeadFrame], mPosition);
		break;
	}
}

void BOSS::Kill()
{
	Dead = true;
	X::PlayAudio(mDeathSprite, false, 0.2f, 0.2f, 0.2f);
}

void BOSS::Collision(Fighter *p)
{
	if (Math::Intersect(p->GetBoundingCircle(), BOSS::GetBoundingCircle()))
	{
		if (p->isNoDmg() == false)
		{
			p->TakeDamage(1);
			X::PlayAudio(mHitSprite, false, 0.2f, 0.2f, 0.2f);
		}
	}
}