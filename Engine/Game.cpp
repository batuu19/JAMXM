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
			VecF2((float)config.carStartXPos, (float)config.carStartYPos),
			config.carStartVelocity,
			config.carSpeed,
			config.carMaxVelocity,
			config.carStartDir,
			config.carTurnRate,
			config.rocketVelocity,
			config.rocketImageFileName,
			35, 35,
			config.carImageFileName,
			70, 70
		)),
	wreck(VecF2(650.f, 300.f), "sprites\\wreck.bmp", 80, 140, 1, 1)
{
	Debug::clear();
	if(musicPlay)sndMusic.Play();
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
	if (!pause)
	{
		auto& rContainer = player.car.getRocketContainer();
		std::vector<int> rocketsToRemove;
		auto pred = [this](Rocket r) {return r.getRect().IsOverlappingWith(wreck.getRect()); };


		for (int i = 0; i < rContainer.size(); i++)
		{
			if (pred(rContainer[i]))
			{
				sndBoom.Play();
				rocketsToRemove.push_back(i);
			}
		}

		for (int i : rocketsToRemove)
		{
			rContainer.erase(rContainer.begin() + i);
		}

		player.update(wnd.kbd);
		wreck.update();

	}
	//TODO: prevent from keeping pressed
	if (wnd.kbd.KeyIsPressed(VK_SPACE))pause = !pause;

	if (wnd.kbd.KeyIsPressed('M'))
	{
		if (muted)
			SoundSystem::SetMasterVolume(1.0f);
		else
			SoundSystem::SetMasterVolume(0.0f);
		muted = !muted;
	}
	if (wnd.kbd.KeyIsPressed('P'))
	{
		if (musicPlay)
			sndMusic.StopAll();
		else
			sndMusic.Play();
		musicPlay = !musicPlay;
	}
}

void Game::ComposeFrame()
{
	map.draw();
	wreck.draw(gfx);
	player.draw(gfx);
}
