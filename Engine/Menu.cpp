#include "Menu.h"

Menu::Menu(const RectI& screenRect, const std::initializer_list<std::string>& buttonNames)
	:
	pos(screenRect.getCenter() - VecI2(backgroundRect.getWidth() / 2, backgroundRect.getHeight() / 2))
{
	buttonCount = (int)buttonNames.size();
	SpriteContainer buttonSurf = { {"sprites\\menu\\buttonAnim.bmp"},1,2,false };
	int padding = (backgroundRect.getHeight() - (buttonCount * buttonSurf.getHeight())) / (buttonCount + 1);
	VecI2 butPos;
	butPos = VecI2{ 
		(backgroundRect.getWidth() - buttonSurf.getWidth()) / 2,
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
	for (auto b : buttons)b.draw(gfx);
}

void Menu::update(float dt)
{
	//for (auto& b : buttons)b.buttonState = Button::State::Default;
}

void Menu::handleInput(Mouse::Event m)
{
	for (auto& b : buttons)
	{
		if (b.getRect().contains(m.GetPos()))
		{
			b.buttonState = Button::State::Active;
			if(m.LeftIsPressed())
				action = b.text;
			return;
		}
		else
		{
			b.buttonState = Button::State::Default;
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

Menu::Button::Button(const VecI2 & butPos, const SpriteContainer & sprites, std::string text)
	:
	butPos(butPos),
	sprites(sprites),
	text(text)
{
}

void Menu::Button::draw(Graphics & gfx) const
{
	switch (buttonState)
	{
	case Menu::Button::State::Default:
		gfx.drawSprite(butPos, sprites[0]);
		break;
	case Menu::Button::State::Active:
		gfx.drawSprite(butPos, sprites[1]);
		break;
	//case Menu::Button::State::Pressed:
	//	break;
	default:
		gfx.drawSprite(butPos, sprites[0]);
		break;
	}
	Font::write(gfx, butPos + VecI2(0, sprites.getHeight() - Font::characterSize),text,-8);
}

RectI Menu::Button::getRect() const
{
	return sprites.getRect().displaceBy(butPos);
}

MainMenu::MainMenu(const RectI & screenRect, const std::initializer_list<std::string>& buttonNames)
	:
	Menu(screenRect,buttonNames)
{
}

void MainMenu::draw(Graphics & gfx) const
{
	gfx.drawSprite({ 0, 0 }, background);
	Menu::draw(gfx);
}
