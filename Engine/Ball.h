#pragma once
#include "Graphics.h"
#include "SpriteCodex.h"
#include "Vec2.h"


class Ball
{
public:
	Ball() = default;
	Ball(const Vec2& pos_in, const Vec2& dir_in);
	void Draw(Graphics& gfx) const;
	void Movement(float dt);
	bool DoWallCollision(const RectF& walls);
	void ReboundX();
	void ReboundY();
	RectF GetRect() const;
	Vec2 GetVel() const;
	Vec2 GetPos() const;
	void SetDirection(const Vec2& dir);
	void SetPos(class Paddle& pad);
	void SetSpeed(char merkki);
	void SetResetBall(bool status);
	bool fail = false;
private:
	bool ResetBall = true;
	float speed = 500.0f;
	float baseSpeed = 500.0f;
	float speedUp = 0.0f;
	static constexpr float radius = 7.0f;
	Vec2 pos;
	Vec2 vel;
	
};