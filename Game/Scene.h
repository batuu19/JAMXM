#pragma once

#include "BMath.h"
#include "Rect.h"
#include "Graphics.h"
#include "Keyboard.h"
#include "Entity.h"


class Scene
{
public:
	Scene(const RectI& screenRect);
	Scene(Scene&) = delete;
	Scene& operator=(const Scene&) = delete;
	virtual ~Scene();
	virtual void update(float dt);
	virtual void draw(Graphics&, const VecF2& cameraPos) const;
	virtual void handleInput(Keyboard::Event) = 0;
protected:
	std::vector<DynamicEntity*> dynamics;
	std::vector<StaticEntity*>  statics;
	RectI screenRect;
};