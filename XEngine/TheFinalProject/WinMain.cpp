#include <XEngine.h>
#include <typeinfo>
#include <exception>
#include <functional>
#include "TheFighter.h"
#include "AnimationState.h"
#include "Energy1.h"
#include "Energy2.h"
#include "EnemyBullet.h"
#include "EnemyBullet2.h"
#include "MeleeEnemy.h"
#include "SkyEnemy.h"
#include "Boss.h"
#include "Eventlistener.h"
#include "EventManager.h"
#include "Leaderboard.h"
#include "HUD.h"


using std::string;
Fighter* dude = nullptr;
Enemy* Badass = nullptr;
Enemy2* Baster = nullptr;
BOSS* Boss = nullptr;
HUD* hud = nullptr;


EventManager pEventManager;
EventListener ShootListener(GameEventType::Shoot);
EventListener ShootSListener(GameEventType::ShootS);
EventListener DeathListener(GameEventType::Death);
Leaderboard* pLeaderboard;

const int HeroWidth = 50;
const int HeroHeight = 80;
const float HeroSpeed = 90.0f;

const int EnemyWidth = 80;
const int EnemyHeight = 130;
const float EnemySpeed = 30.0f;

const float EnemySpeed2 = 20.0f;
const float BossSpeed = 12.0f;

const char* ErrorImage = "spac.jpg";
const char* BackGroundImage = "BackGround.jpg";
const char* HeroTexture = "BasicRight.png";
const char* EnergyTexture1 = "Missile1.png";
const char* EnergyTexture2 = "Missile2.png";
const char* EnemyBulletTexture = "eBullet.png";
const char* GameOver = "GameOver.png";
const char* BackGroundMusic = "Music.mp3";
const char* EnemyTexture2 = "MonsterRight.png";
const char* BossTexture = "StandRight.png";
const char* BossSound = "Boss.wav";

const int kHalfWidth = 64;
const int kHalfHeight = 54;
const int kMaxEnergy = 255;

const int EnemyKHalfWidth = 25;
const int EnemyKHalfHeight = 15;
const int kMaxEnemyBullet = 255;

int gEnergyIndex1 = 0;
int gEnergyIndex2 = 0;
int EnemyBulletIndex = 0;
int WeaponType = 1;
int bgSprite = -1;
int HeroSprite = -1;
int EnemySprite = -1;
int EnergySprite1 = -1;
int EnergySprite2 = -1;
int EnemyBulletSprite = -1;
int Times = 0;
int Score = 0;
int GameOverSprite = -1;
int mMusicSprite = -1;
int EnemySprite2 = -1;
int BossSprite = -1;
int BossSoundSprite = -1;

float DeadTime;
float DeadRate;

float DeadTime2;
float DeadRate2;

bool EnemyDeath = false;
bool CheckingMoment = false;
bool BossComing = false;

void DrawBG();
void Initialize();

NormalEnergy gEnergy1[kMaxEnergy];
SpecialEnergy gEnergy2[kMaxEnergy];

template <class T>
void FireEnergy();
void UpdateEnergy(float deltaTime);
void RenderEnergy();
void NormalCollisions();
void SpecialCollisions();
void NormalCollisions2();
void SpecialCollisions2();

