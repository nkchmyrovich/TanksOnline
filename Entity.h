#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Entity 
{
protected:
	enum BASIC_PROPERTIES { START_HEALTH = 100};
	Vector2f position;
	float dx, dy, x, y, speed, moveTimer;//добавили переменную таймер для будущих целей
	int w,h,health;
	bool isAlive, isMove;
	Texture texture;
	Sprite sprite;
	String name;//враги могут быть разные, мы не будем делать другой класс для врага.всего лишь различим врагов по имени и дадим каждому свое действие в update в зависимости от имени


public:
	Entity ();
	Entity(Image &image, float X, float Y,int W,int H,String Name);

	void draw(RenderWindow& window);

	float get_x();
	float get_y();

	void change_x(float xnew);
	void change_y(float ynew);

	float get_dx();
	float get_dy(); 

	float get_h();
	float get_w();

	void set_x (float x_);
	void set_y (float y_);

	Sprite& getSprite ();

	void setMoveTimer (float time);

};
