

a4.exe: driver.o Bats.o Event.o Gold.o Pit.o Room.o Wumpus.o Cave.o
	g++ driver.o Bats.o Event.o Gold.o Pit.o Room.o Wumpus.o Cave.o -o a4.exe
driver:
	g++ -c driver.cpp
Bats:
	g++ -c Bats.cpp
Event:
	g++ -c Event.cpp
Gold:
	g++ -c Gold.cpp
Pit:
	g++ -c Pit.cpp
Room:
	g++ -c Room.cpp
Wumpus:
	g++ -c Wumpus.cpp
Cave:
	g++ -c Cave.cpp
clean:
	rm -f *.o *.out *.exe
	clear