bool GameLoop(float deltaTime)
{
	std::string s = std::to_string(Score);
	const char* scores = s.c_str();



	X::DrawScreenText(scores, 410.0f, 15.0f, 10.0f, X::Math::Vector4::White());
	DrawBG();
	dude->Update(deltaTime);
	dude->Render();
	hud->Update(Times, dude->GetHealth());
	hud->Render();
	pLeaderboard->PrintLeaderboard();

	if (dude->GetHealth() < 0)
	{
		X::DrawSprite(GameOverSprite, dude->GetPosition());
		pEventManager.RegisterListener(GameEventType::Death, DeathListener);
		pEventManager.Dispatch(GameEventType::Death);
		X::DrawScreenText("Game Over!", 40.0f, 60.0f, 70.0f, X::Math::Vector4::Red());
		X::DrawScreenText(scores, 175.0f, 120.0f, 50.0f, X::Math::Vector4::DarkGray());
	}

	
	if (Badass->GetHealth() < 0)
	{	
		DeadRate = 1.0f;
		DeadTime -= deltaTime;
		if (DeadTime <= 0.0f)
		{
			
			DeadTime = DeadRate;
			Badass->Kill();
			delete Badass;
			Badass = nullptr;
			Score += 25;
			float randomEnemyNumber = X::RandomFloat(0, 2);
			if (randomEnemyNumber > 1)
			{
				Badass = new Enemy(Math::Vector2(-40, 170.0f), EnemySpeed, EnemySprite);
			}
			else
			{
				Badass = new Enemy(Math::Vector2(470, 170.0f), EnemySpeed, EnemySprite);
			}
			Badass->IsDead() == false;
		}
	}

    Badass->Update(deltaTime, dude->GetPosition(), dude);
	Badass->Render();
	if (!dude->isdead())
	{
		if (X::IsKeyPressed(X::Keys::P))
		{
			switch (WeaponType)
			{
			case 1:
				FireEnergy<NormalEnergy>();
				if (!dude->OnAir())
				{
					Times += 1;
					if (Times == 4)
					{
						WeaponType = 2;
					}
				}
				break;
			case 2:
				for (int i = 0; i < 3; i++)
				{
					FireEnergy<SpecialEnergy>();
				}
				Times = 0;
				WeaponType = 1;
				break;
			default:
				XLOG("Unhandled AttackType");
				break;
			}
		}
	}
	
	UpdateEnergy(deltaTime);
	RenderEnergy();
	if (Badass->IsDead() == false)
	{
		NormalCollisions();
		SpecialCollisions();
	}
	if (BossComing == true)
	{
		if (Boss->IsDead() == false)
		{
			NormalCollisions2();
			SpecialCollisions2();
		}
	}
	

	if (Score > 200 && CheckingMoment == false)
	{
		CheckingMoment = true;
		EnemySprite2 = X::LoadTexture(EnemyTexture2);
		float randomEnemyNumber2 = X::RandomFloat(0, 2);
		if (randomEnemyNumber2 > 1)
		{
			Baster = new Enemy2(Math::Vector2(-10, 0.0f), EnemySpeed2, EnemySprite2);
		}
		else
		{
			Baster = new Enemy2(Math::Vector2(470, 0.0f), EnemySpeed2, EnemySprite2);
		}
		
	}

	if (Score > 500 && BossComing == false)
	{
		BossComing = true;
		BossSoundSprite = X::LoadAudio(BossSound);
		X::PlayAudio(BossSoundSprite, false, 0.1f, 0.1f, 0.1f);
		BossSprite = X::LoadTexture(BossTexture);
		float randomEnemyNumber3 = X::RandomFloat(0, 2);
		if (randomEnemyNumber3 > 1)
		{
			Boss = new BOSS(Math::Vector2(-90, 110.0f), BossSpeed, BossSprite);
		}
		else
		{
			Boss = new BOSS(Math::Vector2(510, 110.0f), BossSpeed, BossSprite);
		}
	}

	if (CheckingMoment == true)
	{
		Baster->Update(deltaTime, dude->GetPosition(), dude);
		Baster->Render();
	}

	if (BossComing == true)
	{
		Boss->Update(deltaTime, dude->GetPosition(), dude);
		Boss->Render();
		if (Boss->GetHealth() < 0)
		{
			DeadRate2 = 15.0f;
			DeadTime2 -= deltaTime;
			if (DeadTime2 <= 0.0f)
			{
				DeadTime2 = DeadRate2;
				Boss->Kill();
				delete Boss;
				Boss = nullptr;
				Score += 100;
				BossSoundSprite = X::LoadAudio(BossSound);
				X::PlayAudio(BossSoundSprite, false, 0.1f, 0.1f, 0.1f);
				float randomEnemyNumber3 = X::RandomFloat(0, 2);
				if (randomEnemyNumber3 > 1)
				{
					Boss = new BOSS(Math::Vector2(-90, 110.0f), BossSpeed, BossSprite);


				}
				else
				{
					Boss = new BOSS(Math::Vector2(510, 110.0f), BossSpeed, BossSprite);
				}
				Boss->IsDead() == false;
			}
		}
	}

	return X::IsKeyPressed(X::Keys::ESCAPE);
}

