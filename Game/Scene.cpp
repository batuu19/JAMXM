#include "Scene.h"

Scene::Scene(const RectI& screenRect)
	:
	screenRect(screenRect)
{

}

Scene::~Scene()
{
	cleanAndClear(dynamics);
	cleanAndClear(statics);
}

void Scene::update(float dt)
{
	for (auto d : dynamics)
		d->update(dt);
}

void Scene::draw(Graphics&gfx, const VecF2& cameraPos) const
{
	for (auto s : statics)
		s->draw(gfx, cameraPos);
}

void Scene::handleInput(Keyboard::Event e)
{
	for (auto p : playables)
		p->handleInput(e);
}
