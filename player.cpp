#include "player.h"
#include <SFML/Graphics.hpp>
#include <iostream>

#define LeftPressed (Keyboard::isKeyPressed(Keyboard::Left))
#define RightPressed (Keyboard::isKeyPressed(Keyboard::Right))
#define UpPressed (Keyboard::isKeyPressed(Keyboard::Up))
#define DownPressed (Keyboard::isKeyPressed(Keyboard::Down))

using namespace sf;

Player::Player () :
	Entity(),
	spriteAngle (0),
	cannon()
{} 

Player::Player(Image &bodyImage, Image &cannonImage, float X, float Y,int W,int H, String PlayerName, String CannonName) :
	Entity(bodyImage, X, Y, W, H, PlayerName),
	spriteAngle (0),
	cannon(bodyImage, X, Y, 0, 0, CannonName)
{
	if (PlayerName == "Player1")
	{
	sprite.setTextureRect(IntRect(0,0,w,h));
	}

	isCannon = true;
	state = stay;
}

void Player::control()
{
	if(LeftPressed) //left
	{ 
		speed = 0.1;
		spriteAngle = 90.0f;
		sprite.setRotation(spriteAngle);		
		state = left; 
	}
	if(RightPressed) //right
	{
		speed = 0.1; 
		spriteAngle = -90.0f;
		sprite.setRotation(spriteAngle);	
		state = right; 
	}
	if(UpPressed) //up
	{
		speed = 0.1; 
		spriteAngle = 180.0f;
		sprite.setRotation(spriteAngle);		
		state = up; 
	}
	if(DownPressed) //down
	{
		speed = 0.1;
		spriteAngle = 0.0f; 
		sprite.setRotation(spriteAngle);	
		state = down; 
	}
	if(LeftPressed && UpPressed) //left-up
	{
		speed = 0.1; 
		spriteAngle = 135.0f;
		sprite.setRotation(spriteAngle);		
		state = leftUp; 
	}
	if(RightPressed && UpPressed) //right-up
	{
		speed = 0.1; 
		spriteAngle = -135.0f;
		sprite.setRotation(spriteAngle);	
		state = rightUp; 
	}
	if(LeftPressed && DownPressed) //left-down
	{
		speed = 0.1; 
		spriteAngle = 45.0f;
		sprite.setRotation(spriteAngle);		
		state = leftDown; 
	}
	if(RightPressed && DownPressed) //right-down
	{
		speed = 0.1;
		spriteAngle = -45.0f; 
		sprite.setRotation(spriteAngle);	
		state = rightDown; 
	}
}

void Player::interactionWithMap(map& mapa)//ф-ция взаимодействия с картой
{
 
	for (int i = y / 32; i < (y + h) / 32; i++)
	for (int j = x / 32; j<(x + w) / 32; j++)
	{
		if (mapa.get_ij(i, j) == '0')
		{
		   switch (state)
		   {
		   case right:
                   x = j * 32 - w; break;
		   case left:
                   x = j * 32 + 32; break;
		   case up:
                   y = i * 32 + 32; break;
		   case down:
                   y = i * 32 - h; break;
		   case leftUp:
                   dx = -speed / 1.4; dy = -speed / 1.4; break;
		   case leftDown:
                   dx = -speed / 1.4; dy = speed / 1.4; break;
		   case rightUp:
                   dx = speed / 1.4; dy = -speed / 1.4; break;
		   case rightDown:
                   dx = speed / 1.4; dy = speed / 1.4; break;
		   case stay:
                   break;
		   }



			/*if (dy > 0)
			{
				if (dx > 0)
				{
					x = j * 32 - w / 1.4;
					y = i * 32 - h / 1.4;
				}
								
				if (dx < 0)
				{	y = i * 32 - h;
					x = j * 32 + 32;
				}

				
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
			if ( (dy < 0) && (dx < 0) )
			{
				y = i * 32 + 32;
			}
			if ( (dy > 0) && (dx < 0) )
			{
				x = j * 32 - w;
			}
			if ( (dy < 0) && (dx > 0) )
			{
				x = j * 32 + 32;
			} */
		}
 
		if (mapa.get_ij(i, j) == 's') 
		{ 
			x = 300; y = 300;
			mapa.change_ij(i, j, ' ');
		}
	}
} 	

