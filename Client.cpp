#include "Client.hpp"

Client::Client () :
	socket (),
	clientPacket (),
	serverPacket (),
	receivedPacket (),
	packetToSend (),
	isRunning (true),
	players (),
	mapa ("map.png", mapPlan)
{
	players.resize(CLIENTS_AMOUNT);
	Image playerImage;
	playerImage.loadFromFile("images/tank1.png");
	for (int i = 0; i < CLIENTS_AMOUNT; i++) {
		players[ids[i]];
		players[ids[i]] = Player(playerImage, playerImage, 150, 250, 66, 72, "Player1", "Cannon1");
	}
}

Client::~Client () 
{}

Packet& operator << (Packet& packet, ClientPacket& clientPacket) { //запись в структуру полученных
																 //данных от клиента
	for (int i = 0; i < CLIENTS_AMOUNT; i++) {
		bool b = clientPacket.getKeyboard () [i];// здесь может крякнуться
		packet << b; // в конструкторе есть resize для вектора keys_
	}
	packet << clientPacket.mouseX_ << clientPacket.mouseY_;
	return packet;

}

Packet& operator >> (Packet& packet, ServerPacket& serverPacket) {
	for (auto& it : serverPacket.getPlayersData()) 
		packet >> it.playerX >> it.playerY >> it.playerAngle >> it.cannonAngle;	
	return packet;
}

void Client::connectToServer (IpAddress& ip, int id) {
	socket.connect(ip, ports[id].port);
} 

void Client::receiveServerPacket () {
	socket.receive(receivedPacket);
}

void Client::unpackServerData () {
	receivedPacket >> serverPacket;
}

void Client::updatePlayers () {
	int i = 0;
	for (auto& it : serverPacket.getPlayersData()) {
		players[i].setX(it.playerX);
		players[i].setY(it.playerY);
		players[i].setSpriteAngle(it.playerAngle);
		players[i].setCannonAngle(it.cannonAngle);
	}
}

void Client::sendClientData () {
	clientPacket.createClientPacket ();
	packetToSend << clientPacket;
	socket.send (packetToSend);
}

void Client::mainLoop (RenderWindow& window) {
	while (isRunning && window.isOpen()) {
		receiveServerPacket ();
		unpackServerData ();
		draw (window);
		sendClientData ();
	}
}

void Client::stopClient () {
	isRunning = false;
}

void Client::draw (RenderWindow& window) {
	window.clear(Color::Red);
	mapa.print(window);
	for (auto& it : players) {
		it.draw(window);
	}
	window.display();
	//дописать сдвиг камеры для клиента (идентификацию клиента у клиента)
}

void Client::startClient (IpAddress& ip, int id, RenderWindow& window) {
	connectToServer(ip, id);
	mainLoop(window);
}