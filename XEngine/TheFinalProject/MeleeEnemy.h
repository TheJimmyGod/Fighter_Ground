#ifndef _MELEE_ENEMY_HEADER_H_
#define _MELEE_ENEMY_HEADER_H_

#include <XEngine.h>
using namespace X;

#include "AnimationState.h"
#include "EnemyBullet.h"
#include "Energy1.h"
#include "Energy2.h"
#include "TheFighter.h"

class Enemy
{
public:
	Enemy() {}
	Enemy(Math::Vector2 pos, float speed, int sprite);
	~Enemy() {}

	void Update(float deltaTime, X::Math::Vector2 targetPos, Fighter* p);
	void Render();

	const Math::Vector2& GetPosition() const { return mPosition; }
	float GetSpeed() const { return mSpeed; }

	void SetPosition(const Math::Vector2 pos) { mPosition = pos; }
	void SetSpeed(float speed) { mSpeed = speed; }

	bool IsDead() { return Dead; }
	void TakeDamage(int Dmg) { Health -= Dmg; }

	void SetHealth(int hp) { Health = hp; }
	int GetHealth() const { return Health; }

	Animation GetAnimationState() { return mAnimationState; }
	Math::Circle GetBoundingCircle() const { return Math::Circle(mPosition, 20.0f); }

	void Kill();
	void Collision(Fighter *p);

private:
	bool Dead = false;

	int Health = 12;
	int mAttackSprite = LoadAudio("Fire.wav");
	int mHitSprite = LoadAudio("Shoot2.wav");
	int mDeathSprite = LoadAudio("Magnum.wav");

	Math::Vector2 mPosition;
	float mSpeed;
	int mSpriteNum;
	Animation mAnimationState;
	// add animation state variable

	float standDuration; // length of time of the animation
	int standFrameCount; // number of images in the animation
	int standFrame; // the current frame you are rendering
	float standTimer;

	float LeftmoveDuration;
	int LeftmoveFrameCount;
	int LeftmoveFrame;
	float LeftmoveTimer;

	float RightmoveDuration;
	int RightmoveFrameCount;
	int RightmoveFrame;
	float RightmoveTimer;

	float DeadDuration;
	int DeadFrameCount;
	int DeadFrame;
	float DeadTimer;

	int EnemyStandTexture[2];
	int EnemyRightTexture[3];
	int EnemyLeftTexture[3];
	int EnemyDeadTexture[7];

	float AttackTimer;
	float AttackRate;
	float BulletSpeed = 170.0f;
	EnemyBullet* eEnergy;
};

#endif // !_MELEE_ENEMY_HEADER_H_