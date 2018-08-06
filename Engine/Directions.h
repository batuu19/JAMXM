#pragma once
#include<string>
#include<cctype>
#include<algorithm>

static constexpr int UP = 0;	
static constexpr int UP_RIGHT = 1;
static constexpr int RIGHT = 2;
static constexpr int DOWN_RIGHT = 3;
static constexpr int DOWN = 4;
static constexpr int DOWN_LEFT = 5;
static constexpr int LEFT = 6;
static constexpr int UP_LEFT = 7;
static constexpr int DIRECTIONS_COUNT= 8;

bool isSimpleDirection(int direction);
int getDirection(std::string name);