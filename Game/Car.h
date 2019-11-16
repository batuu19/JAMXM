#pragma once

#include <string>

class Car
{
public:
	friend class CarController;
public:
private:
	const float maxHP = 300.f;
	const float speed = 600.f;
	const float maxVel = 300.f;
	//make it dependent on velocity
	const float turnRate = 0.1f;
	const int turnValue = 1;//how many directions at once

	const std::wstring sndFrictionSrc = L"sound\\game\\friction.wav";
	const std::wstring sndWeaponChangeSrc = L"sound\\game\\reload.wav";
	const std::wstring sndRocketShotSrc = L"sound\\game\\rocketshot.wav";
	const std::string spriteSrc = "Sprites\\cars\\car_black.bmp";
};
