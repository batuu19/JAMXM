#pragma once
#include "Car.h"
#include "BUtils.h"
#include "Rect.h"
#include "Font.h"
#include "Entity.h"

#include<memory>

class Player : 
	public DynamicEntity, 
	public StaticEntity,
	public PlayableEntity
{
public:
	friend class UI;
public:
	Player(std::shared_ptr<Car>);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	~Player();
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
	void reset();
	void scorePoints(int amount = 1);
	void handleInput(Keyboard::Event) override;
	const Car& getCarConst() const;

private:
	std::shared_ptr<Car> car;
	bool shooting = false;
	Car::Speedup speedup = Car::Speedup::None;
	Car::TurnDirection turning = Car::TurnDirection::None;
	int score = 0;


};

class UI : public DynamicEntity, public StaticEntity
{
public:
	UI(Player&);
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
private:
	Surface background = "Sprites\\interface\\interface_background.bmp";
	Player& player;
	const VecI2 pos = { 0,0 };
	float HPPercentage = 1.f;
	const int HPbarLength = 170;
	VecI2 HPRectPos = VecI2(18, 14);
	Color HPcolor = Colors::Red;
};
