#include <player.h>
#include <Entity.h>
#include <map.h>
#include <Graphics.hpp>
#include <view.h>
#include <iostream>
#include <menu.h>
#include <cstdio>
#include "server.h"
#include "Client.hpp"
#include "ServerPacket.hpp"
#include "ClientPacket.hpp"
#include <unistd.h>



#define EXIT 0
#define RESTART 1
#define START 2

const int HEIGHT_MAP = 25;//размер карты высота
const int WIDTH_MAP = 40;//размер карты ширина 

using namespace sf;

int StartGame(int Mode, RenderWindow& window)
{
	Image playerImage;
	playerImage.loadFromFile("images/tank1.png");

//////////////////////////////ПЕРЕПИЛИТЬ////////////////////////////////////////////////////
	String mapPlan[HEIGHT_MAP] = {
	"0000000000000000000000000000000000000000",
	"0                                      0",
	"0   s                                  0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                0                     0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0                                      0",
	"0000000000000000000000000000000000000000",
	};
////////////////////////////////////////////////////////////////////////////////////////////

	view.reset(FloatRect(0, 0, 640, 480));
	
	if(Mode == START)
		switch(menu(window, view))
		{
			case 0: /* СИСТЕМА СОХРАНЕНИЙ*/ break;					//ДОПИЛИТЬ
			case 1: window.close(); return EXIT; break;
			case 2:  break;
			case 3:
				pid_t pid = fork ();
				if (pid == 0) {
					Server server;
					server.serverStart();
				} else {
					Client client;
					IpAddress ip = IpAddress::getLocalAddress();
					client.startClient(ip, 0, window);
				}
				//Client client;
				//IpAddress ip("172.20.10.1");
				return EXIT;
				break;
		}

	map mapa("map.png", mapPlan);

	Player test(playerImage, playerImage, 150, 250, 66, 72, "Player1", "Cannon1");

	Clock clock;

	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time/800;
		Event event;
		while (window.pollEvent(event))
		{
			if(event.type == Event::Closed)
				window.close();
		}

		if(Keyboard::isKeyPressed(Keyboard::Tab)) { return true; }
		if(Keyboard::isKeyPressed(Keyboard::Escape))
		{
			switch(menu(window, view))
			{
			case 1: window.close(); return EXIT; break;
			case 2: return RESTART; break;
			default: break;
			}
		}
			
		window.clear(Color::Red);
		
		mapa.print(window); 
		test.draw(window);
	
		window.display();

		test.update(time, mapa, window);

		view = get_xy_for_view(test.get_x(), test.get_y());
		window.setView(view);
	}
}

void GameRunning(int Mode, RenderWindow& window)
{
	switch(int newMode = StartGame(Mode, window))
	{
		case EXIT: break;
		case RESTART: GameRunning(newMode, window); break;
		case START: GameRunning(newMode, window); break;
		default: break;
	}
}

int main()
{
	RenderWindow window(VideoMode(800, 640), "My_First_Game", Style::Fullscreen);
	GameRunning(START, window);
	return 0;
}