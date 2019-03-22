#include "TheFighter.h"
#include "AnimationState.h"

Fighter::Fighter(Math::Vector2 pos, float speed, int sprite):
	mPosition{ pos },
	mSpeed{speed},
	mSpriteNum{ sprite },
	mAnimationState{ Animation::RightStand },
	standTimer{ standDuration },
	LeftmoveTimer{ LeftmoveDuration },
	RightmoveTimer{RightmoveDuration},
	RightAttackTimer{RightAttackDuration},
	LeftAttackTimer{ LeftAttackDuration },
	RightZtimer{RightZDuration},
	LeftZtimer{LeftZDuration},
	RightDeathTimer{ RightDeathDuration },
	LeftDeathTimer{LeftDeathDuration}
	{
	HeroStandTexture[0] = X::LoadTexture("BasicRight.png");
	HeroStandTexture[1] = X::LoadTexture("BasicLeft.png");

	HeroRightZTexture[0] = X::LoadTexture("Zpackright1.png");
	HeroRightZTexture[1] = X::LoadTexture("Zpackright2.png");

	HeroLeftZTexture[0] = X::LoadTexture("Zpackleft1.png");
	HeroLeftZTexture[1] = X::LoadTexture("Zpackleft2.png");

	HeroLeftTexture[0] = X::LoadTexture("Movement1left.png");
	HeroLeftTexture[1] = X::LoadTexture("Movement2left.png");

	HeroRightTexture[0] = X::LoadTexture("Movement1right.png");
	HeroRightTexture[1] = X::LoadTexture("Movement2right.png");

	HeroRightDeathTexture[0] = X::LoadTexture("BasicRight.png");
	HeroRightDeathTexture[1] = X::LoadTexture("Death1Right.png");
	HeroRightDeathTexture[2] = X::LoadTexture("Death2Right.png");

	HeroLeftDeathTexture[0] = X::LoadTexture("BasicLeft.png");
	HeroLeftDeathTexture[1] = X::LoadTexture("Death1Left.png");
	HeroLeftDeathTexture[2] = X::LoadTexture("Death2Left.png");

	HeroRightAttackTexture[0] = X::LoadTexture("Attack1right.png");
	HeroRightAttackTexture[1] = X::LoadTexture("Attack2right.png");
	HeroRightAttackTexture[2] = X::LoadTexture("Attack3right.png");
	HeroRightAttackTexture[3] = X::LoadTexture("Attack4right.png");
	HeroRightAttackTexture[4] = X::LoadTexture("Attack5right.png");
	HeroRightAttackTexture[5] = X::LoadTexture("Attack6right.png");

	HeroLeftAttackTexture[0] = X::LoadTexture("Attack1left.png");
	HeroLeftAttackTexture[1] = X::LoadTexture("Attack2left.png");
	HeroLeftAttackTexture[2] = X::LoadTexture("Attack3left.png");
	HeroLeftAttackTexture[3] = X::LoadTexture("Attack4left.png");
	HeroLeftAttackTexture[4] = X::LoadTexture("Attack5left.png");
	HeroLeftAttackTexture[5] = X::LoadTexture("Attack6left.png");
}

float gravity = 40.0f;

