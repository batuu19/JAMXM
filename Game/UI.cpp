#include "UI.h"

UI::UI(std::shared_ptr<Player> player)
{
}

void UI::update(float dt)
{
	//HPPercentage = player.car->HP / player.car->maxHP;
}

void UI::draw(Graphics& gfx, const VecF2& cameraPos) const
{
	//gfx.drawSprite(pos, background);
	//gfx.drawRect(RectI(HPRectPos, (int)(HPbarLength * HPPercentage), 10), HPcolor);
	//Font::write(gfx, VecI2{ 165,50 }, std::to_string(player.score), 0, false);
}
