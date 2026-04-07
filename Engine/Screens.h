#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Rect.h"
#include "SpriteEffect.h"
#include "Keyboard.h"
#include "Font.h"

class Screen
{
public:
	enum class Options
	{
		Play,
		Option,
		Info,
		Quit,
		Invalid
	};
	enum class InfoOptions
	{
		Bricks,
		Meters,
		Back,
		Invalid
	};
public:
	Screen(const std::string& text, const Surface& filename, const Vei2& in_textpos);
	void Draw(Graphics& gfx);
	Options ProcessStartMenu(Keyboard& kbd);
	InfoOptions ProcessInfoMenu(Keyboard& kbd);
private:
	void DrawSelectionPointer(Graphics& gfx, const Vei2& StartMenuP) const;
	void MenuMovement(const Keyboard::Event& e);
	void SetSelectionPos();
private:
	const Surface& BackGround;
	Font Menu = ("kuvat//fontsheet.bmp");
	Vei2 textpos;
	int menucount;
	Vei2 SelPointPos;
	int cRadius = 6;
	int nlines;
	std::string menutext;

							//mahollisia vaihtoehtoja
	//liitä enumit yhdeksi luokaksi ja erottele ne jotenki eri objekteihin processkeyn kautta
	//erottele enumit ctr kautta objekteihin
	//luo objektit enumeihin ja kåytä void funktiota valintojen siirtoo?

	//onglema on luoda näppäistö komennot eri objekteihin samalla funktiolla

	
};


































