#include "EnemyBullet2.h"

EnemyBullet2::EnemyBullet2(bool active, int sprite, Math::Vector2 pos, Math::Vector2 vel):
	mIsActive{active},
	mSpriteNum{sprite},
	mPosition{pos},
	mVelocity{vel}
	{}

void EnemyBullet2::Update(float deltaTime)
{
	if (IsActive())
	{
		mPosition += mVelocity * deltaTime;

		//HACK: Assume the bullet only goes upwards
		if (mPosition.y < -20.0f || mPosition.y > 500.0f)
		{
			Destroy();
		}
	}
}

void EnemyBullet2::Render()
{
	if (IsActive() == false)
	{
		return;
	}

	X::DrawSprite(mSpriteNum, mPosition);
}

void EnemyBullet2::Fire(const Math::Vector2& pos, const Math::Vector2& vel)
{
	mPosition = pos;
	mVelocity = vel;
	mIsActive = true;
}

void EnemyBullet2::Destroy()
{
	mIsActive = false;
}
