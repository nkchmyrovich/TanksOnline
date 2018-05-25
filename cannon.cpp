#include "cannon.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

using namespace sf;

Cannon::Cannon ()
{}

Cannon::Cannon(Image &image, float X, float Y, int W, int H, String Name) :
	Entity(image, X, Y, 0, 0, Name),
	spriteAngle (0)
{
	FireRate = 1;

	if (Name == "Cannon1")
	{
	w = 34;
	h = 66;
	sprite.setTextureRect(IntRect(66, 5, w,h));
	sprite.setOrigin(w / 2, h * 0.257575758);

	}
}

void Cannon::interactionWithMap(map& mapa)//ф-ция взаимодействия с картой
{
 
	for (int i = y / 32; i < (y + h) / 32; i++)
	for (int j = x / 32; j<(x + w) / 32; j++)
	{
		if (mapa.get_ij(i, j) == '0')
		{
			if (dy > 0)
			{
				y = i * 32 - h;
			}
			if (dy < 0)
			{
				y = i * 32 + 32;
			}
			if (dx > 0)
			{
				x = j * 32 - w;
			}
			if (dx < 0)
			{
				x = j * 32 + 32;
			}
		}
 
		if (mapa.get_ij(i, j) == 's') 
		{ 
			x = 300; y = 300;
			mapa.change_ij(i, j, ' ');
		}
	}
} 

void Cannon::Rotation(RenderWindow& window)
{
	Vector2i pixelPos = Mouse::getPosition(window);
	Vector2f pos = window.mapPixelToCoords(pixelPos);

	float xMouse = pos.x;
	float yMouse = pos.y;

	float rotation = (atan2(yMouse - y, xMouse - x) * 180 / 3.14159265) - 90;

	spriteAngle = rotation;
	sprite.setRotation(rotation);
}

void Cannon::Rotation (float xMouse, float yMouse) {
	float rotation = (atan2(yMouse - y, xMouse - x) * 180 / 3.14159265) - 90;
	spriteAngle = rotation;
	sprite.setRotation(rotation);
}


	

void Cannon::update (float xnew, float ynew, bool isAlive, RenderWindow& window)
{
	if (name == "Cannon1")
	{
		x = xnew;
		y = ynew;

		sprite.setPosition(x, y); //задаем позицию спрайта в место его центра
		Rotation(window);

		if (health <= 0){ isAlive = false; }

		if (!isMove){ speed = 0; }
	}

	
} 

void Cannon::update (float x_, float y_, float xMouse, float yMouse) {
	x = x_;
	y = y_;

	sprite.setPosition(x, y);
	Rotation(xMouse, yMouse);
}


float Cannon::getSpriteAngle () {
	return spriteAngle;
}

void Cannon::setSpriteAngle (float angle) {
	spriteAngle = angle;
	sprite.setRotation (angle);
}

void Cannon::setX (float x_) {
	x = x_;
	sprite.setPosition(Vector2f(x, y));
}
void Cannon::setY (float y_) {
	y = y_;
	sprite.setPosition(Vector2f(x, y));
}

/*void change_FireRate(int frnew)
{
	FireRate = frnew;
}*/

