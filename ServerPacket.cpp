#include "ServerPacket.hpp"

ServerPacket::ServerPacket () :
	playersData ()
	{
		playersData.resize(CLIENTS_AMOUNT);
	}

ServerPacket::~ServerPacket () 
	{}



void ServerPacket::checkPlayers (std::vector<Player>& players) {
	for (auto& it : players) {
		PlayerData playerData;
		playerData.playerX = it.get_x ();
		playerData.playerY = it.get_y ();
		playerData.playerAngle = it.getSpriteAngle ();
		playerData.cannonAngle = it.getCannon().getSpriteAngle ();
		playersData.push_back (playerData);
	}
}

std::vector<PlayerData>& ServerPacket::getPlayersData () {
	return playersData;	
}