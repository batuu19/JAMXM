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
#include "MainWindow.h"
#include "Game.h"

Game::Game(MainWindow& wnd)
	:
	wnd(wnd),
	gfx(wnd),
	config("config.txt"),
	map(config, gfx),
	player(
		Car(
	VecF2((float)config.carStartXPos,(float)config.carStartYPos ),
	config.carStartVelocity,
	config.carSpeed,
	config.carMaxVelocity,
	config.carStartDir,
	config.carTurnRate,
	config.rocketVelocity,
	config.rocketImageFileName,
	35,35,
	config.carImageFileName,
	70,70
		))
{
	Debug::clear();
	sndMusic.Play();
}

void Game::Go()
{
	gfx.BeginFrame();	
	UpdateModel();
	ComposeFrame();
	gfx.EndFrame();
}

void Game::UpdateModel()
{

	player.update(wnd.kbd);
	//do sprawdzania wymiar�w
	//int x, y;

	//if (wnd.mouse.LeftIsPressed())
	//{
	//	if(!pressed)
	//	{
	//		x = wnd.mouse.GetPosX();
	//		y = wnd.mouse.GetPosY();

	//		std::stringstream ss;
	//		ss << "Mouse at " << x << " " << y;
	//		Debug::writeInfo(ss.str());

	//		pressed = true;
	//	}
	//	
	//}
	//else 
	//	pressed = false;
}

void Game::ComposeFrame()
{
	map.draw();
	player.draw(gfx);
}
