/****************************************************************************************** 
 *	Chili DirectX Framework Version 16.07.20											  *	
 *	Game.h																				  *
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
#pragma once

#include "Keyboard.h"
#include "Mouse.h"
#include "Graphics.h"
#include "Brick.h"
#include "Ball.h"
#include "FrameTimer.h"
#include "Paddle.h"
#include "Sound.h"
#include "Area.h"
#include <random>
#include "Surface.h"
#include <vector>
#include "Font.h"
#include <string>
#include "Screens.h"

class Game
{
public:
	Game(class MainWindow& wnd);
	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	void Go();

private:
	enum class Level
	{
		Lvl1,
		Lvl2,
		Lvl3,
		Lvl4,
		Lvl5,
		Lvl6,
		Lvl7,
		Lvl8,
		Lvl9,
		Testi,
		TestiV
	};

	enum class GameScreen
	{
		Playing,
		StartMenu,
		Options,
		Info,
		GameOver,
		ChoiceScreen1,
		ChoiceScreen2,
		BrickInfo,
		MeterInfo
	};

private:
	void ComposeFrame();
	void UpdateModel(float dt);

private:
	MainWindow& wnd;
	Graphics gfx;
	Surface gameover = Surface("kuvat//game_over.bmp");
	Surface MenuBackground = Surface("kuvat//sky_background_green_hills.bmp");
	Surface BrickInfo = Surface("kuvat//bricks.bmp");
	Surface MeterInfo = Surface("kuvat//metersInfo.bmp");
	Surface ChoiceScreen1 = Surface("kuvat//ChoiceScreen1.bmp");
	Surface ChoiceScreen2 = Surface("kuvat//ChoiceScreen2.bmp");
	Screen StartMenu = { "Play \nOptions \nInfo \nQuit", MenuBackground, Vei2(100,100) };
	Screen InfoMenu = {"Bricks \nMetters \nBack", MenuBackground, Vei2(100, 100)};

	const bool testmode = false;   //testmode, joka mahdollistaa tasojen nopean testaamisen ilman tarvetta pelata läpi edellisiä tasoja
	
	void DrawBack();
	void BrickCollision(std::vector<Brick>& bricks, Ball& ball, int BrickTotal_lvl1);
	void BrickCollision(std::vector<Brick>& bricks, Ball& ball, Ball& ball2, Ball& ball3, int BrickTotal_lvl1)
	{
		BrickCollision(bricks, ball, BrickTotal_lvl1);
		BrickCollision(bricks, ball2, BrickTotal_lvl1);
		BrickCollision(bricks, ball3, BrickTotal_lvl1);
	}

	void DrawScreen(Surface& s);
	void DrawLevel(const Level level);
	void SetLevel(const Level level);
	void ResetGameSettings();
	
	std::vector<Brick> bricks;
	std::vector<Brick> bricks2;
	
	float dt;
	float elapsedTime;

	static constexpr float brickWidth = 40.0;			//Brickkien arvot ja säädöt
	static constexpr float brickHeight = 18.0f;

	static constexpr int BrickViisto_lvl1 = 8;					//14 max
	static constexpr int BrickPysty_lvl1 = 5;
	static constexpr int BrickTotal_lvl1 = BrickViisto_lvl1 * BrickPysty_lvl1;

	static constexpr int BrickViisto_lvl2 = 10;
	static constexpr int BrickPysty_lvl2 = 6;
	static constexpr int BrickTotal_lvl2 = BrickViisto_lvl2 * BrickPysty_lvl2;

	static constexpr int BrickViisto_lvl3 = 2;
	static constexpr int BrickPysty_lvl3 = 10;
	static constexpr int BrickTotal_lvl3 = BrickViisto_lvl3 * BrickPysty_lvl3;

	static constexpr int BrickViisto_lvl3_1 = 3;
	static constexpr int BrickPysty_lvl3_1 = 5;
	static constexpr int BrickTotal_lvl3_1 = BrickViisto_lvl3_1 * BrickPysty_lvl3_1;

	static constexpr int BrickViisto_lvl4 = 14;
	static constexpr int BrickPysty_lvl4 = 9;
	static constexpr int BrickTotal_lvl4 = BrickViisto_lvl4 * BrickPysty_lvl4;

	static constexpr int BrickViisto_lvl5 = 12;
	static constexpr int BrickPysty_lvl5 = 12;
	static constexpr int BrickTotal_lvl5 = BrickViisto_lvl5 + BrickPysty_lvl5;

	static constexpr int BrickViisto_lvl5_1 = 5;
	static constexpr int BrickPysty_lvl5_1 = 4;
	static constexpr int BrickTotal_lvl5_1 = BrickViisto_lvl5_1 * BrickPysty_lvl5_1;

	static constexpr int BrickViisto_lvl6 = 10;
	static constexpr int BrickPysty_lvl6 = 8;
	static constexpr int BrickTotal_lvl6 = BrickViisto_lvl6 * BrickPysty_lvl6;

	static constexpr int BrickViisto_lvl7 = 10;
	static constexpr int BrickPysty_lvl7 = 2;
	static constexpr int BrickTotal_lvl7 = BrickViisto_lvl7 * BrickPysty_lvl7;

	static constexpr int BrickViisto_lvl7_1 = 12;
	static constexpr int BrickPysty_lvl7_1 = 10;
	static constexpr int BrickTotal_lvl7_1 = BrickViisto_lvl7_1 * BrickPysty_lvl7_1;

	static constexpr int BrickViisto_lvl8 = 12;
	static constexpr int BrickPysty_lvl8 = 10;
	static constexpr int BrickTotal_lvl8 = BrickViisto_lvl8 * BrickPysty_lvl8;

	static constexpr int BrickViisto_lvl8_1 = 10;
	static constexpr int BrickPysty_lvl8_1 = 7;
	static constexpr int BrickTotal_lvl8_1 = BrickViisto_lvl8_1 * BrickPysty_lvl8_1;

	static constexpr int BrickViisto_lvlTesti = 2;
	static constexpr int BrickPysty_lvlTesti = 2;
	static constexpr int BrickTotal_lvlTesti = BrickViisto_lvlTesti * BrickPysty_lvlTesti;

	static constexpr int BrickViisto_lvlTestiV = 3;
	static constexpr int BrickPysty_lvlTestiV = 3;
	static constexpr int BrickTotal_lvlTestiV = BrickViisto_lvlTestiV * BrickPysty_lvlTestiV;

	static constexpr float GridStartX = 120.0f;
	static constexpr float GridStartY = 60.0f;

	FrameTimer ft;											//objektit
	Paddle pad{ Vec2(400.0f, 520.0f), 40.0f, 10.0f };

	Ball ball = { Vec2(pad.GetRect().GetCenter().x, pad.GetRect().GetCenter().y - 20.0f), Vec2(200.0f, 200.0f) };
	Ball ball2;
	Ball ball3;

	Area::Life life;
	Area::Meter meter;

	

	Paddle::Guns gun = { Vec2(pad.GetPos()) };
	Level level = { Level::Lvl1 };
	GameScreen GameScreen = { GameScreen::StartMenu };

	Area leftwall = { RectF(110.0f, GridStartX , GridStartY, gfx.ScreenHeight), Colors::Blue };		//pelialueen säätö
	Area rightwall = { RectF(680.0f, 690.0f, GridStartY, gfx.ScreenHeight), Colors::Blue };
	Area topwall = { RectF(110.0f, 690.0f, 50.0f, GridStartY), Colors::Blue };

	RectF walls = { RectF(leftwall.GetRect().right, rightwall.GetRect().left,
		topwall.GetRect().bottom, float(gfx.ScreenHeight)) };

	bool LvlUp = false;
	bool Ball_1 = true;
	bool Ball_2 = false;
	bool Ball_3 = false;
	
};