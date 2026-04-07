#include "Screens.h"


Screen::Screen(const std::string& text, const Surface& filename, const Vei2& in_textpos)
	:
	menutext(text),
	textpos(in_textpos),
	BackGround(filename),
	menucount(0)
{
	nlines = Menu.GetNumberOfLines(text);
	SetSelectionPos();
}



void Screen::Draw(Graphics& gfx)
{
	SpriteEffect::NoChroma E;
	gfx.DrawSprite(Vei2(0, 0), BackGround, E);
	Menu.DrawTexts(menutext, textpos, gfx, Colors::Red);
	DrawSelectionPointer(gfx, SelPointPos);
}


void Screen::DrawSelectionPointer(Graphics& gfx, const Vei2& StartMenuP) const
{
	gfx.DrawCircle(StartMenuP.x, StartMenuP.y, cRadius, Colors::Blue);
}

void Screen::MenuMovement(const Keyboard::Event& e) 
{
	if (e.GetCode() == VK_UP && menucount > 0)
	{
		menucount -= 1;
	}
	if (e.GetCode() == VK_DOWN && menucount < nlines)
	{
		menucount += 1;
	}
}

void Screen::SetSelectionPos()
{
	SelPointPos.x = textpos.x - 30;
	SelPointPos.y = (textpos.y + (Menu.GetcharHeight() / 2)) + (menucount * Menu.GetcharHeight());
}



Screen::Options Screen::ProcessStartMenu(Keyboard& kbd) 
{
	SetSelectionPos();
	const Keyboard::Event e = kbd.ReadKey();
	if (e.IsPress())
	{
		MenuMovement(e);
		if (e.GetCode() == VK_RETURN)
		{
			if (menucount == 0)
			{
				return Options::Play;
			}
			else if (menucount == 1)
			{
				return Options::Option;
			}
			else if (menucount == 2)
			{
				return Options::Info;
			}
			else if (menucount == 3)
			{
				return Options::Quit;
			}
		}
	}
	return Options::Invalid;
}

Screen::InfoOptions Screen::ProcessInfoMenu(Keyboard& kbd)
{
	SetSelectionPos();
	const Keyboard::Event e = kbd.ReadKey();
	if (e.IsPress())
	{
		MenuMovement(e);
		if (e.GetCode() == VK_RETURN)
		{
			if (menucount == 0)
			{
				return InfoOptions::Bricks;
			}
			else if (menucount == 1)
			{
				return InfoOptions::Meters;
			}
			else if (menucount == 2)
			{
				return InfoOptions::Back;
			}
		}
	}
	return InfoOptions::Invalid;
}





