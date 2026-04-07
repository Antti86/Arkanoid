/*
 * Brick.cpp
 * Copyright (C) 2026 Antti Parhiala
 * Licensed under GPL-3.0-or-later. See License.txt.
 */
#include "Brick.h"
#include <assert.h>
#include <cmath>


Brick::Brick(const RectF& rect_in, Color c_in)
	:
	rect(rect_in),
	c(c_in)
{
	if (c == Colors::Orange)
	{
		state = State::indestructible;
	}
	else if (c == Colors::Gray)
	{
		state = State::TwoHit;
	}
	else if (c == Colors::Magenta)
	{
		state = State::LifeUp;
	}
	else if (c == Colors::Yellow)
	{
		state = State::SpeedUp;
	}
	else if (c == Colors::Blue || c == Colors::Red || c == Colors::Green)
	{
		state = State::MeterUp;
	}
	else if (c == Colors::Scarlet)
	{
		state = State::LargePad;
	}
	else if (c == Colors::MidnightBlue)
	{
		state = State::MultipleBalls;
	}
	else if (c == Colors::LawnGreen)
	{
		state = State::Catcher;
	}
	else if (c == Colors::Purple)
	{
		state = State::MeterFull;
	}
	else if (c == Colors::Black)
	{
		state = State::Empty;
		destroyed = true;
	}
	else
	{
		state = State::Basic;
	}
}


void Brick::Draw(Graphics& gfx) const
{
	
	if (!destroyed && !firstcol)
	{
		gfx.DrawRect(rect.Expand( -padding), c);
	}
	if (!destroyed && firstcol)
	{
		gfx.DrawRectSpacec(rect.Expand(-padding), c);
	}
	if (destroyed && indestructible)				//Lvl up ei toiminu kunnolla joskus, siksi tämä, selvitä tarviiko viel..
	{
		gfx.DrawRect(rect.Expand(-padding), c);
	}
}

bool Brick::CheckBallCollision(const Ball& ball) const
{
	if (indestructible && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		return true;
	}
	if (!destroyed && GetRect().IsOverlappingWith(ball.GetRect()))
	{
		return true;
	}
	return false;
}

void Brick::ExecuteBallCollision(Ball& ball)
{
	assert(CheckBallCollision(ball));
	const Vec2 ballpos = ball.GetPos();

	if (std::signbit(ball.GetVel().x) == std::signbit((ballpos - GetCenter()).x)
		|| ballpos.x >= rect.left && ballpos.x <= rect.right)
	{
		ball.ReboundY();
	}
	else
	{
		ball.ReboundX();
	}
}

bool Brick::CheckAmmoCollision(const Paddle::Guns& gun) const
{
	if (indestructible && GetRect().IsOverlappingWith(gun.GetRect()))
	{
		return true;
	}
	if (!destroyed && GetRect().IsOverlappingWith(gun.GetRect()))
	{
		return true;
	}
	return false;
}


RectF Brick::GetRect() const
{
	return rect;
}

Vec2 Brick::GetCenter() const
{
	return Vec2(rect.GetCenter());
}

Brick::State Brick::GetState() const
{
	return state;
}

void Brick::SetStateBroken()
{
	state = State::Broken;
}

Color Brick::FlashEffect(Color c)
{
	if (ColorFlash)
	{
		if (c.GetB() >= 245)
		{
			ColorFlash = false;
			c = Colors::Orange;
		}
		else
		{
			c = Color(c.GetR(), c.GetG() + 1, c.GetB() + 3);
		}
	}
	else
	{
		c = Colors::Orange;
	}
	return c;
}

Color Brick::ColorPulse(Color c)
{
	if (increasing)
	{
		if (c.GetR() >= 253)
		{
			increasing = false;
		}
		else
		{
			c = Color(c.GetR() + 1, c.GetG() + 1, c.GetB() + 1);
		}
	}
	else
	{
		if (c.GetR() <= 3)
		{
			increasing = true;
		}
		else
		{
			c = Color(c.GetR() - 1, c.GetG() - 1, c.GetB() - 1);
		}
	}
	return c;
}

void Brick::SetColor(char merkki)
{
	if (merkki == 'P')
	{
		c = ColorPulse(c);
	}
	if (merkki == 'F')
	{
		c = FlashEffect(c);
	}
}

bool Brick::GetFirstcol()
{
	return firstcol;
}

bool Brick::GetDestroyed()
{
	return destroyed;
}

void Brick::SetDestr()
{
	destroyed = true;
}

void Brick::Setfirstcol()
{
	firstcol = true;
}

