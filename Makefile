all:
	g++ main.cpp -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -o game
	./game
	rm game
