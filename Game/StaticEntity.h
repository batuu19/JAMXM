#pragma once
#include "Graphics.h"
#include "BMath.h"

class StaticEntity
{
public:
	virtual void draw(Graphics&,const VecF2& cameraPos) const = 0;
	virtual ~StaticEntity() = default;
};