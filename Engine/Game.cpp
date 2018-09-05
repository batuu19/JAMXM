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
	world(gfx.getScreenRect()),
	pauseMenu(gfx.getScreenRect(),{"Resume","Menu","Quit"}),
	menu(gfx.getScreenRect(), {"Play","Quit"})
{
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
	while (!wnd.kbd.KeyIsEmpty())
	{
		const Keyboard::Event k = wnd.kbd.ReadKey();
		handleInput(k);
	}
	while (!wnd.mouse.IsEmpty())
	{
		const Mouse::Event m = wnd.mouse.Read();
		handleInput(m);
	}
	

	const float dt = ft.mark();
	switch (gameState)
	{
	case GameState::MainMenu:
		processAction(menu.getActiveButtonAction());
		menu.update(dt);
		break;
	case GameState::GamePaused:
		processAction(pauseMenu.getActiveButtonAction());
		break;
	case GameState::Game:
		world.update(dt);
		break;
	default:
		break;
	}
}

void Game::ComposeFrame()
{
	switch (gameState)
	{
	case GameState::MainMenu:
		menu.draw(gfx);
		break;
	case GameState::GamePaused:
		world.draw(gfx);
		pauseMenu.draw(gfx);
		break;
	case GameState::Game:
		world.draw(gfx);
		break;
	default:
		break;
	}
}

void Game::handleInput(Keyboard::Event k)
{
	if (k.IsPress())
	{
		switch (k.GetCode())
		{
		case VK_ESCAPE:
			pauseGame();
			break;
		default:
			break;
		}
	}
	if (gameState == GameState::Game)
		world.handleInput(k);
}

void Game::handleInput(Mouse::Event m)
{
	switch (gameState)
	{
	case GameState::MainMenu:
		menu.handleInput(m);
		break;
	case GameState::Game:
		break;
	case GameState::GamePaused:
		pauseMenu.handleInput(m);
		break;
	default:
		break;
	}
	
}

void Game::processAction(std::string action)
{
	if (action == "Play")
		enterGame();
	else if (action == "Resume")
		unpauseGame();
	else if (action == "Menu")
		enterMainMenu();
	else if (action == "Quit")
		exitGame();

}

//needed if here?
bool Game::pauseGame()
{
	if (gameState != GameState::Game)return false;//can go only from Game
	else
	{
		gameState = GameState::GamePaused;
		return true;
	}
}

bool Game::unpauseGame()
{
	if (gameState != GameState::GamePaused)return false;//can go only from GamePaused
	else
	{
		gameState = GameState::Game;
		return true;
	}
}

bool Game::enterGame()
{
	if (gameState != GameState::MainMenu)return false;//can go only from MainMenu
	else
	{
		world.reset();
		gameState = GameState::Game;
		return true;
	}
}

bool Game::enterMainMenu()
{
	if (gameState != GameState::GamePaused)return false;//can go only from GamePaused
	else
	{
		gameState = GameState::MainMenu;
		return true;
	}
}

bool Game::exitGame()
{
	if (gameState != GameState::MainMenu && gameState != GameState::GamePaused)return false;//can go only from MainMenu && GamePaused 
	else
	{
		wnd.Kill();
		return true;//not needed?
	}
}




