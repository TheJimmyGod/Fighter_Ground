#include "SkyEnemy.h"
#include "AnimationState.h"
#include "EnemyBullet2.h"

Enemy2::Enemy2(Math::Vector2 pos, float speed, int sprite) :
	mPosition{ pos },
	mSpeed{ speed },
	mSpriteNum{ sprite },
	mAnimationState{ Animation::RightStand },
	standTimer{ standDuration },
	AttackRate{ 5.0f }
{
	eEnergy2 = new EnemyBullet2(false, X::LoadTexture("eBullet2.png"), Math::Vector2::Zero(), Math::Vector2::Zero());

	EnemyStandTexture[0] = X::LoadTexture("MonsterRight.png");
	EnemyStandTexture[1] = X::LoadTexture("MonsterLeft.png");
}

void Enemy2::Update(float deltaTime, X::Math::Vector2 targetPos, Fighter *p)
{


	Math::Vector2 E = Enemy2::GetPosition();
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
	if (mPosition.x <= targetPos.x)
	{
		mAnimationState = Animation::RightStand;
		mPosition.x += mSpeed * deltaTime;
	}
	if (mPosition.x >= targetPos.x)
	{
		mAnimationState = Animation::LeftStand;
		mPosition.x -= mSpeed * deltaTime;
	}
	eEnergy2->Update(deltaTime);
	eEnergy2->Render();

	AttackTimer -= deltaTime;
	if (AttackTimer <= 0.0f)
	{
		eEnergy2->Fire(E, vel);
		AttackTimer = AttackRate;
		X::PlayAudio(mAttackSprite, false, 0.2f, 0.2f, 0.2f);
	}

	// switch on animation state
	

	// update the image index in the array to render.
}

void Enemy2::Render()
{
	switch (mAnimationState)
	{
	case Animation::LeftStand:
		X::DrawSprite(EnemyStandTexture[1], mPosition);
		break;
	case Animation::RightStand:
		X::DrawSprite(EnemyStandTexture[0], mPosition);
		break;
	}
}

void Enemy2::Collision(Fighter *p)
{
	if (eEnergy2->IsActive())
	{
		if (Math::Intersect(p->GetBoundingCircle(), eEnergy2->GetBoundingCircle()))
		{
			eEnergy2->Destroy();
			if (p->isNoDmg() == false)
			{
				p->TakeDamage(1);
				X::PlayAudio(mHitSprite, false, 0.2f, 0.2f, 0.2f);
			}
		}
	}
}