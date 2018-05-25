#include <SFML/Graphics.hpp>
#include <iostream>
#include "map.h"
const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина 

using namespace sf;

map::map(String F, String* mapPlan)
{
	TileMap = mapPlan;

	File = F;

	image.loadFromFile("images/" + File);//загружаем файл для карты
	texture.loadFromImage(image);//заряжаем текстуру картинкой
	look.setTexture(texture);//заливаем текстуру спрайтом
}

int map::print(RenderWindow& window) 
{
	//std::cout << "Starting to print map..." << "\n";	

	for (int i = 0; i < HEIGHT_MAP; i++)
	for (int j = 0; j < WIDTH_MAP; j++)
	{
		//std::cout << "Now in for" << "\n";

		if (TileMap[i][j] == ' ')  look.setTextureRect(IntRect(0, 0, 32, 32)); 
		if (TileMap[i][j] == 's')  look.setTextureRect(IntRect(32, 0, 32, 32));
		if (TileMap[i][j] == '0') look.setTextureRect(IntRect(64, 0, 32, 32));
 		
		look.setPosition(j * 32, i * 32);
		//std::cout << "End of for" << "\n";	
		window.draw(look);
	}

	return 1;
}

String map::get_ij(int i, int j)
{
	return TileMap[i][j];
}

void map::change_ij(int i, int j, char s)
{
	TileMap[i][j] = s;
}

/*void map::interactionWithMainHero(essence& hero)//ф-ция взаимодействия с картой
{
 
	for (int i = hero.get_y() / 32; i < (hero.get_y() + hero.get_h()) / 32; i++)
	for (int j = hero.get_x() / 32; j<(hero.get_x() + hero.get_w()) / 32; j++)
	{
		if (TileMap[i][j] == '0')
		{
			if (hero.get_dy() > 0)
			{
				hero.change_y(i * 32 - hero.get_h());
			}
			if (hero.get_dy() < 0)
			{
				hero.change_y(i * 32 + hero.get_h());
			}
			if (hero.get_dm() > 0)
			{
				hero.change_x(j * 32 - hero.get_w());
			}
			if (hero.get_dm() < 0)
			{
				hero.change_x(j * 32 + hero.get_w());
			}
		}
 
		if (TileMap[i][j] == 's') 
		{ 
			hero.change_x(300); hero.change_y(300);
			TileMap[i][j] = ' ';
		}
	}
}*/





