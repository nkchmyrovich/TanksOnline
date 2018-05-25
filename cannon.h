#pragma once
#include <SFML/Graphics.hpp>
#include "Entity.h"
#include "map.h"

using namespace sf;

class Cannon :public Entity
{
protected:
	int FireRate;
	float spriteAngle;

	void interactionWithMap(map& mapa);
	void Rotation(RenderWindow& window);
	void Rotation(float xMouse, float yMouse);

public:
	Cannon ();
	Cannon(Image &image, float X, float Y,int W,int H,String Name);

	void update(float time, map& mapa);
	void update(float x, float y, bool isAlive, RenderWindow& window);
	void update (float x_, float y_, float xMouse, float yMouse);
	void Shooting();

	float getSpriteAngle ();
	void setSpriteAngle (float angle);
	void setX (float x);
	void setY (float y);
	//void change_FireRate(int frnew);

};
