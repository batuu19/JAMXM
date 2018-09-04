#pragma once
#include "Graphics.h"
#include "Surface.h"
#include "Rect.h"
#include "Font.h"
#include <vector>
#include <initializer_list>
#include "Mouse.h"
#include "MainWindow.h"

class Menu
{
public:
	Menu(const RectI& screenRect,const std::initializer_list<std::string>& buttonNames);
	Menu(const Menu&) = delete;
	Menu& operator=(const Menu&) = delete;
	void draw(Graphics&) const;
	void handleInput(Mouse::Event m);
	std::string getActiveButtonAction();
protected:
	class Button
	{
	public:
		friend class Menu;
	public:
		Button(const VecI2& butPos,const Surface&, std::string text = "");
		void draw(Graphics&) const;
		RectI getRect() const;
	private:
		VecI2 butPos;
		Surface background;
		std::string text;
	};

protected:
	std::vector<Button> buttons;
	Surface background = "sprites\\menu\\submenuBackground.bmp";
	VecI2 pos;
	int buttonCount;

	std::string action;
};

class MainMenu : public Menu
{
public:
	MainMenu(const RectI& screenRect,const std::initializer_list<std::string>& buttonNames);
	void update(float dt);
	void draw(Graphics&) const;
private:
	Surface background = "sprites\\menu\\background.bmp";
};