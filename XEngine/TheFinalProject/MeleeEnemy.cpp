#include "MeleeEnemy.h"
#include "AnimationState.h"
#include "EnemyBullet.h"

Enemy::Enemy(Math::Vector2 pos, float speed, int sprite) :
	mPosition{ pos },
	mSpeed{ speed },
	mSpriteNum{ sprite },
	mAnimationState{ Animation::RightStand },
	standTimer{ standDuration },
	LeftmoveTimer{ LeftmoveDuration },
	RightmoveTimer{ RightmoveDuration },
	DeadTimer{ DeadDuration },
	AttackRate{ 2.0f }
	{

	eEnergy = new EnemyBullet(false, X::LoadTexture("eBullet.png"), Math::Vector2::Zero(), Math::Vector2::Zero());

	EnemyStandTexture[0] = X::LoadTexture("EBasicRight.png");
	EnemyStandTexture[1] = X::LoadTexture("EBasicLeft.png");

	EnemyLeftTexture[0] = X::LoadTexture("WalkingLeft.png");
	EnemyLeftTexture[1] = X::LoadTexture("WalkingLeft2.png");
	EnemyLeftTexture[2] = X::LoadTexture("WalkingLeft3.png");

	EnemyRightTexture[0] = X::LoadTexture("WalkingRight.png");
	EnemyRightTexture[1] = X::LoadTexture("WalkingRight2.png");
	EnemyRightTexture[2] = X::LoadTexture("WalkingRight3.png");

	EnemyDeadTexture[0] = X::LoadTexture("Death1.png");
	EnemyDeadTexture[1] = X::LoadTexture("Death2.png");
	EnemyDeadTexture[2] = X::LoadTexture("Death3.png");
	EnemyDeadTexture[3] = X::LoadTexture("Death4.png");
	EnemyDeadTexture[4] = X::LoadTexture("Death5.png");
	EnemyDeadTexture[5] = X::LoadTexture("Death6.png");
	EnemyDeadTexture[6] = X::LoadTexture("Death7.png");

	}

void Enemy::Update(float deltaTime, X::Math::Vector2 targetPos, Fighter *p)
{


	Math::Vector2 E = Enemy::GetPosition();
	Math::Vector2 P = targetPos;
	X::Math::Vector2 Din = P - E;
	Din = X::Math::Normalize(Din);
	X::Math::Vector2 vel = Din * BulletSpeed;
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
		eEnergy->Update(deltaTime);
		eEnergy->Render();

		AttackTimer -= deltaTime;
		if (AttackTimer <= 0.0f)
		{
			eEnergy->Fire(E, vel);
			AttackTimer = AttackRate;
			X::PlayAudio(mAttackSprite, false, 0.2f, 0.2f, 0.2f);
		}
	}

	if (!Dead)
	{
		if (Health < 0)
		{
			mAnimationState = Animation::Death;
			eEnergy->Destroy();
		}
	}

	// switch on animation state
	switch (mAnimationState)
	{
	case Animation::Left:
		LeftmoveFrameCount = 3;
		LeftmoveDuration = 0.25f;
		LeftmoveTimer -= deltaTime;
		if (LeftmoveTimer <= 0.0f)
		{
			LeftmoveTimer = LeftmoveDuration;
			LeftmoveFrame = (LeftmoveFrame + 1) % LeftmoveFrameCount;
		}
		break;
	case Animation::Right:
		RightmoveFrameCount = 3;
		RightmoveDuration = 0.25f;
		RightmoveTimer -= deltaTime;
		if (RightmoveTimer <= 0.0f)
		{
			RightmoveTimer = RightmoveDuration;
			RightmoveFrame = (RightmoveFrame + 1) % RightmoveFrameCount;
		}
		break;
	case Animation::Death:
		DeadFrameCount = 7;
		DeadDuration = 0.15f;
		DeadTimer -= deltaTime;
		if (DeadTimer <= 0.0f)
		{
			DeadTimer = DeadDuration;
			DeadFrame = (DeadFrame + 1) % DeadFrameCount;
		}
	}

	// update the image index in the array to render.
}

void Enemy::Render()
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

void Enemy::Kill()
{
	Dead = true;
	X::PlayAudio(mDeathSprite, false, 0.2f, 0.2f, 0.2f);
}

void Enemy::Collision(Fighter *p)
{
	if (eEnergy->IsActive())
	{
		if (Math::Intersect(p->GetBoundingCircle(), eEnergy->GetBoundingCircle()))
		{
			eEnergy->Destroy();
			if (p->isNoDmg() == false)
			{
				p->TakeDamage(1);
				X::PlayAudio(mHitSprite, false, 0.2f, 0.2f, 0.2f);
			}
		}
	}
}