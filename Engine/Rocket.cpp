#include "Rocket.h"

Rocket::Rocket(const Config & config, int x, int y, int dir)
	:
	pos(x, y),
	dir(dir),
	sprites(config.getRocketImageFileName(),5,1,35,35),
	vel(vectorsNormalized[dir] * config.getRocketVelocity())
{
}

Rocket::Rocket(const Config & config, Vec2 pos, int dir)
	:
	pos(pos),
	dir(dir),
	sprites(config.getRocketImageFileName(), 5, 1, 35, 35),
	vel(vectorsNormalized[dir] * config.getRocketVelocity())

{
}

void Rocket::draw(Graphics & gfx) const
{
	gfx.drawSprite((Vei2)pos, sprites[dir]);
}

void Rocket::update()
{
	pos += vel;
}
