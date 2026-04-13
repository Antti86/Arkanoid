/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.cpp																			  *
 *	Copyright 2016 PlanetChili.net <http://www.planetchili.net>							  *
 *																						  *
 *	This file is part of The Chili DirectX Framework.									  *
 *																						  *
 *	The Chili DirectX Framework is free software: you can redistribute it and/or modify	  *
 *	it under the terms of the GNU General Public License as published by				  *
 *	the Free Software Foundation, either version 3 of the License, or					  *
 *	(at your option) any later version.													  *
 *																						  *
 *	The Chili DirectX Framework is distributed in the hope that it will be useful,		  *
 *	but WITHOUT ANY WARRANTY; without even the implied warranty of						  *
 *	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the						  *
 *	GNU General Public License for more details.										  *
 *																						  *
 *	You should have received a copy of the GNU General Public License					  *
 *	along with The Chili DirectX Framework.  If not, see <http://www.gnu.org/licenses/>.  *
 ******************************************************************************************/
 // Edited by Antti Parhiala, 2026
#include "MainWindow.h"
#include "Game.h"
#include "Colors.h"

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd )
	
{
}

void Game::Go()
{
	gfx.BeginFrame();
	elapsedTime = ft.Mark();
	while (elapsedTime > 0.0f)
	{
		dt = std::min(0.0025f, elapsedTime);
		UpdateModel(dt);
		elapsedTime -= dt;
	}
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel(float dt)
{
	if (GameScreen == GameScreen::Playing)		
	{
		ball.SetPos(pad);					//Pallon sijainti ja liike

		if (ball.DoWallCollision(walls) || ball2.DoWallCollision(walls) || ball3.DoWallCollision(walls))
		{
			//‰‰net t‰h‰n joskus
		}
		if (Ball_1)
		{
			ball.Movement(dt);
		}
		if (Ball_2)
		{
			ball2.SetResetBall(false);
			ball2.Movement(dt);
		}
		if (Ball_3)
		{
			ball3.SetResetBall(false);
			ball3.Movement(dt);
		}
		if (wnd.kbd.KeyIsPressed(VK_SPACE))
		{
			ball.SetResetBall(false);
		}
		if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		{
			GameScreen = GameScreen::StartMenu;
			meter.ResetAllmeter();
			life.SetLife('R');
			SetLevel(Level::Lvl1);
		}

		if (wnd.kbd.KeyIsPressed(VK_CONTROL) && meter.GetB_meterY() <= meter.GetMeterMin() &&
			meter.Blue != Area::Meter::MeterPos::None)
		{
			meter.SetBlueM('-');			//Sinisen mittarin mekaniikka
			ball.SetSpeed('s');
			ball2.SetSpeed('s');
			ball3.SetSpeed('s');
		}
		else
		{
			ball.SetSpeed('r');
			ball2.SetSpeed('r');
			ball3.SetSpeed('r');
		}

		gun.WallCollision(walls);
		gun.SetPos(pad);
		gun.AmmoMovment(dt);
		
		if (wnd.kbd.KeyIsPressed(VK_TAB) && meter.Green != Area::Meter::MeterPos::None
			&& meter.GetG_meterY() <= meter.GetMeterMin() && !gun.GetGuns())			//Ase funktiot
		{
			gun.SetGuns(true);
			meter.SetGreenM('-');
		}

		if (testmode)
		{
			if (wnd.kbd.KeyIsPressed('C'))					
			{
				meter.Green = Area::Meter::MeterPos::Left;
			}
			if (wnd.kbd.KeyIsPressed('W'))		
			{
				meter.SetGreenM('+');
			}
			if (wnd.kbd.KeyIsPressed('P'))
			{
				meter.Blue = Area::Meter::MeterPos::Right;
			}
			if (wnd.kbd.KeyIsPressed('Q'))
			{
				meter.SetBlueM('+');
			}
		}

		if (!Ball_1)
		{
			ball.fail = true;
		}
		if (!Ball_2)
		{
			ball2.fail = true;
		}
		if (!Ball_3)
		{
			ball3.fail = true;
		}

		bool allfail = true;
		if (ball.fail || ball2.fail || ball3.fail)				//El‰m‰ mekaniikka
		{
			allfail = allfail && ball.fail && ball2.fail && ball3.fail;

			if (ball.fail)
			{
				Ball_1 = false;
			}
			if (ball2.fail)
			{
				Ball_2 = false;
			}
			if (ball3.fail)
			{
				Ball_3 = false;
			}

			if (allfail)
			{
				life.SetLife('-');
				ball.SetResetBall(true);
				ball.fail = false;
				Ball_1 = true;

				if (life.GetLife() == 0)
				{
					GameScreen = GameScreen::GameOver;			

				}
			}

		}

		pad.Movement(wnd.kbd, dt);		//Paddlen funktiot
		pad.WallCollision(walls);
		pad.PaddleSize(dt);
		pad.DrawCatchSign(gfx);
		pad.ResetCooldown(dt);
		if (Ball_1)
		{
			pad.BallCollision(ball);
		}
		if (Ball_2)
		{
			pad.BallCollision(ball2);
		}
		if (Ball_3)
		{
			pad.BallCollision(ball3);
		}
		
		
		if (level == Level::Lvl1)			//Lvl p‰ivitys
		{
			BrickCollision(bricks, ball, BrickTotal_lvl1);
			if (LvlUp)
			{
				level = Level::Lvl2;
				ball.SetResetBall(true);
				LvlUp = false;
				SetLevel(Level::Lvl2);
			}
		}
		else if (level == Level::Lvl2)
		{
			BrickCollision(bricks, ball, BrickTotal_lvl2);
			if (LvlUp)
			{
				level = Level::Lvl3;
				ball.SetResetBall(true);
				LvlUp = false;
				SetLevel(Level::Lvl3);
			}
		}
		else if (level == Level::Lvl3)
		{
			BrickCollision(bricks, ball, BrickTotal_lvl3);
			BrickCollision(bricks2, ball, BrickTotal_lvl3_1);
			if (LvlUp)
			{
				GameScreen = GameScreen::ChoiceScreen1;
				ball.SetResetBall(true);
				level = Level::Lvl4;
				LvlUp = false;
				SetLevel(Level::Lvl4);
			}
		}
		else if (level == Level::Lvl4)
		{
			BrickCollision(bricks, ball, BrickTotal_lvl4);
			if (LvlUp)
			{
				level = Level::Lvl5;
				ball.SetResetBall(true);
				LvlUp = false;
				SetLevel(Level::Lvl5);
			}
		}
		else if (level == Level::Lvl5)
		{
			BrickCollision(bricks, ball, BrickTotal_lvl5);
			BrickCollision(bricks2, ball, BrickTotal_lvl5_1);
			if (LvlUp)
			{
				level = Level::Lvl6;
				ball.SetResetBall(true);
				LvlUp = false;
				SetLevel(Level::Lvl6);
			}
		}
		else if (level == Level::Lvl6)
		{
			BrickCollision(bricks, ball, BrickTotal_lvl6);
			if (LvlUp)
			{
				GameScreen = GameScreen::ChoiceScreen2;
				SetLevel(Level::Lvl7);
				ball.SetResetBall(true);
				level = Level::Lvl7;
				LvlUp = false;
			}
		}
		else if (level == Level::Lvl7)
		{
			BrickCollision(bricks, ball, ball2, ball3, BrickTotal_lvl7);
			BrickCollision(bricks2, ball, ball2, ball3, BrickTotal_lvl7_1);
			if (LvlUp)
			{
				SetLevel(Level::Lvl8);
				ball.SetResetBall(true);
				level = Level::Lvl8;
				LvlUp = false;
			}
		}
		else if (level == Level::Lvl8)
		{
			BrickCollision(bricks, ball, BrickTotal_lvl8);
			BrickCollision(bricks2, ball, BrickTotal_lvl8_1);
			if (LvlUp)
			{
				ball.SetResetBall(true);
				level = Level::Lvl9;
				LvlUp = false;
			}
		}
		else if (level == Level::TestiV)
		{
			BrickCollision(bricks, ball, BrickTotal_lvlTestiV);
		}

		if (testmode)
		{

			if (wnd.kbd.KeyIsPressed('1'))			
			{
				SetLevel(Level::Lvl1);
				level = Level::Lvl1;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('2'))
			{
				SetLevel(Level::Lvl2);
				level = Level::Lvl2;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('3'))
			{
				SetLevel(Level::Lvl3);
				level = Level::Lvl3;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('4'))
			{
				SetLevel(Level::Lvl4);
				level = Level::Lvl4;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('5'))
			{
				SetLevel(Level::Lvl5);
				level = Level::Lvl5;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('6'))
			{
				SetLevel(Level::Lvl6);
				level = Level::Lvl6;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('7'))
			{
				SetLevel(Level::Lvl7);
				level = Level::Lvl7;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('8'))
			{
				SetLevel(Level::Lvl8);
				level = Level::Lvl8;
				ball.SetResetBall(true);
			}
			if (wnd.kbd.KeyIsPressed('T'))
			{
				level = Level::TestiV;
				SetLevel(Level::TestiV);
				ball.SetResetBall(true);
			}
		}



	}
	else if (GameScreen == GameScreen::GameOver)		//Game over ruudun mekaniikka
	{
		if (wnd.kbd.KeyIsPressed(VK_SPACE))			
		{
			GameScreen = GameScreen::StartMenu;
			life.SetLife('R');
			meter.ResetAllmeter();
		}
	}
	else if (GameScreen == GameScreen::StartMenu)		//alku menu ruudun mekaniikka
	{
		Screen::Options o = StartMenu.ProcessStartMenu(wnd.kbd);
		switch (o)
		{
		case Screen::Options::Play:
			level = Level::Lvl1;
			SetLevel(Level::Lvl1);
			GameScreen = GameScreen::Playing;
			break;
		case Screen::Options::Option:
			GameScreen = GameScreen::Options;
			break;
		case Screen::Options::Info:
			GameScreen = GameScreen::Info;
			break;
		case Screen::Options::Quit:
			wnd.Kill();
			break;
		}
	}
	else if (GameScreen == GameScreen::Options)			//options menu ruudun mekaniikka
	{
		if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
		{
			GameScreen = GameScreen::StartMenu;
		}
	}
	else if (GameScreen == GameScreen::Info)				 // info menu ruudun mekaniikka
	{
		Screen::InfoOptions o = InfoMenu.ProcessInfoMenu(wnd.kbd);
		switch (o)
		{
		case Screen::InfoOptions::Bricks:
			GameScreen = GameScreen::BrickInfo;
			break;
		case Screen::InfoOptions::Meters:
			GameScreen = GameScreen::MeterInfo;
			break;
		case Screen::InfoOptions::Back:
			GameScreen = GameScreen::StartMenu;
			break;
		}
	}
		else if (GameScreen == GameScreen::BrickInfo )
		{
			if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
			{
				GameScreen = GameScreen::Info;
			}
		}
		else if (GameScreen == GameScreen::MeterInfo)
		{
			if (wnd.kbd.KeyIsPressed(VK_ESCAPE))
			{
				GameScreen = GameScreen::Info;
			}
		}
	else if (GameScreen == GameScreen::ChoiceScreen1)		//ensinm‰isen valinta ruudun mekaniikka
	{
		if (wnd.kbd.KeyIsPressed('B'))
		{
			meter.Blue = Area::Meter::MeterPos::Left;
			GameScreen = GameScreen::Playing;
		}
		else if (wnd.kbd.KeyIsPressed('R'))
		{
			meter.Red = Area::Meter::MeterPos::Left;
			GameScreen = GameScreen::Playing;
		}
		else if (wnd.kbd.KeyIsPressed('G'))
		{
			meter.Green = Area::Meter::MeterPos::Left;
			GameScreen = GameScreen::Playing;
		}
	}
	else if (GameScreen == GameScreen::ChoiceScreen2)		//toisen valinta ruudun mekaniikka
	{
		if (wnd.kbd.KeyIsPressed('B'))
		{
			ball.SetSpeed('b');
			GameScreen = GameScreen::Playing;
		}
		else if (wnd.kbd.KeyIsPressed('R'))
		{
			pad.SetPadChoiceSize(true);
			pad.padsize = Paddle::PadSize::Small;
			GameScreen = GameScreen::Playing;
		}
	}
}



void Game::ComposeFrame()
{
	if (GameScreen == GameScreen::StartMenu)
	{
		StartMenu.Draw(gfx);
	}
	else if (GameScreen == GameScreen::Info)
	{
		InfoMenu.Draw(gfx);
	}
		else if (GameScreen == GameScreen::BrickInfo)
		{
			DrawBrickInfo();
		}
		else if (GameScreen == GameScreen::MeterInfo)
		{
			DrawMeterInfo();
		}
	else if (GameScreen == GameScreen::GameOver)
	{
		DrawOver();
	}
	else if (GameScreen == GameScreen::ChoiceScreen1 || GameScreen == GameScreen::ChoiceScreen2)
	{
		
	}
	else if (GameScreen == GameScreen::Playing)
	{
		switch (level)
		{
		case Level::Lvl1:
			DrawLevel(Level::Lvl1);
			break;

		case Level::Lvl2:
			DrawLevel(Level::Lvl2);
			break;

		case Level::Lvl3:
			DrawLevel(Level::Lvl3);
			break;

		case Level::Lvl4:
			DrawLevel(Level::Lvl4);
			break;

		case Level::Lvl5:
			DrawLevel(Level::Lvl5);
			break;

		case Level::Lvl6:
			DrawLevel(Level::Lvl6);
			break;

		case Level::Lvl7:
			DrawLevel(Level::Lvl7);
			break;

		case Level::Lvl8:
			DrawLevel(Level::Lvl8);
			break;

		case Level::Lvl9:
			DrawLevel(Level::Lvl4);
			break;

		case Level::TestiV:
			DrawLevel(Level::TestiV);
			break;
		}

		leftwall.DrawWall(gfx);
		rightwall.DrawWall(gfx);
		topwall.DrawWall(gfx);
		life.DrawLife(gfx);
		pad.Draw(gfx);
		meter.DrawMeter(gfx, meter.Blue, meter.GetB_meterY(), Colors::Blue);
		meter.DrawMeter(gfx, meter.Red, meter.GetR_meterY(), Colors::Red);
		meter.DrawMeter(gfx, meter.Green, meter.GetG_meterY(), Colors::Green);
		gun.DrawAmmo(gfx);
		
		if (Ball_1)
		{
			ball.Draw(gfx);
		}
		if (Ball_2)
		{
			ball2.Draw(gfx);
		}
		if (Ball_3)
		{
			ball3.Draw(gfx);
		}
	}
}


void Game::DrawBack()
{
	SpriteEffect::GhostNochroma E{ 0.2f };
	gfx.DrawSprite(Vei2(0, 0), MenuBackground, E);
}

void Game::BrickCollision(std::vector<Brick>& bricks, Ball& ball, int BrickTotal_lvl1)
{
	bool BallCollisionhappend = false;
	bool AmmoCollisionhappend = false;
	float CurColDist;
	int CurColIndex;
	bool allDestroyed = true;
	for (int i = 0; i < BrickTotal_lvl1; i++)
	{
		if (bricks[i].ColorChange)
		{
			bricks[i].SetColor('P');
		}
		if (bricks[i].ColorFlash)
		{
			bricks[i].SetColor('F');
		}

		allDestroyed = allDestroyed && bricks[i].GetDestroyed() == true;

		if (bricks[i].CheckBallCollision(ball))
		{
			const float newColDist = (ball.GetPos() - bricks[i].GetCenter()).GetLengthSq();
			if (BallCollisionhappend)
			{
				if (newColDist < CurColDist)
				{
					CurColDist = newColDist;
					CurColIndex = i;
				}
			}
			else
			{
				CurColDist = newColDist;
				CurColIndex = i;
				BallCollisionhappend = true;
			}
		}
		if (bricks[i].CheckAmmoCollision(gun))
		{
			const float newColDist = (gun.GetPos() - bricks[i].GetCenter()).GetLengthSq();
			if (AmmoCollisionhappend)
			{
				if (newColDist < CurColDist)
				{
					CurColDist = newColDist;
					CurColIndex = i;
				}
			}
			else
			{
				CurColDist = newColDist;
				CurColIndex = i;
				AmmoCollisionhappend = true;
			}
		}
	}
	if (allDestroyed)
	{
		LvlUp = true;
		ball.SetSpeed('0');
		Ball_2 = false;
		Ball_3 = false;
	}
	if (BallCollisionhappend || AmmoCollisionhappend)
	{
		if (BallCollisionhappend)
		{
			bricks[CurColIndex].ExecuteBallCollision(ball);
		}
		if (AmmoCollisionhappend)
		{
			gun.SetGuns(false);
		}

		if (bricks[CurColIndex].GetState() == Brick::State::indestructible)
		{
			bricks[CurColIndex].ColorFlash = true;
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::Basic)
		{
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::Broken)
		{
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::TwoHit)
		{
			bricks[CurColIndex].Setfirstcol();
			bricks[CurColIndex].SetStateBroken();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::SpeedUp)
		{
			ball.SetSpeed('+');
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::SpeedDown)
		{
			ball.SetSpeed('-');
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::LifeUp)
		{
			life.SetLife('+');
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::MeterUp)
		{
			meter.SetRedM(life);
			meter.SetGreenM('+');
			meter.SetBlueM('+');
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::MeterFull)
		{
			meter.SetBlueM('F');
			meter.SetGreenM('F');
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::Catcher)
		{
			pad.SetCatch();
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::MultipleBalls)
		{
			Ball_2 = true;
			Ball_3 = true;
			const Vec2 pos = bricks[CurColIndex].GetCenter();
			ball2 = Ball(Vec2(pos), Vec2(0.4f, -1.0f));
			ball3 = Ball(Vec2(pos), Vec2(-0.4f, -1.0f));
			bricks[CurColIndex].SetDestr();
		}
		else if (bricks[CurColIndex].GetState() == Brick::State::LargePad)
		{
			pad.padsize = Paddle::PadSize::Large;
			bricks[CurColIndex].SetDestr();
		}
	}
}


void Game::DrawOver()
{
	SpriteEffect::NoChroma E;
	gfx.DrawSprite(Vei2(250, 150), gameover, E);
}

void Game::DrawBrickInfo()
{
	SpriteEffect::NoChroma E;
	gfx.DrawSprite(Vei2(0, 0), BrickInfo, E);
}

void Game::DrawMeterInfo()
{
	SpriteEffect::NoChroma E;
	gfx.DrawSprite(Vei2(0, 0), MeterInfo, E);
}

void Game::DrawLevel(const Level level)
{
	if (level == Level::Lvl1)
	{
		//SpriteEffect::GhostNochroma E{ 0.2f };
		//gfx.DrawSprite(Vei2(0, 0), MenuBackground, E);			//Vain Release

		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::Lvl2)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::Lvl3)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		for (const Brick& b : bricks2)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::Lvl4)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::Lvl5)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		for (const Brick& b : bricks2)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::Lvl6)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::Lvl7)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		for (const Brick& b : bricks2)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::Lvl8)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
		for (const Brick& b : bricks2)
		{
			b.Draw(gfx);
		}
	}
	else if (level == Level::TestiV)
	{
		for (const Brick& b : bricks)
		{
			b.Draw(gfx);
		}
	}
}

