/*
 * Brick.h
 * Copyright (C) 2026 Antti Parhiala
 * Licensed under GPL-3.0-or-later. See License.txt.
 */

#pragma once
#include "Graphics.h"
#include "Rect.h"
#include "Colors.h"
#include "Ball.h"
#include "Paddle.h"

class Brick
{
public:
	enum class State
	{
		Basic,
		Broken,
		TwoHit,
		indestructible,
		SpeedUp,
		SpeedDown,
		LifeUp,
		MeterUp,
		MeterFull,
		Catcher,
		MultipleBalls,
		LargePad,
		Empty
	};

public:
	Brick() = default;
	Brick(const RectF& rect_in, Color c_in);
	void Draw(Graphics& gfx) const;
	bool CheckBallCollision(const Ball& ball) const;
	void ExecuteBallCollision(Ball& ball);
	bool CheckAmmoCollision(const Paddle::Guns& gun) const;
	RectF GetRect() const;
	Vec2 GetCenter() const;
	void SetColor(char merkki);
	bool GetFirstcol();
	bool GetDestroyed();
	void SetDestr();
	void Setfirstcol();
	bool indestructible = false;
	bool ColorChange = false;
	bool ColorFlash = false;
	State GetState() const;
	void SetStateBroken();
private:
	Color FlashEffect(Color c);
	Color ColorPulse(Color c);
	static constexpr float padding = 1.0f;
	RectF rect;
	Color c;
	bool destroyed = false;
	bool firstcol = false;
	bool increasing = true;
	State state;
};