#include "Menu.h"

Menu::Menu()
{
	buttons.emplace_back(VecI2(350, 350), Surface("sprites\\menu\\buttonBackground.bmp"));
}

void Menu::draw(Graphics & gfx) const
{
	gfx.drawSprite(pos, background);
	for (auto b : buttons)b.draw(gfx);
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
}

void MainMenu::draw(Graphics & gfx) const
{
	gfx.drawSprite({ 0, 0 }, background);
	Menu::draw(gfx);
}
