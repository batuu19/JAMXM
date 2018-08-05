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

Game::Game( MainWindow& wnd )
	:
	wnd( wnd ),
	gfx( wnd ),
	car(70,70,Colors::Cyan)
{
	//gfx.drawSprite(0, 0, background);
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

	if (wnd.kbd.KeyIsPressed(VK_UP))
	{
		car.speedup();
	}
	else if (wnd.kbd.KeyIsPressed(VK_DOWN))
	{
		
	}
	else if (wnd.kbd.KeyIsPressed(VK_LEFT))
	{
		//delta_loc = { -1,0 };
	}
	else if (wnd.kbd.KeyIsPressed(VK_RIGHT))
	{
		car.turnRight();
	}

	car.update();
}

void Game::ComposeFrame()
{
	gfx.drawSprite(0, 0, background);
	car.draw(gfx);
}
