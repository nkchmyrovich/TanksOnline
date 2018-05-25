#pragma once 
#include "Entity.h"
#include "map.h"

using namespace sf;

class Bullet : public Entity
{
	enum BULLET_PROPERTIES { 
		SPEED = 10,
		LENGTH = 10,
		WIDTH = 4
	};
	Vector2f direction;
	
public:
	Bullet (Image &image, float X, float Y, float moveTimer);
	~Bullet();

	void update (float time, map& mapa);
	void interactionWithMap(map& mapa);
	void setDirection (Vector2f& direction);
	void activate ();
	bool isActive ();
	void setTimer (float time_);
	void setPosition (float x, float y);


};


