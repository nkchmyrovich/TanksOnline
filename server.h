#pragma once
#include <thread>
#include <vector>
#include <map>
#include <iostream> 
#include "ServerPacket.hpp"
#include "ClientPacket.hpp"
#include <SFML/Network.hpp>
#include "NetworkConfig.hpp"
#include "PlayerProp.hpp"

using namespace sf;


class Server
{
/*
	Сервер принимает от клиента пакеты и считывает их содержимое в ClientPacket.
	В mainLoop всё обсчитывается и отправляется ServerPacket, содержимое которого нужно
	для отрисовки у клиента.
*/
	enum PROPERTIES { HEIGHT_MAP = 25};

	bool isRunning;

	std::vector<int> clientsIps;

	TcpListener listener;
	TcpSocket socket;

	Clock clock;

	std::map<int, ClientPacket> clients; //структура пришедшая от клиента из пакета

	std::map<int, Player> players; //данные игроков для обсчитывания взаимодействий

	std::map<int, Packet> receivedPackets;

	std::vector<std::thread> threads;

	ServerPacket serverData;
	Packet serverPacket;
	//std::vector<Packet> receivedPackets; //полученные от клиентов пакеты
	std::map<int, Packet> sendPackets; //данные для отправки клиентам (для отрисовки)

	friend Packet& operator << (Packet& packet, ServerPacket& serverPack);
	friend Packet& operator >> (Packet& packet, ClientPacket& clientPack);

	void checkPorts ();
	void mainLoop ();
	void threadFunction (int index);
	void unpackPlayersData ();
	void updatePlayer (int id, float time);


	void stopMainLoop ();

	void packServerData ();
	void sendServerData ();
	void threadSendFunction (int index);

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

	map mapa;

public:
	
	void serverStart ();
	void stopServer (); 

	Server();
	~Server();

	/* data */
};