void Fighter::Update(float deltaTime)
{

	if (mPosition.y < 180.0f)
	{
		mPosition.y += gravity * deltaTime;
	}

	if (mPosition.y > 300.0f)
	{
		mPosition.y = 180.0f;
	}

	// Stop him from going off the top of the screen.
	if (mPosition.y < 1.5f)
	{
		mPosition.y = 1.5f;
	}

	if (!Dead)
	{
		if (X::IsKeyDown(X::Keys::A)) // moving left
		{
			mAnimationState = Animation::Left;
			// update your animation state to "moveLeft"
			if (mPosition.x < 0.0f)
			{

			}
			else
			{
				mPosition.x -= mSpeed * deltaTime;
			}

		}
		if (X::IsKeyDown(X::Keys::D)) // moving right
		{
			mAnimationState = Animation::Right;
			// update animation state to "moveRight"
			if (mPosition.x > 432.5f)
			{

			}
			else
			{
				mPosition.x += mSpeed * deltaTime;
			}
		}
		if (X::IsKeyDown(X::Keys::W))
		{
			if (mAnimationState == Animation::Right)
			{
				mAnimationState = Animation::RightJump;
				if (mPosition.y > 245.5f)
				{

				}
				else
				{
					mPosition.y -= mSpeed * deltaTime;
				}
			}
			if (mAnimationState == Animation::Left)
			{
				mAnimationState = Animation::LeftJump;
				if (mPosition.y > 245.5f)
				{

				}
				else
				{
					mPosition.y -= mSpeed * deltaTime;
				}
			}
		}
		if (X::IsKeyDown(X::Keys::P))
		{
			if (mAnimationState == Animation::Right && X::IsKeyPressed(X::Keys::P) && mPosition.y > 170.0f)
			{
				mAnimationState = Animation::RightAttack;
			}
			else if (mAnimationState == Animation::Left && X::IsKeyPressed(X::Keys::P) && mPosition.y > 170.0f)
			{
				mAnimationState = Animation::LeftAttack;
			}

		}
	}
	OntheSky();
	if (NoDmg == true)
	{
		HitTimer -= deltaTime;
		if (HitTimer <= 0.0f)
		{
			HitTimer = HitRate;
			NoDmg = false;
		}
	}
	if (!Dead)
	{
		if (Health < 0)
		{
			Kill();
			if (mAnimationState == Animation::Left || mAnimationState == Animation::LeftJump)
			{
				mAnimationState = Animation::LeftDeath;
			}
			if (mAnimationState == Animation::Right || mAnimationState == Animation::RightJump)
			{
				mAnimationState = Animation::RightDeath;
			}
			

		}
	}

	// switch on animation state
	switch (mAnimationState)
	{
	case Animation::Left:
		LeftmoveFrameCount = 2;
		LeftmoveDuration = 0.3f;
		LeftmoveTimer -= deltaTime;
		if (LeftmoveTimer <= 0.0f)
		{
			LeftmoveTimer = LeftmoveDuration;
			LeftmoveFrame = (LeftmoveFrame + 1) % LeftmoveFrameCount;
		}
		break;
	case Animation::Right:
		RightmoveFrameCount = 2;
		RightmoveDuration = 0.3f;
		RightmoveTimer -= deltaTime;
		if (RightmoveTimer <= 0.0f)
		{
			RightmoveTimer = RightmoveDuration;
			RightmoveFrame = (RightmoveFrame + 1) % RightmoveFrameCount;
		}
		break;
	case Animation::LeftAttack:
		LeftAttackFrameCount = 6;
		LeftAttackDuration = 0.15f;
		LeftAttackTimer -= deltaTime;
		if (LeftAttackTimer <= 0.0f)
		{
			LeftAttackTimer = LeftAttackDuration;
			LeftAttackFrame = (LeftAttackFrame + 1) % LeftAttackFrameCount;
		}
		break;
	case Animation::RightAttack:
		RightAttackFrameCount = 6;
		RightAttackDuration = 0.15f;
		RightAttackTimer -= deltaTime;
		if (RightAttackTimer <= 0.0f)
		{
			RightAttackTimer = RightAttackDuration;
			RightAttackFrame = (RightAttackFrame + 1) % RightAttackFrameCount;
		}
		break;
	case Animation::RightJump:
		RightZFrameCount = 2;
		RightZDuration = 1.0f;
		RightZtimer -= deltaTime;
		if (RightZtimer <= 0.0f)
		{
			RightZtimer = RightZDuration;
			RightZFrame = (RightZFrame + 1) % RightZFrameCount;
		}
		break;
	case Animation::LeftJump:
		LeftZFrameCount = 2;
		LeftZDuration = 1.0f;
		LeftZtimer -= deltaTime;
		if (LeftZtimer <= 0.0f)
		{
			LeftZtimer = LeftZDuration;
			LeftZFrame = (LeftZFrame + 1) % LeftZFrameCount;
		}
		break;
	case Animation::LeftDeath:
		LeftDeathFrameCount = 3;
		LeftDeathDuration = 3.0f;
		LeftDeathTimer -= deltaTime;
		if (LeftDeathTimer <= 0.0f)
		{
			LeftDeathTimer = LeftDeathDuration;
			LeftDeathFrame = (LeftDeathFrame + 1) % LeftDeathFrameCount;
		}
		break;
	case Animation::RightDeath:
		RightDeathFrameCount = 3;
		RightDeathDuration = 3.0f;
		RightDeathTimer -= deltaTime;
		if (RightDeathTimer <= 0.0f)
		{
			RightDeathTimer = RightDeathDuration;
			RightDeathFrame = (RightDeathFrame + 1) % RightDeathFrameCount;
		}
		break;

	}
	// update the image index in the array to render.
}

void Fighter::Render()
{
	switch (mAnimationState)
	{
	case Animation::LeftStand:
		X::DrawSprite(HeroStandTexture[1], mPosition);
		break;
	case Animation::RightStand:
		X::DrawSprite(HeroStandTexture[0], mPosition);
		break;
	case Animation::Left:
		if (OnAir()) { X::DrawSprite(HeroLeftZTexture[LeftmoveFrame], mPosition); }
		else { X::DrawSprite(HeroLeftTexture[LeftmoveFrame], mPosition); }
		break;
	case Animation::Right:
		if (OnAir()) { X::DrawSprite(HeroRightZTexture[RightmoveFrame], mPosition); }
		else { X::DrawSprite(HeroRightTexture[RightmoveFrame], mPosition); }
		break;
	case Animation::LeftAttack:
		X::DrawSprite(HeroLeftAttackTexture[LeftAttackFrame], mPosition);
		break;
	case Animation::RightAttack:
		X::DrawSprite(HeroRightAttackTexture[RightAttackFrame], mPosition);
		break;
	case Animation::RightJump:
		X::DrawSprite(HeroRightZTexture[RightZFrame], mPosition);
		break;
	case Animation::LeftJump:
		X::DrawSprite(HeroLeftZTexture[LeftZFrame], mPosition);
		break;
	case Animation::LeftDeath:
		X::DrawSprite(HeroLeftDeathTexture[LeftDeathFrame], mPosition);
		break;
	case Animation::RightDeath:
		X::DrawSprite(HeroRightDeathTexture[RightDeathFrame], mPosition);
		break;
	}
}

void Fighter::Kill()
{
	Dead = true;
}
