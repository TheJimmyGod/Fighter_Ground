#include "Energy2.h"


NormalEnergy::NormalEnergy(bool active, int sprite, Math::Vector2 pos, Math::Vector2 vel) :
	mIsActive{ active },
	mSpriteNum{ sprite },
	mPosition{ pos },
	mVelocity{ vel }
	{}

void NormalEnergy::Update(float deltaTime)
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

void NormalEnergy::Render()
{
	if (IsActive() == false)
	{
		return;
	}

	X::DrawSprite(mSpriteNum, mPosition);
}

void NormalEnergy::Fire(const Math::Vector2& pos, const Math::Vector2& vel)
{
	mPosition = pos;
	mVelocity = vel;
	mIsActive = true;
}

void NormalEnergy::Destroy()
{
	mIsActive = false;
}
