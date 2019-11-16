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
	Player(std::shared_ptr<Car>);
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
	void reset();
	void scorePoints(int amount = 1);
	void handleInput(Keyboard::Event) override;
	const Car& getCarConst() const;

private:
	std::shared_ptr<Car> car;//make unique_ptr?
	bool shooting = false;
	Car::Speedup speedup = Car::Speedup::None;
	Car::TurnDirection turning = Car::TurnDirection::None;
	int score = 0;


};
