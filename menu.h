#pragma once
#include <vector>
#include <unistd.h>
#include <iostream>
#include <cstdio>

#define ChoiseNum 6
#define Extra 1

#define Background 0
#define Continue 1
#define NewGame 2
#define Multiplayer 3
#define Profile 4
#define Settings 5
#define Quit 6
#define ComingSoon 7

using namespace sf;

void Vector_push(std::vector<String> &Files)
{
	Files.push_back("nMenu.png");
	Files.push_back("Continue.png");
	Files.push_back("NewGame.png");
	Files.push_back("Multiplayer.png");
	Files.push_back("Profile.png");
	Files.push_back("Settings.png");
	Files.push_back("Quit.png");
	Files.push_back("ComingSoon.png");	
}

int menu(RenderWindow & window, View& view) 
{
	std::vector<String> Files;
	Vector_push(Files);

	std::vector<Texture*> textures;
	std::vector<Sprite*> menuPoints;

	Texture texture0, texture1, texture2, texture3, texture4, texture5, texture6, texture7;
	Sprite sprite0, sprite1, sprite2, sprite3, sprite4, sprite5, sprite6, sprite7;

	textures.push_back(&texture0);	
	textures.push_back(&texture1);
	textures.push_back(&texture2);
	textures.push_back(&texture3);
	textures.push_back(&texture4);
	textures.push_back(&texture5);
	textures.push_back(&texture6);
	textures.push_back(&texture7);

	menuPoints.push_back(&sprite0);
	menuPoints.push_back(&sprite1);
	menuPoints.push_back(&sprite2);
	menuPoints.push_back(&sprite3);
	menuPoints.push_back(&sprite4);
	menuPoints.push_back(&sprite5);
	menuPoints.push_back(&sprite6);
	menuPoints.push_back(&sprite7);

	for (int j = 0; j <= ChoiseNum + Extra; j++)
	{	
		textures[j]->loadFromFile("images/" + Files[j]);
		menuPoints[j]->setTexture(*textures[j]);

		if(j != 0 && j != 7)
		{
			menuPoints[j]->setPosition(300, 260 + 60*(j-1));
			menuPoints[j]->setColor(Color::White);
		}
		else
		{
			switch(j)
			{
			case 0: menuPoints[j]->setPosition(0, 0); break;
			case 7: menuPoints[j]->setPosition(300, 400); break;
			}
		}
			
	}

	bool isMenu = 1;
	int menuNum = 1;

 	view.setCenter(0, 0);
	view.reset(FloatRect(0, 0, 800, 640));
	window.setView(view);
	
	while (isMenu)
	{
		window.clear(Color(129, 181, 221));

		menuPoints[menuNum]->setColor(Color::White); 

		if(Keyboard::isKeyPressed(Keyboard::Down)) 
		{ 
			if(menuNum == ChoiseNum)
				menuNum = 1;
			else
				menuNum++;
			usleep(200000);
		}

		if(Keyboard::isKeyPressed(Keyboard::Up)) 
		{  
			if(menuNum == 1)
				menuNum = ChoiseNum;
			else
				menuNum--;
			usleep(200000);
		}

		menuPoints[menuNum]->setColor(Color::Blue);
				
		if (Keyboard::isKeyPressed(Keyboard::Return))
		{
			if (menuNum == Continue) {isMenu = false; view.reset(FloatRect(0, 0, 640, 480)); return 0;} 
			if (menuNum == NewGame) {isMenu = false; view.reset(FloatRect(0, 0, 640, 480)); return 2; }
			if (menuNum == Multiplayer)  { 
				isMenu = false;
				view.reset(FloatRect(0, 0, 640, 480));
				return 3;

				}
			if (menuNum == Profile)  { window.draw(*menuPoints[Background]); window.draw(*menuPoints[ComingSoon]); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == Settings)  { window.draw(*menuPoints[Background]); window.draw(*menuPoints[ComingSoon]); window.display(); while (!Keyboard::isKeyPressed(Keyboard::Escape)); }
			if (menuNum == Quit)  { window.close(); isMenu = false; view.reset(FloatRect(0, 0, 640, 480)); return 1; }
 
		}

		for (int k = 0; k <= ChoiseNum; k++)
		window.draw(*menuPoints[k]);
		
		
		window.display();
	}
}
