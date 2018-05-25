#include <SFML/Graphics.hpp>
#include "Entity.h"
#include <iostream>

using namespace sf;

Entity::Entity () 
{}

Entity::Entity(Image &image, float X, float Y, int W, int H, String Name) :
	x (X),
	y (Y),
	speed (0),
	moveTimer (0),
	w (W),
	h (H),
	health (START_HEALTH),
	isAlive (true),
	isMove (false),
	name (Name)
{
		texture.loadFromImage(image);
		sprite.setTexture(texture);
		sprite.setOrigin(w / 2, h / 2);
}

void Entity::draw(RenderWindow& window)
{
	window.draw(sprite);
}

float Entity::get_x()
{
	return x;
}

float Entity::get_y()
{
	return y;
}

void Entity::change_x(float xnew)
{
	x = xnew;
}

void Entity::change_y(float ynew)
{
	y = ynew;
}
	
float Entity::get_dx()
{
	return dx;
}

float Entity::get_dy()
{
	return dy;
} 

float Entity::get_h()
{
	return h;
}

float Entity::get_w()
{
	return w;
} 

void Entity::set_x (float x_) {
	x = x_;
}

void Entity::set_y (float y_) {
	y = y_;
}

Sprite& Entity::getSprite () {
	return sprite;
}

void Entity::setMoveTimer (float time) {
	moveTimer = time;
}
