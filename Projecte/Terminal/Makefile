#OPCIONS = -D_JUDGE_ -G_GLIBCXX_DEBUG -O0 -Wall -Wextra -Wno-sign-compare -std=c++11 -g
#OPCIONS = -O0 -Wall -Wextra -Werror -Wno-sign-compare -std=c++11 -ansi -g
OPCIONS = -O0 -Wall -Wextra -Wno-sign-compare -std=c++11 -ansi -g

program.exe: driver_gestterm.o ubicacio.o contenidor.o terminal.o
	g++ -o program.exe driver_gestterm.o ubicacio.o contenidor.o terminal.o -lesin
	rm *.o

driver_gestterm.o: driver_gestterm.cpp ubicacio.cpp ubicacio.hpp contenidor.cpp contenidor.hpp cataleg.hpp terminal.cpp terminal.hpp
	g++ -c driver_gestterm.cpp $(OPCIONS)

ubicacio.o: ubicacio.cpp ubicacio.hpp
	g++ -c ubicacio.cpp $(OPCIONS)

contenidor.o: contenidor.cpp contenidor.hpp
	g++ -c contenidor.cpp $(OPCIONS)

terminal.o: terminal.cpp terminal.hpp ubicacio.hpp contenidor.hpp cataleg.hpp
	g++ -c terminal.cpp $(OPCIONS)

clean:
	rm *.exe
	rm *.out
	rm *.o
	rm *.gch



test.exe: xxx.o ubicacio.o contenidor.o terminal.o
	g++ -o program.exe xxx.o ubicacio.o contenidor.o terminal.o -lesin
	rm *.o

xxx.o: xxx.cpp ubicacio.cpp ubicacio.hpp contenidor.cpp contenidor.hpp cataleg.hpp terminal.cpp terminal.hpp
	g++ -c xxx.cpp $(OPCIONS)