int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	X::Start("Fighter Ground", hInstance, 450, 258, 0);

	Initialize();
	try
	{
		bgSprite = X::LoadTexture(ErrorImage);
		if (bgSprite >= 0)
		{
			throw "Back Ground Sprite Error";
		}
	}
	catch (const char*)
	{
		BackGroundImage = "BackGround.jpg";
		bgSprite = X::LoadTexture(BackGroundImage);
	}
	X::Run(GameLoop);
	delete dude;
	dude = nullptr;
	delete Badass;
	Badass = nullptr;
	delete Boss;
	Boss = nullptr;
	delete pLeaderboard;
	pLeaderboard = nullptr;
	X::Stop();
	return 0;
}


void Initialize()
{
	// Set texture path
	X::SetTexturePath("../Data/Final");
	X::SetAudioPath("../Data/Sounds");

	// Load background image
	bgSprite = X::LoadTexture(BackGroundImage);
	XASSERT(bgSprite != -1, "Background Not Loaded");

	// Init Hero
	HeroSprite = X::LoadTexture(HeroTexture);
	GameOverSprite = X::LoadTexture(GameOver);
	XASSERT(HeroSprite != -1, "HeroSprite Not Loaded");
	std::map<string, int> data = { {"Player" , Score} };
	pLeaderboard = new Leaderboard();
	pLeaderboard->InitializeData(data);
	hud = new HUD();
	dude = new Fighter(Math::Vector2(200.0f, 180.0f), HeroSpeed, HeroSprite);
	float randomEnemyNumber = X::RandomFloat(0, 2);
	if (randomEnemyNumber > 1)
	{
		Badass = new Enemy(Math::Vector2(-70, 170.0f), EnemySpeed, EnemySprite);
	}
	else
	{
		Badass = new Enemy(Math::Vector2(470, 170.0f), EnemySpeed, EnemySprite);
	}

	// Init Bullet
	EnergySprite1 = X::LoadTexture(EnergyTexture1);
	EnergySprite2 = X::LoadTexture(EnergyTexture2);
	EnemyBulletSprite = X::LoadTexture(EnemyBulletTexture);

	mMusicSprite = X::LoadAudio(BackGroundMusic);
	X::PlayAudio(mMusicSprite, true, 0.1f, 1.0f, 1.0f);
	for (int i = 0; i < kMaxEnergy; i++)
	{
		gEnergy1[i] = *(new NormalEnergy(false, EnergySprite1, Math::Vector2::Zero(), Math::Vector2::Zero()));
	}

	for (int i = 0; i < kMaxEnergy; i++)
	{
		gEnergy2[i] = *(new SpecialEnergy(false, EnergySprite2, Math::Vector2::Zero(), Math::Vector2::Zero()));
	}
	// Events
}


void DrawBG()
{
	X::DrawSprite(bgSprite, Math::Vector2::Zero());
}

