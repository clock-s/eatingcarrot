all:
	g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -o game
	./game
	rm game
