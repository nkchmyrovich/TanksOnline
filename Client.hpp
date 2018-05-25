#pragma once 
#include <SFML/Network.hpp>

#include "ServerPacket.hpp"
#include "ClientPacket.hpp"
#include "NetworkConfig.hpp"



using namespace sf;


class Client
{

	TcpSocket socket;

	ClientPacket clientPacket; //для отправки серверу
	ServerPacket serverPacket; //принять от сервера

	Packet receivedPacket; //полученный от сервера пакет
	Packet packetToSend; //пакет для отправки на сервер

	bool isRunning;

	std::vector<Player> players;

	friend Packet& operator >> (Packet& packet, ServerPacket& clientPack); 
	friend Packet& operator << (Packet& packet, ClientPacket& clientPack);

	void connectToServer (IpAddress& ip, int id); //подключение к серверу через сокет по ip и порту
	void receiveServerPacket (); //получение пакета от сервера
	void unpackServerData (); //распаковка пакета в структуру ServerPacket
	void updatePlayers ();
	void draw (RenderWindow& window);
	void sendClientData (); //создание ClientPacket, упаковка в packetToSend, отпрака на сервер 

	void mainLoop (RenderWindow& window); //зацикливание

	


public:
	void startClient (IpAddress& ip, int id, RenderWindow& window);
	void stopClient ();

	Client();
	~Client();

	/* data */
};