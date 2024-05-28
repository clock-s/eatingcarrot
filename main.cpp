#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <iostream>

using namespace sf;

int main(){
  RenderWindow window(VideoMode(300,200), "Não Deixe cair!");

  //ADD GAME FONT
  Font font;
  if(!font.loadFromFile("./PixelBloated.ttf")){
    std::cout << "Error to upload text font!";
    return 1;
  }



  while(window.isOpen()){
    Event event;

    if(window.pollEvent(event)){

    }



    //Update
    window.clear();
    window.display();
  }






  

  return 0;
}
