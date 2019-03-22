#ifndef HUD_HEADER
#define HUD_HEADER

#include "XEngine.h"

class HUD
{
public:
	HUD();
	~HUD();

	void Update(int E, int Hp)
	{
		EnergyRate = E;
		HPRate = Hp;
	}

	void Render() const
	{
		switch (EnergyRate)
		{
		case 0:
			X::DrawSprite(Energy[0], X::Math::Vector2(400.0f, 210.0f));
			break;
		case 1:
			X::DrawSprite(Energy[1], X::Math::Vector2(400.0f, 210.0f));
			break;
		case 2:
			X::DrawSprite(Energy[2], X::Math::Vector2(400.0f, 210.0f));
			break;
		case 3:
			X::DrawSprite(Energy[3], X::Math::Vector2(400.0f, 210.0f));
			break;
		case 4:
			X::DrawSprite(Energy[4], X::Math::Vector2(400.0f, 210.0f));
			break;
		}
		switch (HPRate)
		{
		case 0:
			X::DrawSprite(Health[0], X::Math::Vector2(0.0f, 0.0f));
			break;
		case 1:
			X::DrawSprite(Health[0], X::Math::Vector2(0.0f, 0.0f));
			X::DrawSprite(Health[1], X::Math::Vector2(45.0f, 0.0f));
			break;
		case 2:
			X::DrawSprite(Health[0], X::Math::Vector2(0.0f, 0.0f));
			X::DrawSprite(Health[1], X::Math::Vector2(45.0f, 0.0f));
			X::DrawSprite(Health[2], X::Math::Vector2(90.0f, 0.0f));
		}
	}

private:
	int Energy[5];
	int Health[3];

	int EnergyRate;
	int HPRate;
};

HUD::HUD()
{
	Energy[0] = X::LoadTexture("Energy1.png");
	Energy[1] = X::LoadTexture("Energy2.png");
	Energy[2] = X::LoadTexture("Energy3.png");
	Energy[3] = X::LoadTexture("Energy4.png");
	Energy[4] = X::LoadTexture("Energy5.png");

	Health[0] = X::LoadTexture("Health1.png");
	Health[1] = X::LoadTexture("Health2.png");
	Health[2] = X::LoadTexture("Health3.png");

	EnergyRate = 0;
}

HUD::~HUD()
{
}

#endif // !HUD_HEADER