template <class T>
void FireEnergy()
{
	const int index1 = gEnergyIndex1;
	const int index2 = gEnergyIndex2;
	float randomNumber = X::RandomFloat(-35, 35);
	if (typeid(T) == typeid(NormalEnergy))
	{
		// Fire a SmallBullet
		if (gEnergy1[index1].IsActive() == false)
		{
			if (dude->GetAnimationState() == Animation::RightAttack)
			{
				// If the bullet at the current index is not already active, set its position and velocity.
				Math::Vector2 vel(250.0f, randomNumber);
				Math::Vector2 pos = dude->GetPosition();
				gEnergy1[index1].Fire(pos, vel);

				// Increment the index
				gEnergyIndex1 = (gEnergyIndex1 + 1) % kMaxEnergy;
				pEventManager.RegisterListener(GameEventType::Shoot, ShootListener);
				pEventManager.Dispatch(GameEventType::Shoot);
			}
			else if (dude->GetAnimationState() == Animation::LeftAttack)
			{
				// If the bullet at the current index is not already active, set its position and velocity.
				Math::Vector2 vel(-250.0f, randomNumber);
				Math::Vector2 pos = dude->GetPosition();
				gEnergy1[index1].Fire(pos, vel);

				// Increment the index
				gEnergyIndex1 = (gEnergyIndex1 + 1) % kMaxEnergy;
				pEventManager.RegisterListener(GameEventType::Shoot, ShootListener);
				pEventManager.Dispatch(GameEventType::Shoot);
			}

		}
	}
	else if (typeid(T) == typeid(SpecialEnergy))
	{
		// Fire a BigBullet
		if (gEnergy2[index2].IsActive() == false)
		{
			if (dude->GetAnimationState() == Animation::RightAttack)
			{
				// If the bullet at the current index is not already active, set its position and velocity.
				Math::Vector2 vel(250.0f, -10.0f);
				Math::Vector2 pos = dude->GetPosition();
				gEnergy2[index2].Fire(pos, vel);

				// Increment the index
				gEnergyIndex2 = (gEnergyIndex2 + 1) % kMaxEnergy;
				pEventManager.RegisterListener(GameEventType::ShootS, ShootSListener);
				pEventManager.Dispatch(GameEventType::ShootS);
			}
			else if (dude->GetAnimationState() == Animation::LeftAttack)
			{
				// If the bullet at the current index is not already active, set its position and velocity.
				Math::Vector2 vel(-250.0f, -10.0f);
				Math::Vector2 pos = dude->GetPosition();
				gEnergy2[index2].Fire(pos, vel);

				// Increment the index
				gEnergyIndex2 = (gEnergyIndex2 + 1) % kMaxEnergy;
				pEventManager.RegisterListener(GameEventType::ShootS, ShootSListener);
				pEventManager.Dispatch(GameEventType::ShootS);
			}
		}
	}
}

void UpdateEnergy(float deltaTime)
{
	for (int i = 0; i < kMaxEnergy; i++)
	{
		gEnergy1[i].Update(deltaTime);
		gEnergy2[i].Update(deltaTime);
	}
}

void RenderEnergy()
{
	for (int i = 0; i < kMaxEnergy; i++)
	{
		gEnergy1[i].Render();
		gEnergy2[i].Render();
	}
}

void SpecialCollisions()
{
	for (int j = 0; j < kMaxEnergy; ++j)
	{
		if (gEnergy2[j].IsActive())
		{
			if (Math::Intersect(Badass->GetBoundingCircle(), gEnergy2[j].GetBoundingCircle()))
			{
				gEnergy2[j].Destroy();
				Badass->TakeDamage(3);
			}
		}
	}
}

void SpecialCollisions2()
{
	for (int j = 0; j < kMaxEnergy; ++j)
	{
		if (gEnergy2[j].IsActive())
		{
			if (Math::Intersect(Boss->GetBoundingCircle(), gEnergy2[j].GetBoundingCircle()))
			{
				gEnergy2[j].Destroy();
				Boss->TakeDamage(2);
			}
		}
	}
}


void NormalCollisions()
{
	for (int i = 0; i < kMaxEnergy; ++i)
	{
		if (gEnergy1[i].IsActive())
		{
			if (Math::Intersect(Badass->GetBoundingCircle(), gEnergy1[i].GetBoundingCircle()))
			{
				gEnergy1[i].Destroy();
				Badass->TakeDamage(1);
			}
		}
	}
}

void NormalCollisions2()
{
	for (int i = 0; i < kMaxEnergy; ++i)
	{
		if (gEnergy1[i].IsActive())
		{
			if (Math::Intersect(Boss->GetBoundingCircle(), gEnergy1[i].GetBoundingCircle()))
			{
				gEnergy1[i].Destroy();
				Boss->TakeDamage(1);
			}
		}
	}
}