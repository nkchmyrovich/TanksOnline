#include "server.h"

using namespace sf;

Server::Server () :
	isRunning (true),
	listener (),
	socket (),
	clock (),
	clients (),
	players (),
	receivedPackets (),
	threads (CLIENTS_AMOUNT),
	serverData (),
	serverPacket (),
	sendPackets (),
	mapa ("map.png", mapPlan)
{
	Image playerImage;
	playerImage.loadFromFile("images/tank1.png");
	for (int i = 0; i < CLIENTS_AMOUNT; i++) {
		players[ids[i]];
		players[ids[i]] = Player(playerImage, playerImage, 150, 250, 66, 72, "Player1", "Cannon1");
	}
	//это тестовый вариант, нужна доработка
}

Server::~Server () {}

Packet& operator >> (Packet& packet, ClientPacket& clientPacket) { //запись в структуру полученных
																 //данных от клиента
	for (int i = 0; i < CLIENTS_AMOUNT; i++) {
		bool b = clientPacket.getKeyboard () [i];// здесь может крякнуться
		packet >> b; // в конструкторе есть resize для вектора keys_
	}
	packet >> clientPacket.mouseX_ >> clientPacket.mouseY_;
	return packet;

}

Packet& operator << (Packet& packet, ServerPacket& serverPacket) {
	for (auto& it : serverPacket.getPlayersData()) 
		packet << it.playerX << it.playerY << it.playerAngle << it.cannonAngle;	
	return packet;
}


void Server::threadFunction (int index) {
/*
	
*/
	Packet packet; //создаём пакет
	listener.listen(ports[index].port);
	listener.accept(socket);
	socket.receive(packet); //получаем пакет от клиента из порта
	receivedPackets[ids[index]] = packet; //помещаем полученный пакет в std::map
	std::cout << index << std::endl;


}

typedef void (Server::*threadMemFunc) (int x);

void Server::checkPorts () {
	//std::vector<std::thread> threads (CLIENTS_AMOUNT); //создаём вектор тредов
	int i = 0;
	//threadMemFunc f = &Server::threadFunction; // создание указателя на функцию-член класса
											   //но этот метод не работает
	for (auto& it : threads) {
		it = std::thread ([this, i] {this->threadFunction(i);}); //запускаем треды для каждого клиента
		i++;
	}
	for (auto& it : threads) {
		it.join(); //joining
	}
}

void Server::unpackPlayersData () {
	for (auto& it : receivedPackets) {
		ClientPacket packet;
		it.second >> packet;
		clients[it.first] = packet;
	}
}

void Server::mainLoop () {
	while (isRunning) {
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;
		checkPorts ();
		unpackPlayersData ();
		for (auto& it : clients) 
			updatePlayer (it.first, time);
		/*
		Здесь нужно написать доработку столкновений между танками и пулями.
		*/

		for (auto& it : players) {
			it.second.setMoveTimer(time);
		}
		packServerData();

	}
}

void Server::updatePlayer (int id, float time) {
	bool LeftPressed = clients[id].getKeyboard() [LEFT_KEY];
	bool RightPressed = clients[id].getKeyboard() [RIGHT_KEY];
	bool UpPressed = clients[id].getKeyboard() [UP_KEY];
	bool DownPressed = clients[id].getKeyboard() [DOWN_KEY];
	if(LeftPressed) //left
	{ 
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(90.0f);		
		players[id].setState(right); 
	}
	if(RightPressed) //right
	{
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(-90.0f);		
		players[id].setState(right);
	}
	if(UpPressed) //up
	{
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(180.0f);		
		players[id].setState(up); 
	}
	if(DownPressed) //down
	{
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(-180.0f);		
		players[id].setState(down);
	}
	if(LeftPressed && UpPressed) //left-up
	{
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(135.0f);		
		players[id].setState(leftUp); 
	}
	if(RightPressed && UpPressed) //right-up
	{
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(-135.0f);		
		players[id].setState(rightUp); 
	}
	if(LeftPressed && DownPressed) //left-down
	{
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(45.0f);		
		players[id].setState(leftDown);
	}
	if(RightPressed && DownPressed) //right-down
	{
		players[id].setSpeed(0.1);
		players[id].setSpriteAngle(-45.0f);		
		players[id].setState(rightDown);
	}
	players[id].update(time, mapa, clients[id].getMouseX(), clients[id].getMouseY());
		
}

void Server::serverStart () {
	std::cout << "SERVER!";
	mainLoop ();
}

void Server::stopServer () {
	stopMainLoop();
}

void Server::stopMainLoop () {
	isRunning = false;
}

void Server::packServerData () {
	for (auto& it : players) {
		PlayerData playerData;
		playerData.playerX = it.second.get_x();
		playerData.playerY = it.second.get_y();
		playerData.playerAngle = it.second.getSpriteAngle();
		playerData.cannonAngle = it.second.getCannon().getSpriteAngle();
		serverData.playersData.push_back(playerData); 
	}
	serverPacket << serverData;

}

void Server::sendServerData () {
	int i = 0;
	//threadMemFunc f = &Server::threadFunction; // создание указателя на функцию-член класса
											   //но этот метод не работает
	for (auto& it : threads) {
		it = std::thread ([this, i] {this->threadSendFunction(i);}); //запускаем треды для каждого клиента
		i++;
	}
	for (auto& it : threads) {
		it.join(); //joining
	}
}

void Server::threadSendFunction (int index) {
	listener.listen(ports[index].port);// не уверен на счёт этого
	listener.accept(socket);//
	socket.send(serverPacket);
}