void Player::draw(RenderWindow& window)
{
	if(!isCannon)
		Entity::draw(window);
	else
	{
		window.draw(sprite);
		cannon.draw(window);
	}
}

void Player::update(float time, map& mapa, RenderWindow& window)
	   {
		    control();//функция управления персонажем
		    switch (state)//тут делаются различные действия в зависимости от состояния
		    {
		    case right:
		    	dx = speed; 
		    	dy = 0; 
		    	break;
		    case left:
		    	dx = -speed; 
		    	dy = 0; 
		    	break;
		    case up:
		    	dx = 0; 
		    	dy = -speed; 
		    	break;
		    case down:
		    	dx = 0; 
		    	dy = speed; 
		    	break;
		    case leftUp:
		    	dx = -speed / 1.4; 
		    	dy = -speed / 1.4; 
		    	break;
		    case leftDown:
		    	dx = -speed / 1.4; 
		    	dy = speed / 1.4; 
		    	break;
		    case rightUp:
		    	dx = speed / 1.4; 
		    	dy = -speed / 1.4; 
		    	break;
		    case rightDown:
		    	dx = speed / 1.4; 
		    	dy = speed / 1.4; 
		    	break;
		    case stay: 
		    	break;		
		    }

		    x += dx * time;
		    y += dy * time;
 
		    interactionWithMap(mapa);

		    sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
		    cannon.update(x + w / 2, y + h / 2, isAlive, window);

		    if (health <= 0){ isAlive = false; }

		    if (!isMove){ speed = 0; }

		 //  if (life) { view = get_xy_for_view(); window.setView(view); }
	   }

void Player::update (float time, map& mapa, float xMouse, float yMouse) {
	switch (state)//тут делаются различные действия в зависимости от состояния
		{
		case right:
			dx = speed; 
			dy = 0; 
			break;
		case left:
			dx = -speed; 
			dy = 0; 
			break;
		case up:
			dx = 0; 
			dy = -speed; 
			break;
		case down:
			dx = 0; 
			dy = speed; 
			break;
		case leftUp:
			dx = -speed / 1.4; 
			dy = -speed / 1.4; 
			break;
		case leftDown:
			dx = -speed / 1.4; 
			dy = speed / 1.4; 
			break;
		case rightUp:
			dx = speed / 1.4; 
			dy = -speed / 1.4; 
			break;
		case rightDown:
			dx = speed / 1.4; 
			dy = speed / 1.4; 
			break;
		case stay: 
			break;		
		}

	x += dx * time;
	y += dy * time;
 
	interactionWithMap(mapa);

	sprite.setPosition(x + w / 2, y + h / 2); //задаем позицию спрайта в место его центра
	cannon.update(x + w / 2, y + h / 2, xMouse, yMouse);

	if (!isMove){ speed = 0; }
} 


float Player::getSpriteAngle () {
	return spriteAngle;
}

Cannon& Player::getCannon () {
	return cannon;
}

void Player::setSpriteAngle (float angle) {
	spriteAngle = angle;
	sprite.setRotation(spriteAngle);
}
void Player::setCannonAngle (float angle) {
	cannon.setSpriteAngle(angle);
}

void Player::setX (float x_) {
	x = x_;
	sprite.setPosition(Vector2f(x, y));
	cannon.setX(x);
}


void Player::setY (float y_) {
	y = y_;
	sprite.setPosition(Vector2f(x, y));
	cannon.setY(y);
}

void Player::setSpeed (float speed_) {
	speed = speed_;
}

void Player::setState (int state_) {
	state = state_;
}













