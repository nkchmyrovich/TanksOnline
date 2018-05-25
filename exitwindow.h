#include <Graphics.hpp>
#include <iostream>
#include <cstdio>

using namespace sf;

int exitWindow()
{
	RenderWindow exitwin(VideoMode(800, 200), "EXIT");

	Font font;
	font.loadFromFile("fonts/exitFont.otf");
	Text text("Are you sure you want to exit?(y/n)", font, 30);
	text.setColor(Color::Black);
	text.setStyle(sf::Text::Bold);
	text.setPosition(150, 100);

	Texture exitBGrTxt;
	Sprite exitBGrSpr;

	exitBGrTxt.loadFromFile("images/exitimage.jpg");
	exitBGrSpr.setTexture(exitBGrTxt);

	Event exitEvent;	

	while (exitwin.isOpen())
	{
		while (exitwin.pollEvent(exitEvent))
		{
			if(exitEvent.type == Event::Closed)
			{
				exitwin.close();
				std::cout << "YES \n";
				fflush(stdout);
				return 1;
			}

			/*if(Keyboard::isKeyPressed(Keyboard::Y))
			{
				exitwin.close();
				return 0;
			}

			if(Keyboard::isKeyPressed(Keyboard::N))
			{
				exitwin.close();
				return 1;
			}*/
		}

		exitwin.clear(Color::White);
		//std::cout << "Starting to print..." << "\n";
	
		exitwin.draw(exitBGrSpr);
		//std::cout << "Sprite printed" << "\n";
		//exitwin.draw(text);
		//std::cout << "Text printed " << "\n";
	
		exitwin.display();
	}

	return 2;
}

		
