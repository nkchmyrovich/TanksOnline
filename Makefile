CC=g++
STD11=-std=c++11


CFLAGS=-std=c++11 -c -Wall

all: hello

hello: main.o player.o map.o Entity.o cannon.o bullet.o server.o Client.o ClientPacket.o ServerPacket.o
	$(CC)  main.o player.o map.o Entity.o cannon.o bullet.o server.o Client.o ClientPacket.o ServerPacket.o -o game -L/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/lib -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

Entity.o: Entity.cpp
	$(CC) $(CFLAGS) Entity.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

player.o: player.cpp
	$(CC) $(CFLAGS) player.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Docume:nts/4sem/proj/src

cannon.o: cannon.cpp
	$(CC) $(CFLAGS) cannon.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

map.o: map.cpp
	$(CC) $(CFLAGS) map.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

bullet.o: bullet.cpp
	$(CC) $(CFLAGS) bullet.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src
	
server.o: server.cpp
	$(CC) $(CFLAGS) server.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

Client.o: Client.cpp
	$(CC) $(CFLAGS) Client.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

ClientPacket.o: ClientPacket.cpp
	$(CC) $(CFLAGS) ClientPacket.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

ServerPacket.o: ServerPacket.cpp
	$(CC) $(CFLAGS) ServerPacket.cpp -I/Users/hmurovicnikitaandreevic/Documents/SFML-2.3.2/include/SFML -I/Users/hmurovicnikitaandreevic/Documents/4sem/proj/src

clean:
	rm -rf *.o hello
