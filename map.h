#pragma once
#include <SFML/Graphics.hpp> 

using namespace sf;

class map
{
protected:
	String* TileMap; 
		
	String File;//файл с расширением
	Image image;
	Texture texture;
	Sprite look;
public:
	map(String F, String* mapPlan);

	int print(RenderWindow& window);
	String get_ij(int i, int j);
	void change_ij(int i, int j, char s);

	//void interactionWithMainHero(essence& hero);
};






