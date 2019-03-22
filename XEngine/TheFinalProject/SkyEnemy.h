#ifndef _SKY_ENEMY_HEADER_H_
#define _SKY_ENEMY_HEADER_H_

#include <XEngine.h>
using namespace X;

#include "AnimationState.h"
#include "EnemyBullet2.h"
#include "TheFighter.h"

class Enemy2
{
public:
	Enemy2() {}
	Enemy2(Math::Vector2 pos, float speed, int sprite);
	~Enemy2() {}

	void Update(float deltaTime, X::Math::Vector2 targetPos, Fighter* p);
	void Render();

	const Math::Vector2& GetPosition() const { return mPosition; }
	float GetSpeed() const { return mSpeed; }

	void SetPosition(const Math::Vector2 pos) { mPosition = pos; }
	void SetSpeed(float speed) { mSpeed = speed; }

	Animation GetAnimationState() { return mAnimationState; }
	Math::Circle GetBoundingCircle() const { return Math::Circle(mPosition, 20.0f); }
	void Collision(Fighter *p);

private:
	bool Dead = false;

	int mAttackSprite = LoadAudio("Fire.wav");
	int mHitSprite = LoadAudio("Shoot2.wav");

	Math::Vector2 mPosition;
	float mSpeed;
	int mSpriteNum;
	Animation mAnimationState;
	// add animation state variable

	float standDuration; // length of time of the animation
	int standFrameCount; // number of images in the animation
	int standFrame; // the current frame you are rendering
	float standTimer;

	int EnemyStandTexture[2];

	float AttackTimer;
	float AttackRate;
	float BulletSpeed = 170.0f;
	EnemyBullet2* eEnergy2;
};

#endif // !_SKY_ENEMY_HEADER_H_