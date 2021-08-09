all: racing

racing: main.o enviroment.o 
	 g++ main.o enviroment.o -o racing -lpthread

main.o: main.cpp
	g++ -c main.cpp

enviroment.o: enviroment.cpp
	g++ -c enviroment.cpp

clean:
	rm -rf *.o racing
