#include "EnemyBullet.h"

EnemyBullet::EnemyBullet(bool active, int sprite, Math::Vector2 pos, Math::Vector2 vel) :
	mIsActive{ active },
	mSpriteNum{ sprite },
	mPosition{ pos },
	mVelocity{ vel }
	{}


void EnemyBullet::Update(float deltaTime)
{
	if (IsActive())
	{
		mPosition += mVelocity * deltaTime;

		//HACK: Assume the bullet only goes upwards
		if (mPosition.x < -20.0f || mPosition.x > 500.0f)
		{
			Destroy();
		}
	}
}

void EnemyBullet::Render()
{
	if (IsActive() == false)
	{
		return;
	}

	X::DrawSprite(mSpriteNum, mPosition);
}

void EnemyBullet::Fire(const Math::Vector2& pos, const Math::Vector2& vel)
{
	mPosition = pos;
	mVelocity = vel;
	mIsActive = true;
}

void EnemyBullet::Destroy()
{
	mIsActive = false;
}
