#pragma once
#include "Graphics.h"
#include "SpriteContainer.h"
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
	virtual void draw(Graphics&) const;
	virtual void update(float dt);
	void handleInput(Mouse::Event m);
	std::string getActiveButtonAction();
protected:
	class Button
	{
	public:
		friend class Menu;
	public:
		Button(const VecI2& butPos,const SpriteContainer&, std::string text = "");
		void draw(Graphics&) const;
		RectI getRect() const;
	private:
		VecI2 butPos;
		SpriteContainer sprites;
		std::string text;
		enum class State
		{
			Default,
			Active,
			Pressed
		};
		State buttonState = State::Default;

	};

protected:
	std::vector<Button> buttons;
	RectI backgroundRect = {0,400,0,700};
	VecI2 pos;
	int buttonCount;

	std::string action;
};

class MainMenu : public Menu
{
public:
	MainMenu(const RectI& screenRect,const std::initializer_list<std::string>& buttonNames);
	void draw(Graphics&) const override;
private:
	Surface background = "sprites\\menu\\background.bmp";
};