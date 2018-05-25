#pragma once 

struct Ports {
	int port;
	bool isFree;
	void unable () {
		isFree = false;
	}
	void enable () {
		isFree = true;
	}
};

const Ports ports [CLIENTS_AMOUNT] = { { 2000, true}, {2001, true}};

const int ids [CLIENTS_AMOUNT] = {0, 1};

#define CLIENTS_AMOUNT 2
