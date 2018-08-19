#pragma once
#include<string>
#include<cctype>
#include<algorithm>
#include<vector>
#include "Vec2.h"

static constexpr int UP = 0;
//1
static constexpr int UP_RIGHT = 2;
//3
static constexpr int RIGHT = 4;
//5
static constexpr int DOWN_RIGHT = 6;
//7
static constexpr int DOWN = 8;
//9
static constexpr int DOWN_LEFT = 10;
//11
static constexpr int LEFT = 12;
//13
static constexpr int UP_LEFT = 14;
//15
static constexpr int DIRECTIONS_COUNT= 16;

int getDirection(std::string name);

//has to be normalized
std::vector<Vec2> directionVec =
{
	{ 0.0f,-1.0f },//up
	{ 1.0f,-2.0f },
	{ 1.0f,-1.0f },//up_right
	{ 2.0f,-1.0f },
	{ 2.0f,0.0f },//right
	{ 2.0f,1.0f },
	{ 1.0f,1.0f },//down_right
	{ 1.0f,2.0f },
	{ 0.0f,2.0f },//down
	{ -1.0f,2.0f },
	{ -1.0f,1.0f },//down_left
	{ -2.0f,1.0f },
	{ -2.0f,0.0f },//left
	{ -2.0f,-1.0f },
	{ -1.0f,-1.0f },//up_left
	{ -1.0f,-2.0f },
};

void normalizeDirectionVectors();