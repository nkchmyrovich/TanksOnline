#pragma once 
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>
using namespace sf;

enum KEYS {
	UP_KEY,
	DOWN_KEY,
	RIGHT_KEY,
	LEFT_KEY,
	S_KEY,
	RIGHT_MOUSE,
	LEFT_MOUSE
};

#define KEYS_NUMBER 7

enum IDS {
	CLIENT1,
	CLIENT2
};

/*
Пакет содержит информацию о командах, подаваемых клиентом на сервер.
*/

class ClientPacket
{

	void checkKeyboard ();
	void checkMouse ();


public:
	std::vector<bool> keys_;
	float mouseX_;
	float mouseY_;

	void createClientPacket ();

	float getMouseX ();
	float getMouseY ();
	Vector2f getMousePosition ();

	std::vector<bool>& getKeyboard ();

	ClientPacket ();
	~ClientPacket ();

	/* data */
};