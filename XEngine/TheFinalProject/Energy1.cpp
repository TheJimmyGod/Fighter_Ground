#include "Energy1.h"


SpecialEnergy::SpecialEnergy(bool active, int sprite, Math::Vector2 pos, Math::Vector2 vel):
	mIsActive{ active },
	mSpriteNum{sprite},
	mPosition{ pos },
	mVelocity{vel}
	{}

void SpecialEnergy::Update(float deltaTime)
{
	if (IsActive())
	{
		mPosition += mVelocity * deltaTime;

		//HACK: Assume the bullet only goes upwards
		if (mPosition.x < -100.0f || mPosition.x > 500.0f)
		{
			Destroy();
		}
	}
}

void SpecialEnergy::Render()
{
	if (IsActive() == false)
	{
		return;
	}

	X::DrawSprite(mSpriteNum, mPosition);
}

void SpecialEnergy::Fire(const Math::Vector2& pos, const Math::Vector2& vel)
{
	mPosition = pos;
	mVelocity = vel;
	mIsActive = true;
}

void SpecialEnergy::Destroy()
{
	mIsActive = false;
}