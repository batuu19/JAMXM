#pragma once

#include "BMath.h"
#include "Rect.h"

//TOOD hitbox with polygon
//think about hitbox using points, but unnecesary 
class Hitbox {
public:
	Hitbox(const RectI& rect, VecI2 pos);
	Hitbox(const RectI& rect);

	virtual bool contains(const VecI2& point) const;
	virtual bool contains(const RectI& other) const;
	virtual bool contains(const Hitbox& other) const;
	virtual bool isOverlappingWith(const Hitbox& other) const;
	virtual bool isContainedBy(const RectI& other) const;
	virtual bool isContainedBy(const Hitbox& other) const;

	virtual void updatePos(const VecI2& newPos);

	RectI getFixedRect() const;
private:
	RectI rect;
	VecI2 pos = { 0,0 };//top left
};