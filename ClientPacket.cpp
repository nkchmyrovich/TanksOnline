#include "ClientPacket.hpp"

ClientPacket::ClientPacket () :
	keys_ (),
	mouseX_ (0),
	mouseY_ (0)
{
	keys_.resize(KEYS_NUMBER);
	for (int i = 0; i < KEYS_NUMBER; i++)
		keys_[i] = false;

	checkKeyboard ();
	checkMouse ();
}

ClientPacket::~ClientPacket () 
{}

void ClientPacket::checkKeyboard () {
	if (Keyboard::isKeyPressed(Keyboard::Up)) 
		keys_[UP_KEY] = true;
	
	if (Keyboard::isKeyPressed(Keyboard::Down)) 
		keys_[DOWN_KEY] = true;
	
	if (Keyboard::isKeyPressed(Keyboard::Right)) 
		keys_[RIGHT_KEY] = true;
	
	if (Keyboard::isKeyPressed(Keyboard::Left)) 
		keys_[LEFT_KEY] = true;

	if (Keyboard::isKeyPressed(Keyboard::S)) 
		keys_[S_KEY] = true;
}

void ClientPacket::checkMouse () {
	if (Mouse::isButtonPressed(Mouse::Right)) 
		keys_[RIGHT_MOUSE] = true;
	
	if (Mouse::isButtonPressed(Mouse::Left))
		keys_[LEFT_MOUSE] = true;

	Vector2i positionI = Mouse::getPosition ();
	Vector2f position = Vector2f(positionI.x, positionI.y);

	mouseX_ = position.x;
	mouseY_ = position.y;
}

void ClientPacket::createClientPacket () {
	checkKeyboard ();
	checkMouse ();
}



std::vector<bool>& ClientPacket::getKeyboard () {
	return keys_;
}

float ClientPacket::getMouseX () {
	return mouseX_;
}

float ClientPacket::getMouseY () {
	return mouseY_;
}

Vector2f ClientPacket::getMousePosition () {
	return Vector2f(mouseX_, mouseY_);
}