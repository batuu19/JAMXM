#include "Scene.h"

Scene::Scene(const RectI& screenRect)
	:
	screenRect(screenRect)
{}

void Scene::update(float dt)
{
	auto it = std::remove_if(dynamics.begin(), dynamics.end(), [&dt](std::weak_ptr<DynamicEntity> ptr)
		{
			if (auto d = ptr.lock())
			{
				d->update(dt);
				return false;
			}
			else return true;
		});
	dynamics.erase(it, dynamics.end());

}

void Scene::draw(Graphics& gfx, const VecF2& cameraPos)
{
	auto it = std::remove_if(statics.begin(), statics.end(), [&gfx,&cameraPos](std::weak_ptr<StaticEntity> ptr)
		{
			if (auto s = ptr.lock())
			{
				s->draw(gfx, cameraPos);
				return false;
			}
			else return true;
		});
	statics.erase(it, statics.end());
}

void Scene::handleInput(Keyboard::Event e)
{
	auto it = std::remove_if(playables.begin(), playables.end(), [&e](std::weak_ptr<PlayableEntity> ptr)
		{
			if (auto p = ptr.lock())
			{
				p->handleInput(e);
				return false;
			}
			else return true;
		});
	playables.erase(it, playables.end());
}

void Scene::addDynamic(std::shared_ptr<DynamicEntity> ptr)
{
	dynamics.push_back(ptr);
}

void Scene::addStatic(std::shared_ptr<StaticEntity> ptr)
{
	statics.push_back(ptr);
}

void Scene::addPlayable(std::shared_ptr<PlayableEntity> ptr)
{
	playables.push_back(ptr);
}
