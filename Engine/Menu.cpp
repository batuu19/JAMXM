#include "Menu.h"

Menu::Menu(const RectI& screenRect, const std::initializer_list<std::string>& buttonNames)
	:
	pos(screenRect.getCenter() - VecI2(background.getWidth() / 2, background.getHeight() / 2))
{
	buttonCount = buttonNames.size();
	Surface buttonSurf = "sprites\\menu\\buttonBackground.bmp";
	int padding = (background.getHeight() - (buttonCount * buttonSurf.getHeight())) / (buttonCount + 1);
	VecI2 butPos;
	butPos = VecI2{ 
		(background.getWidth() - buttonSurf.getWidth()) / 2,
		padding 
	} +pos;

	for (auto& t:buttonNames)
	{
		buttons.emplace_back(butPos, buttonSurf,t);
		butPos.y += padding + buttonSurf.getHeight();
	}
}

void Menu::draw(Graphics & gfx) const
{
	gfx.drawSprite(pos, background);
	for (auto b : buttons)b.draw(gfx);
}

void Menu::handleInput(Mouse::Event m)
{
	for (auto& b : buttons)
	{
		if (b.getRect().contains(m.GetPos()))
		{
			if(m.LeftIsPressed())action = b.text;
			return;
		}
	}
	action = "";
}

std::string Menu::getActiveButtonAction()
{
	auto tempAction = action;
	action = "";
	return tempAction;
}

Menu::Button::Button(const VecI2 & butPos, const Surface & background, std::string text)
	:
	butPos(butPos),
	background(background),
	text(text)
{
}

void Menu::Button::draw(Graphics & gfx) const
{
	gfx.drawSprite(butPos, background);
	Font::write(gfx, butPos + VecI2(0, background.getHeight() - Font::characterSize),text,-8);
}

RectI Menu::Button::getRect() const
{
	return background.getRect().displaceBy(butPos);
}

MainMenu::MainMenu(const RectI & screenRect, const std::initializer_list<std::string>& buttonNames)
	:
	Menu(screenRect,buttonNames)
{
}

void MainMenu::update(float dt)
{
}

void MainMenu::draw(Graphics & gfx) const
{
	gfx.drawSprite({ 0, 0 }, background);
	Menu::draw(gfx);
}