void Game::SetLevel(const Level level)
{
	//Testi Level
	if (level == Level::TestiV)
	{
		bricks.clear();
		bricks.reserve(BrickTotal_lvlTestiV);
		const Vec2 topleft = { GridStartX + (brickWidth * 4), GridStartY + (brickHeight * 5) };
		int i = 0;
		for (int y = 0; y < BrickPysty_lvlTestiV; y++)
		{
			Color c = Colors::MidnightBlue;
			for (int x = 0; x < BrickViisto_lvlTestiV; x++)
			{
				bricks.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
					brickWidth, brickHeight), c));
				if (x == 1)
				{
					bricks[i].ColorChange = true;
				}
				i++;
			}
		}
	}
	if (level == Level::Lvl1)
	{

		bricks.clear();
		bricks.reserve(BrickTotal_lvl1);
		{
			const Vec2 topleft = { GridStartX + (brickWidth * 3), GridStartY + (brickHeight * 3) };
			Color colors[BrickPysty_lvl1] = { Colors::Blue, Colors::Red, Colors::Cyan, Colors::White, Colors::Orange };

			for (int y = 0; y < BrickPysty_lvl1; y++)
			{
				Color c = colors[y];
				for (int x = 0; x < BrickViisto_lvl1; x++)
				{
					int i = y * BrickViisto_lvl1 + x;
					bricks.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
					if (y == 4)
					{
						bricks[i].indestructible = true;
						bricks[i].SetDestr();
					}
				}
			}
		}
	}
	if (level == Level::Lvl2)
	{
		bricks.clear();
		bricks.reserve(BrickTotal_lvl2);
		Color colors[BrickPysty_lvl2] = { Colors::Blue, Colors::White, Colors::Red,
							   Colors::Cyan, Colors::Blue, Colors::Gray };

		const Vec2 topleft = { GridStartX + (brickWidth * 2), GridStartY + (brickHeight * 3) };

		for (int y = 0; y < BrickPysty_lvl2; y++)
		{
			Color c = colors[y];
			for (int x = 0; x < BrickViisto_lvl2; x++)
			{
				bricks.emplace_back( Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
					brickWidth, brickHeight), c));
			}
		}
	}
	if (level == Level::Lvl3)
	{
		{
			bricks.clear();
			bricks.reserve(BrickTotal_lvl3);
			const Vec2 topleft = { GridStartX, GridStartY };
			for (int y = 0; y < BrickPysty_lvl3; y++)
			{
				Color c = Colors::Cyan;
				for (int x = 0; x < BrickViisto_lvl3; x++)
				{
					bricks.emplace_back( Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
				}
			}
		}
		{
			bricks2.clear();
			bricks2.reserve(BrickTotal_lvl3_1);
			const Vec2 topleft = { GridStartX + (brickWidth * 10), GridStartY + (brickHeight * 4) };
			Color c;
			for (int y = 0; y < BrickPysty_lvl3_1; y++)
			{
				for (int x = 0; x < BrickViisto_lvl3_1; x++)
				{
					int i = y * BrickViisto_lvl3_1 + x;
					if (y == 2 && x == 1)
					{
						c = Colors::Magenta;
					}
					else if (y == 1 && x < 2)
					{
						c = Colors::Black;
					}
					else if (y == 2 && x == 0)
					{
						c = Colors::Black;
					}
					else if (y == 3 && x < 2)
					{
						c = Colors::Black;
					}
					else
					{
						c = Colors::Orange;
					}
					bricks2.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
				}
			}
		}
	}
	if (level == Level::Lvl4)
	{
		bricks.clear();
		bricks.reserve(BrickTotal_lvl4);
		const Vec2 topleft = { GridStartX, GridStartY + (brickHeight * 2) };
		Color c;
		for (int y = 0; y < BrickPysty_lvl4; y++)
		{
			for (int x = 0; x < BrickViisto_lvl4; x++)
			{
				int i = y * BrickViisto_lvl4 + x;

				if (y < 8 && x < 5)
				{
					c = Colors::Blue;
				}
				else if (y < 8 && x > 5)
				{
					c = Colors::Red;
				}
				else if (y == 8)
				{
					c = Colors::Gray;
				}
				if (y < 8)
				{
					if (x < 2)
					{
						c = Colors::Black;
					}
					if (x > 3 && x < 10)
					{
						c = Colors::Black;
					}
					if (x > 11)
					{
						c = Colors::Black;
					}
				}
				bricks.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
					brickWidth, brickHeight), c));
			}
		}
	}
	if (level == Level::Lvl5)
	{
		bricks.clear();
		bricks.reserve(BrickTotal_lvl5);
		{
			const Vec2 topleft = { GridStartX + (brickWidth * 2), GridStartY };
			int i = 0;
			int x = 0;
			int y = 0;
			Color c = Colors::Orange;
			for (y = 0; y < BrickPysty_lvl5; y++)
			{
				bricks.emplace_back (Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
					brickWidth, brickHeight), c));

				if (y > 2 && y < 6)
				{
					bricks[i].indestructible = false;
					bricks[i].SetDestr();
				}
				else
				{
					bricks[i].indestructible = true;
				}
				i++;

			}
			const Vec2 topleft2 = { GridStartX + (brickWidth * 2), GridStartY };
			for (x = 0; x < BrickViisto_lvl5; x++)
			{
				bricks.emplace_back(Brick(RectF(topleft2 + Vec2(x * brickWidth, y * brickHeight),
					brickWidth, brickHeight), c));

				bricks[i].indestructible = true;
				
				i++;
			}

		}
		bricks2.clear();
		bricks2.reserve(BrickTotal_lvl5_1);
		{
			const Vec2 topleft = { GridStartX + (brickWidth * 7), GridStartY + (brickHeight * 3) };
			Color colors[BrickViisto_lvl5_1] = { Colors::Blue, Colors::Blue, Colors::Gray, Colors::Red, Colors::Red };
			for (int y = 0; y < BrickPysty_lvl5_1; y++)
			{
				for (int x = 0; x < BrickViisto_lvl5_1; x++)
				{
					Color c = colors[x];
					bricks2.emplace_back( Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
				}
			}
		}
	}
	if (level == Level::Lvl6)
	{
		bricks.clear();
		bricks.reserve(BrickTotal_lvl6);
		const Vec2 topleft = { GridStartX + (brickWidth * 2), GridStartY + (brickHeight * 5) };
		Color colors[BrickPysty_lvl6] = { Colors::Cyan, Colors::Cyan, Colors::White, Colors::Blue, Colors::Red,
			Colors::Yellow, Colors::Gray, Colors::Yellow };
		for (int y = 0; y < BrickPysty_lvl6; y++)
		{
			Color c = colors[y];
			for (int x = 0; x < BrickViisto_lvl6; x++)
			{
				if (x == 4)
				{
					c = Colors::Black;
				}
				else
				{
					c = colors[y];
				}
				bricks.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
					brickWidth, brickHeight), c));
			}
		}
	}
	if (level == Level::Lvl7)
	{
		bricks.clear();
		bricks.reserve(BrickTotal_lvl7);
		{
			const Vec2 topleft = { GridStartX + (brickWidth * 2), GridStartY };
			Color c;
			for (int y = 0; y < BrickPysty_lvl7; y++)
			{
				for (int x = 0; x < BrickViisto_lvl7; ++x)
				{
					if (y == 0 && x <= 4)
					{
						c = Colors::Blue;
					}
					else if (y == 0 && x >= 5)
					{
						c = Colors::Red;
					}
					else if (y == 1)
					{
						c = Colors::Gray;
					}
					bricks.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
				}
			}
		}
		bricks2.clear();
		bricks2.reserve(BrickTotal_lvl7_1);
		{
			const Vec2 topleft = { GridStartX + (brickWidth * 2), GridStartY + (brickHeight * 3) };
			Color c = Colors::Orange;

			for (int y = 0; y < BrickPysty_lvl7_1; y++)
			{
				for (int x = 0; x < BrickViisto_lvl7_1; x++)
				{
					int i = y * BrickViisto_lvl7_1 + x;
					if (y == 3 && x == 3)
					{
						c = Colors::Scarlet;
					}
					else if (y == 3 && x == 7)
					{
						c = Colors::MidnightBlue;
					}
					else
					{
						c = Colors::Orange;
					}

					bricks2.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
					if (y == 3 && x == 3)
					{
						
					}
					else if (y == 3 && x == 7)
					{
						
					}
					else if (y == 0 && (x == 0 || x == 2 || x == 4 || x == 6 || x == 8))
					{
						
						bricks2[i].indestructible = true;
					}
					else if (y == 3 && (x == 1 || x == 5 || x == 9))
					{
						
						bricks2[i].indestructible = true;
					}

					else if (y == 6 && (x == 0 || x == 2 || x == 4 || x == 6 || x == 8))
					{
						
						bricks2[i].indestructible = true;
					}
					else if (y == 9 && (x == 1 || x == 3 || x == 7 || x == 9))
					{
						
						bricks2[i].indestructible = true;
					}
					else
					{
						bricks2[i].SetDestr();
					}


				}
			}
		}
	}
	if (level == Level::Lvl8)
	{
		bricks.clear();
		bricks.reserve(BrickTotal_lvl8);
		{
			const Vec2 topleft = { GridStartX + (brickWidth * 1), GridStartY + (brickHeight * 2) };
			Color c;
			for (int y = 0; y < BrickPysty_lvl8; y++)
			{
				for (int x = 0; x < BrickViisto_lvl8; x++)
				{
					int i = y * BrickViisto_lvl8 + x;
					if (y <= 2 && (x == 0 || x == 2 || x == 9 || x == 11))
					{
						c = Colors::Orange;
					}
					else if (y == 3 && (x <= 2 || x >= 9))
					{
						c = Colors::Orange;
					}
					else if (y == 2 && x == 1)
					{
						c = Colors::Purple;
					}
					else if (y == 2 && x == 10)
					{
						c = Colors::Magenta;
					}
					else if ((y == 6 || y == 7 || y == 8) && (x == 5 || x == 7))
					{
						c = Colors::Orange;
					}
					else if (y == 9 && (x == 5 || x == 6 || x == 7))
					{
						c = Colors::Orange;
					}
					else if (y == 8 && x == 6)
					{
						c = Colors::Scarlet;
					}
					else
					{
						c = Colors::Black;
					}
					bricks.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
				}
			}
		}
		bricks2.clear();
		bricks2.reserve(BrickTotal_lvl8_1);
		{
			const Vec2 topleft = { GridStartX + (brickWidth * 2), GridStartY + (brickHeight * 6) };
			Color c = Colors::Gray;
			for (int y = 0; y < BrickPysty_lvl8_1; y++)
			{
				for (int x = 0; x < BrickViisto_lvl8_1; x++)
				{
					if (y == 0 || x == 0 || x == 9)
					{
						c = Colors::Gray;
					}
					else
					{
						c = Colors::Black;
					}
					bricks2.emplace_back(Brick(RectF(topleft + Vec2(x * brickWidth, y * brickHeight),
						brickWidth, brickHeight), c));
				}
			}
		}
	}
}



