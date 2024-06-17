BIBLIOTECAS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
EXECUTAVEL = EatingCarrot.exe


all:
	g++ -c main.cpp
	
	g++ -c eater.cpp

	g++ main.o eater.o $(BIBLIOTECAS) -o $(EXECUTAVEL)
	
	rm *.o

	./$(EXECUTAVEL)

	rm $(EXECUTAVEL)
