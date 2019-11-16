#include "UI.h"

UI::UI(std::shared_ptr<CarController> carController)
	:
	carController(carController)
{
}

void UI::update(float dt)
{
}

void UI::draw(Graphics& gfx, const VecF2& cameraPos) const
{
	gfx.drawSprite(pos, background);
	gfx.drawRect(RectI(HPRectPos, (int)(HPbarLength * carController->getHPPercentage()), 10), HPcolor);
	Font::write(gfx, VecI2{ 165,50 }, std::to_string(carController->getScore()), 0, false);
}
