#include "Rocket.h"

Rocket::Rocket(Config & config, int x, int y, int dir)
	:
	pos(x, y),
	dir(dir),
	sprites(config.getRocketImageFileName(),5,1,35,35)
{

}

void Rocket::draw(Graphics &) const
{
}

void Rocket::update()
{
}
