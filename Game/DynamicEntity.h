#pragma once

class DynamicEntity
{
public:
	virtual void update(float dt) = 0;
	virtual ~DynamicEntity() = default;
};
