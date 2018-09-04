#pragma once
#include "Graphics.h"
#include "Surface.h"
#include <vector>
class Menu
{
public:
	Menu();
	void draw(Graphics&) const;
private:
	class Button
	{
	public:
		friend class Menu;
	public:
		Button(const VecI2& butPos,const Surface&, std::string text = "");
		void draw(Graphics&) const;
	private:
		VecI2 butPos;
		Surface background;
		std::string text;
	};

private:
	VecI2 pos = { 100,100 };
	std::vector<Button> buttons;
	Surface background = "sprites\\menu\\submenuBackground.bmp";
};

class MainMenu : public Menu
{
public:
	void draw(Graphics&) const;
private:
	Surface background = "sprites\\menu\\background.bmp";
};