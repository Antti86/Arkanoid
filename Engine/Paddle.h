#pragma once
#include "Graphics.h"
#include "Ball.h"
#include "Vec2.h"
#include "Colors.h"
#include "Rect.h"
#include "Keyboard.h"


class Paddle
{
public:
	class Guns
	{
	public:
		Guns() = default;
		Guns(const Vec2& pos_in);
		void DrawAmmo(Graphics& gfx) const;
		void AmmoMovment(float dt);
		void SetPos(const Paddle& pad);
		void WallCollision(const RectF walls);
		RectF GetRect() const;
		Vec2 GetPos() const;
		void SetGuns(bool status);
		bool GetGuns() const;
	private:
		Vec2 pos;
		static constexpr float speed = 800.0f;
		static constexpr int radius = 6;
		bool guns = false;
	};
public:
	enum class PadSize
	{
		Small,
		Normal,
		Large
	};
	PadSize padsize = { PadSize::Normal };
public:
	Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in);
	void Draw(Graphics& gfx) const;
	bool BallCollision(Ball& ball);
	void WallCollision(const RectF& walls);
	void Movement(Keyboard& kbd, float dt);
	RectF GetRect() const;
	Vec2 GetPos() const;
	void ResetCooldown(float dt);
	void PaddleSize(float dt);
	void SetCatch();
	void DrawCatchSign(Graphics& gfx) const;
	void SetPadChoiceSize(bool status);
private:
	bool CatchCount() const;
	Color color = Colors::White;
	Color WingColor = Colors::Red;
	float WingWidth = 10.0f;
	float speed = 600.0f;		
	float MaxExitRation = 2.8f; 
	float eXitFactor;
	float halfWidth;
	float halfHeight;
	Vec2 pos;
	int CatchCounter = 0;
	float PadtimerEnd = 15.0f;
	float PadtimerStart = 0.0f;
	bool PadChoiceSize = false;
	float cooldowntimerstart = 0.0f;		//cooldown käytössä mutta vaatii lisää testiä
	float cooldowntimerend = 0.3f;
	bool Cooldown = false;
};