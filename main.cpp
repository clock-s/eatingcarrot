#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include <cmath>
#include <iostream>
#include <string>
#include <time.h>
#include <cstdlib>

enum class Stats {initGame, inGame, endGame, pause};

using enum Stats;
using namespace sf;
using namespace std;

Stats stats = inGame;

RectangleShape makesSquare(Sprite &image, RenderWindow &window);

int main(){
  RenderWindow window(VideoMode(960,640), "Não Deixe cair!", Style::Titlebar | Style::Close);
  window.setFramerateLimit(60); //Set limit frame
  window.setPosition(Vector2i(200,80)); //Set window position 
  window.setMouseCursorVisible(false);

  //RANDOM TIME
  srand(time(NULL));


  //ADD TEXT
  Font font;
  if(!font.loadFromFile("sprites/./KingGaming.ttf")){
    cout << "Error to upload text font!\n";
    return 1;
  }
  
  //In game
  Text points ("Catch: 0" , font , 20), lose("Loses: 0", font, 20);
  Color textColor (252,174,178); //green 174 or 254, choose
  points.setPosition(5,3);/*                */lose.setPosition(window.getSize().x - lose.getCharacterSize()*6, 3);
  points.setFillColor(textColor);/*       */lose.setFillColor(textColor);
  int catchScore = 0;/*                         */int loseScore = 0;
  
  //Off Game
  Text gameOverTxt("GAME OVER", font, 100), restart("Aperte F1 para voltar e F2 para sair", font, 12);
  gameOverTxt.setPosition(100,100);/*           */restart.setPosition(window.getSize().x - restart.getCharacterSize()*20, 3);
  gameOverTxt.setFillColor(Color::White);/*   */restart.setFillColor(textColor);


  //MAKE OBJECTS
  
  //Smiles
  Texture sample;
  sample.loadFromFile("sprites/./sample.jpg");
  Sprite sampleImage(sample);

  size_t maxObj = 5; int numOfObj = 0;
  RectangleShape *smile = new RectangleShape[maxObj];
  for(size_t i = 0; i < maxObj ; i++ ) smile[i] = makesSquare(sampleImage, window);

  //Background in game
  Texture backText;
  backText.loadFromFile("sprites/./background.jpg");
  Sprite backImage(backText);
  
  RectangleShape background(Vector2f(window.getSize().x , window.getSize().y));
  background.setTexture(backImage.getTexture());

  //Background off game
  Texture gameOverText;
  gameOverText.loadFromFile("sprites/./gameover");
  Sprite gameOverImage(gameOverText);

  RectangleShape gameOver (Vector2f(window.getSize().x, window.getSize().y));
  gameOver.setTexture(gameOverImage.getTexture()); 
  
  //Carrot
  Texture carrotText;
  carrotText.loadFromFile("sprites/./carrot.png");
  Sprite carrotImage(carrotText);

  RectangleShape carrot(Vector2f(70,50));
  carrot.setTexture(carrotImage.getTexture());


  //OTHER PARAMETERS
  Vector2i mouseCoord;            //Mouse coordantes to
  Vector2f pixelMouseCoord;      //carrot end clicks

  float maxTimer = 20.0f; float timer = maxTimer;  //Make objects
  
  bool pressed = false;         //Control mouse  BUTTOM

  float speed = 2.0f;    int controlSpeed = 1;


  /*
  LOGIC: PRESS? -> MOVE -> IF BUTTOM -> YES -> TOP
           ^                   |               |
           |                  NO               |
           |                  |                |
           -------------------------------------
  */





  while(window.isOpen()){
    Event event;

    while(window.pollEvent(event)){
      if(event.type == Event::Closed) window.close();  //Close Window

        mouseCoord = Mouse::getPosition(window); //Recive Mouse coord
        pixelMouseCoord = window.mapPixelToCoords(mouseCoord); //Accurace the coord if window had a Resized
      
        carrot.setPosition(pixelMouseCoord.x - 15,pixelMouseCoord.y - 10);
      }

    //CONTROL MOUSE BUTTOM
    if(event.type == event.MouseButtonPressed) pressed = false;

  
  if(stats == inGame){                   ///////IN GAME//////
      //ADJUST INIT OF SMILES
      if(numOfObj < maxObj ){
        if(timer > maxTimer){
          timer = 0;
          numOfObj++;
        }else{
          timer += 1.0f;
        }
      }

      //CHECK ALL SMILES
      for(size_t i = 0 ; i < numOfObj ; i++){
        bool del = false;
        float xPosition = rand()%(static_cast<int>(window.getSize().x) - static_cast<int>(smile->getSize().x) - 10) + 10;

        //CONDITION TO GAIN POINTS
        if(Mouse::isButtonPressed(Mouse::Left)){
          if(smile[i].getGlobalBounds().contains(carrot.getPosition()) && !pressed){
            del = true;
            catchScore++;
            controlSpeed++;
            points.setString("Catch: " + std::to_string(catchScore));
            pressed = true;
          }
        }

        //MOVEMENT
        smile[i].move(0,speed);


        //CONDITION TO GAIN LOSE POINTS
        if((smile[i].getPosition().y + smile->getSize().y) > window.getSize().y){ 
          del = true;
          loseScore++;
          lose.setString("Loses: " + std::to_string(loseScore));
        }
      
      
        //GO TO THE TOP OF WINDOW
        if(del){
          smile[i].setPosition(xPosition ,10);
        }

      
        //INCREASE SPEED/DIFICULT
        if(controlSpeed%10 == 0){
          speed += .2f;
          controlSpeed++;
        }
      }

      
      //GAME OVER
      if(loseScore == 10){
        stats = inGame;
      }


      //APPLYING ALL UPDATES
      window.clear();
      window.draw(background);

      for(size_t i = 0 ; i < numOfObj ; i++) window.draw(smile[i]);
      window.draw(carrot);
      window.draw(points);
      window.draw(lose);
  
  } else if (stats == endGame){          ///////GAME OVER////////
    window.clear();
    window.draw(gameOver);

    window.draw(gameOverTxt);
    window.draw(restart);
    window.draw(points);

    if(Keyboard::isKeyPressed(Keyboard::F1)){
      speed = 2.0;
      float xPosition = rand()%(static_cast<int>(window.getSize().x) - static_cast<int>(smile->getSize().x) - 10) + 10;
      for(size_t i = 0 ; i < numOfObj ; i++) window.draw(smile[i]);
      numOfObj = 0;
      controlSpeed = 1;
      catchScore = 0;
      loseScore = 0;
    }else if(Keyboard::isKeyPressed(Keyboard::F2)) window.close();

  }



    window.display();
  }





  //DELETE ALL OBJECTS CREATED
  delete[] smile;
  smile = nullptr;

  return 0;
}




RectangleShape makesSquare(Sprite &image, RenderWindow &window){
  RectangleShape square;
  square.setSize(Vector2f(100,100));
  square.setPosition((rand()%(static_cast<int>(window.getSize().x) - static_cast<int>(square.getSize().x) - 20) + 10) ,10);
  square.setTexture(image.getTexture());
  square.setFillColor(Color(255,51,153));

  return square;
}
