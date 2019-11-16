#pragma once

#include "CarController.h"
#include "Font.h"

class UI : public DynamicEntity, public StaticEntity
{
public:
	UI(std::shared_ptr<CarController> carController);
	void update(float dt) override;
	void draw(Graphics&, const VecF2& cameraPos) const override;
private:
	Surface background = "Sprites\\interface\\interface_background.bmp";
	std::shared_ptr<CarController> carController;
	const VecI2 pos = { 0,0 };
	const int HPbarLength = 170;
	VecI2 HPRectPos = VecI2(18, 14);
	Color HPcolor = Colors::Red;
};