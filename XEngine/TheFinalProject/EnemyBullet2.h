#ifndef SKY_ENEMY_BULLET_HEADER_H_
#define SKY_ENEMY_BULLET_HEADER_H_

#include <XEngine.h>
#include "TheFighter.h"
using namespace X;

class EnemyBullet2
{
public:
	EnemyBullet2() {}
	EnemyBullet2(bool active, int sprite, Math::Vector2 pos, Math::Vector2 vel);
	~EnemyBullet2() {}

	void Update(float deltaTime);
	void Render();

	void Fire(const Math::Vector2& pos, const Math::Vector2& vel);
	void Destroy();

	bool IsActive() const { return mIsActive; }
	Math::Circle GetBoundingCircle() const { return Math::Circle(mPosition, 5.0f); }

private:
	bool mIsActive;
	int mSpriteNum;
	Math::Vector2 mPosition;
	Math::Vector2 mVelocity;
	const char* EnemyBulletTexture = "eBullet2.png";
};
#endif // !SKY_ENEMY_BULLET_HEADER_H_