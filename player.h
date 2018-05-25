#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "cannon.h"
#include "PlayerProp.hpp"

using namespace sf;

class Player : public Entity
{
protected:
	int state;
	float spriteAngle;
	bool isCannon;

	void control();
	void interactionWithMap(map& mapa);
	Cannon cannon;

public:
	Player ();
	Player(Image &bodyImage, Image &cannonImage, float X, float Y,int W, int H, String PlayerName, String CannonName);

	void draw(RenderWindow& window);
	void update(float time, map& mapa, RenderWindow& window);
	void update (float time, map& mapa, float xMouse, float yMouse);
	Cannon& getCannon ();

	void setSpriteAngle (float angle);
	void setCannonAngle (float angle);
	void setX (float x);
	void setY (float y);
	float getSpriteAngle ();
	void setSpeed (float speed_);
	void setState (int state_);
};
