#pragma once

#include "Entity.h"
#include "Player.h"

class UI : public DynamicEntity, public StaticEntity
{
public:
	UI(std::shared_ptr<Player> player);
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
private:
	Surface background = "Sprites\\interface\\interface_background.bmp";
	std::shared_ptr<Player> player;
	const VecI2 pos = { 0,0 };
	float HPPercentage = 1.f;
	const int HPbarLength = 170;
	VecI2 HPRectPos = VecI2(18, 14);
	Color HPcolor = Colors::Red;
};