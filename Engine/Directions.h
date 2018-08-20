#pragma once
#include<string>
#include<cctype>
#include<algorithm>
#include<vector>
#include "BMath.h"

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

const std::vector<Vec2> directionVec =
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

const std::vector<Vec2> vectorsNormalized =
{
	{directionVec[0].getNormalized() },
	{directionVec[1].getNormalized() },
	{directionVec[2].getNormalized() },
	{directionVec[3].getNormalized() },
	{directionVec[4].getNormalized() },
	{directionVec[5].getNormalized() },
	{directionVec[6].getNormalized() },
	{directionVec[7].getNormalized() },
	{directionVec[8].getNormalized() },
	{directionVec[9].getNormalized() },
	{directionVec[10].getNormalized()},
	{directionVec[11].getNormalized()},
	{directionVec[12].getNormalized()},
	{directionVec[13].getNormalized()},
	{directionVec[14].getNormalized()},
	{directionVec[15].getNormalized()}
};