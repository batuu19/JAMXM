#pragma once

#include <memory>

#include "BMath.h"
#include "Rect.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Entity.h"
#include "ContainerUtils.h"


class Scene
{
public:
	Scene(const RectI& screenRect);
	Scene(Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	virtual ~Scene() = default;
	virtual void update(float dt);
	virtual void draw(Graphics&, const VecF2& cameraPos = { 0.f,0.f });//not const, changes static entities
	virtual void handleInput(Keyboard::Event);
protected:
	std::vector<std::weak_ptr<DynamicEntity>> dynamics;//update
	std::vector<std::weak_ptr<StaticEntity>>  statics;//draw
	std::vector<std::weak_ptr<PlayableEntity>> playables;//handleInput
	RectI screenRect;
};
