#pragma once
#include "BMath.h"
#include "Player.h"
#include "Entity.h"
#include "Map.h"
#include "Animation.h"
#include "BUtils.h"
#include "ContainerUtils.h"
#include "PhysicsUtils.h"
#include "Camera.h"
#include "UFO.h"
#include <exception>
#include "Font.h"
class World
{
public:
	World(const RectI& screenRect);
	World(const World&) = delete;
	World& operator=(const World&) = delete;
	~World();
	void handleInput(Keyboard::Event);
	void update(float dt);
	void draw(Graphics&) const;
	void reset();
	const Map& getMapConst() const;
	const Player& getPlayerConst() const;
private:
	Map* map = new Map(0);
	RectI screenRect;
	RectI mapRect;
	mutable std::mt19937 rng = std::mt19937(std::random_device{}());
	mutable std::uniform_int_distribution<int> xDist, yDist;
	Camera camera;
	std::vector<Rocket*> rockets;
	std::vector<Animation> animations;
	Car* car = new Car(VecF2(216.f, 867.f), RIGHT, rockets,animations);
	Player player;
	std::vector<UFO*> ufos;
	UI ui;
	bool musicPlaying = true;
	Font font;

	bool newUfoNeeded = false;
	bool carDead = false;

	//sounds
	Sound sndBoom = Sound(L"sound\\game\\explosion.wav");
	Sound bgm = Sound(L"sound\\music\\music.wav", Sound::LoopType::AutoFullSound);
	//SoundEffect sndRaceStart = SoundEffect({
	//	L"sound\\speech\\larry\\go_go_go.wav",
	//	L"sound\\speech\\larry\\let_the_carnage_begin.wav",
	//	L"sound\\speech\\larry\\lets_ride.wav"
	//});
	SoundEffect sndAfterBoom = SoundEffect({
		L"sound\\speech\\larry\\holy_transmission.wav",
		L"sound\\speech\\larry\\smashed.wav",
		L"sound\\speech\\larry\\terrific.wav",
		L"sound\\speech\\larry\\what_a_blow.wav",
		L"sound\\speech\\larry\\wipeout.wav"
	});

	Sound sndAboutBlow = Sound(L"sound\\speech\\larry\\p1_is_about_to_blow.wav");
	bool aboutBlow = false;


	bool carOnRoad = false;
};