#pragma once
#include "Car.h"
#include "BUtils.h"
#include "Rect.h"
#include "Font.h"

class Player
{
public:
	friend class UI;
public:
	Player(Car*);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	~Player();
	void update(float dt);
	void draw(Graphics&, const VecF2& cameraPos) const;
	void reset();
	void scorePoint();
	void handleInput(Keyboard::Event);
	const Car& getCarConst() const;

private:
	Car* car;
	bool shooting = false;
	Car::Speedup speedup = Car::Speedup::None;
	Car::TurnDirection turning = Car::TurnDirection::None;
	int score = 0;
};

class UI
{
public:
	UI(Player&);
	void update(float dt);
	void draw(Graphics&,VecF2 cameraPos) const;
private:
	Surface background = "Sprites\\interface\\interface_background.bmp";
	Player& player;
	const VecI2 pos = { 0.f,0.f };
	float HPPercentage = 1.f;
	RectI HPRect = RectI({ 18,14 },80,10);
	Color HPcolor = Colors::Red;
};
