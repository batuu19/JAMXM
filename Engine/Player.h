#pragma once
#include "Car.h"
#include "BUtils.h"
#include "Rect.h"

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
	void handleInput(Keyboard&, Mouse&);
	const Car& getCarConst() const;

private:
	Car* car;
	bool shooting = false;
	Car::Speedup speedup = Car::Speedup::None;
};

class UI
{
public:
	UI(Player&);
	void update(float dt);
	void draw(Graphics&,VecF2 cameraPos) const;
private:
	Player& player;
	const VecI2 pos = { 0.f,0.f };
	float HPPercentage = 1.f;
	RectI HPRect = RectI({ 0,0 },200,30);
	Color HPcolor = Colors::Red;
};
