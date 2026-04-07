#include "Paddle.h"
#include <cmath>

Paddle::Paddle(const Vec2& pos_in, float halfWidth_in, float halfHeight_in)
	:
	pos(pos_in),
	halfWidth(halfWidth_in),
	halfHeight(halfHeight_in)
{
	eXitFactor = MaxExitRation / halfWidth;
}

void Paddle::Draw(Graphics& gfx) const
{
	RectF rect = GetRect();
	gfx.DrawRect(rect, WingColor);
	rect.left += WingWidth;
	rect.right -= WingWidth;
	gfx.DrawRect(rect, color);

}

bool Paddle::BallCollision(Ball& ball)
{
	const Vec2 ballpos = ball.GetPos();
	const RectF rect = GetRect();

	if (GetRect().IsOverlappingWith(ball.GetRect()))
	{
		if (CatchCount())
		{
			ball.SetResetBall(true);
			const Vec2 Dir = Vec2(0.2f, -1.0f);
			ball.SetDirection(Dir);
			CatchCounter -= 1;
		}
		if (std::signbit(ball.GetVel().x) == std::signbit((ballpos - rect.GetCenter()).x)
			|| ballpos.x >= rect.left && ballpos.x <= rect.right)
		{
			Vec2 dir;
			const float xDiffrence = ballpos.x - pos.x;
			dir = Vec2(xDiffrence * eXitFactor, -1.0f);
			ball.SetDirection(dir);
		}
		else
		{
			ball.ReboundX();
		}
		
		return true;
	}
	return false;
}

void Paddle::WallCollision(const RectF& walls)
{
	const RectF rect = GetRect();
	if (rect.left < walls.left)
	{
		pos.x += walls.left - rect.left;
	}
	else if (rect.right > walls.right)
	{
		pos.x -= rect.right - walls.right;
	}
}

void Paddle::Movement(Keyboard& kbd, float dt)
{
	if (kbd.KeyIsPressed(VK_LEFT))
	{
		pos.x -= speed * dt;
	}
	else if (kbd.KeyIsPressed(VK_RIGHT))
	{
		pos.x += speed * dt;
	}
}

RectF Paddle::GetRect() const
{
	return RectF::FromCenter(pos, halfWidth, halfHeight);
}

Vec2 Paddle::GetPos() const
{
	return pos;
}

void Paddle::ResetCooldown(float dt)
{
	if (Cooldown)
	{
		if ((cooldowntimerstart += dt) > cooldowntimerend)
		{
			Cooldown = false;
			cooldowntimerstart = 0.0f;
		}
	}
}

void Paddle::PaddleSize(float dt)
{
	switch (padsize)
	{
	case PadSize::Small:
		halfWidth = 30.0f;
		break;

	case PadSize::Normal:
		halfWidth = 40.0f;
		break;

	case PadSize::Large:
		halfWidth = 50.0f;
		if ((PadtimerStart += dt) > PadtimerEnd)
		{
			PadtimerStart = 0.0f;
			if (PadChoiceSize)
			{
				padsize = PadSize::Small;
			}
			else
			{
				padsize = PadSize::Normal;
			}
		}
		else
		{
			padsize = PadSize::Large;
		}
		break;
	}
}

bool Paddle::CatchCount() const
{
	if (CatchCounter > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
	
}

void Paddle::SetCatch()
{
	CatchCounter = 3;
}

void Paddle::DrawCatchSign(Graphics& gfx) const
{
	if (CatchCount())
	{
		gfx.DrawCircle(120, 30, 10, Colors::Green);
	}
}

void Paddle::SetPadChoiceSize(bool status)
{
	if (status == true)
	{
		PadChoiceSize = true;
	}
	else if (status == false)
	{
		PadChoiceSize = false;
	}
	
}

Paddle::Guns::Guns(const Vec2& pos_in)
	:
	pos(pos_in)
{

}

void Paddle::Guns::DrawAmmo(Graphics& gfx) const
{
	if (guns)
	{
		gfx.DrawCircle((int)pos.x, (int)pos.y, radius, Colors::Red);
	}
}

void Paddle::Guns::AmmoMovment(float dt)
{
	if (guns)
	{
		pos.y -= speed * dt;
	}
}

void Paddle::Guns::SetPos(const Paddle& pad)
{
	if (!guns)
	{
		pos = pad.GetPos();
	}
}

void Paddle::Guns::WallCollision(const RectF walls)
{
	if (pos.y - radius < walls.top)
	{
		guns = false;
	}
}

RectF Paddle::Guns::GetRect() const
{
	return RectF::FromCenter(pos, radius, radius);
}

Vec2 Paddle::Guns::GetPos() const
{
	return pos;
}

void Paddle::Guns::SetGuns(bool status)
{
	if (status == true)
	{
		guns = true;
	}
	else if (status == false)
	{
		guns = false;
	}
}

bool Paddle::Guns::GetGuns() const
{
	return guns;
}
