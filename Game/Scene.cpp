#include "Scene.h"

Scene::Scene(const RectI& screenRect)
	:
	screenRect(screenRect)
{

}

Scene::~Scene()
{
	for (auto d : dynamics)
		delete d;
	for (auto s : statics)
		delete s;
	dynamics.clear();
	statics.clear();
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
