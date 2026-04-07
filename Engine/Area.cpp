#include "Area.h"

Area::Area(const RectF& rect_in, Color c_in)
	:
	rect(rect_in),
	c(c_in)
	
{}

void Area::DrawWall(Graphics & gfx) const
{
	gfx.DrawRect(rect, c);
}

RectF Area::GetRect() const
{
	return rect;
}



void Area::Life::DrawLife(Graphics& gfx) const
{
	Vei2 life1 = { 510, 15 };
	Vei2 life2 = { 550, 15 };
	Vei2 life3 = { 590, 15 };
	Vei2 life4 = { 630, 15 };
	Vei2 life5 = { 670, 15 };
	
	SpriteEffect::Chroma E{ Colors::White };
	if (life == 6)
	{
		gfx.DrawSprite(life1, surf, E);
		gfx.DrawSprite(life2, surf, E);
		gfx.DrawSprite(life3, surf, E);
		gfx.DrawSprite(life4, surf, E);
		gfx.DrawSprite(life5, surf, E);
	}
	if (life == 5)
	{
		gfx.DrawSprite(life1, surf, E);
		gfx.DrawSprite(life2, surf, E);
		gfx.DrawSprite(life3, surf, E);
		gfx.DrawSprite(life4, surf, E);
	}
	if (life == 4)
	{
		gfx.DrawSprite(life1, surf, E);
		gfx.DrawSprite(life2, surf, E);
		gfx.DrawSprite(life3, surf, E);
	}
	if (life == 3)
	{
		gfx.DrawSprite(life1, surf, E);
		gfx.DrawSprite(life2, surf, E);
	}
	if (life == 2)
	{
		gfx.DrawSprite(life1, surf, E);
	}
}

int Area::Life::GetLife() const
{
	return life;
}

void Area::Life::SetLife(char merkki)
{
	if (merkki == '+' && life < 7)
	{
		life += 1;
	}
	if (merkki == '-')
	{
		life -= 1;
	}
	if (merkki == 'R')
	{
		life = 4;
	}
}


void Area::Meter::DrawMeter(Graphics& gfx, MeterPos& pos, float b_meterY, Color c) const
{
	RectF MeterLeft = { Vec2(50.0f, b_meterY), Vec2(70.0f, MeterMin) };
	RectF MeterRight = { Vec2(740.0f, b_meterY), Vec2(760.0f, MeterMin) };
	switch (pos)
	{
	case MeterPos::None:
		break;

	case MeterPos::Left:
		gfx.DrawRect(pohja_left, Colors::White);
		gfx.DrawCircle(60, 560, 20, c);
		gfx.DrawRect(MeterLeft, c);
		break;

	case MeterPos::Right:
		gfx.DrawRect(pohja_right, Colors::White);
		gfx.DrawCircle(750, 560, 20, c);
		gfx.DrawRect(MeterRight, c);
		break;
	}
}

void Area::Meter::SetBlueM(char merkki)
{
	if (Blue != MeterPos::None )
	{
		if (merkki == '+' && b_meterY > MeterMax)
		{
			b_meterY -= 8.0f;

		}
		if (merkki == '-' && b_meterY < MeterMin)
		{
			b_meterY += 0.1f;
		}
		if (merkki == 'F')
		{
			b_meterY = MeterMax;
		}
	}
}

void Area::Meter::SetRedM(Life& life)
{
	if (Red != MeterPos::None)
	{
		r_meterY -= 10.0f;

		if (r_meterY <= MeterMax)
		{
			life.SetLife('+');
			r_meterY = MeterMin;
		}
	}
}

void Area::Meter::SetGreenM(char merkki)
{
	if (Green != MeterPos::None)
	{
		if (merkki == '+' && g_meterY > MeterMax)
		{
			g_meterY -= 7.0f;
		}
		if (merkki == '-' && g_meterY < MeterMin)
		{
			g_meterY += 19.2f;
		}
		if (merkki == 'F')
		{
			g_meterY = MeterMax;
		}
	}
}

void Area::Meter::ResetAllmeter()
{
	Blue = MeterPos::None;
	Red = MeterPos::None;
	Green = MeterPos::None;
	b_meterY = 530.0f;
	r_meterY = 530.0f;
	g_meterY = 530.0f;
}

float Area::Meter::GetMeterMin() const
{
	return MeterMin;
}

float Area::Meter::GetG_meterY() const
{
	return g_meterY;
}

float Area::Meter::GetB_meterY() const
{
	return b_meterY;
}

float Area::Meter::GetR_meterY() const
{
	return r_meterY;
}
