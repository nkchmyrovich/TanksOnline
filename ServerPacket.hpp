#pragma once
#include "player.h" 
/*
Пакет должен содержать в себе всё, что необходимо для отрисовки у клиента.

*/
using namespace sf;

struct PlayerData {
	float playerX;
	float playerY;
	float playerAngle;
	float cannonAngle;
};

#define CLIENTS_AMOUNT 2

class ServerPacket
{
	



public:
	std::vector<PlayerData> playersData;// fixit: сделать private

	void checkPlayers (std::vector<Player>& players); //формирование пакета для передачи от 
													  //сервера клиенту

	//void getPlayers (std::vector<Player>& players); //получение players из данных пакета

	std::vector<PlayerData>& getPlayersData ();

	ServerPacket();
	~ServerPacket();

	
};