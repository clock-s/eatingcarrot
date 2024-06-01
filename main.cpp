#include <time.h>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/WindowStyle.hpp>
#include<SFML/Audio.hpp>
#include <cstdlib>

enum class Stats {initGame, inGame, endGame, pause};

using namespace sf;

Stats stats = Stats::inGame;

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
  font.loadFromFile("Archives/Fonts/./KingGaming.ttf");
  
  //In game
  Text points ("Catch: 0" , font , 20), lose("Loses: 0", font, 20);
  Color textColor (252,174,178); //green 174 or 254, choose
  points.setPosition(5,3);/*                */lose.setPosition(window.getSize().x - lose.getCharacterSize()*6, 3);
  points.setFillColor(textColor);/*       */lose.setFillColor(textColor);
  int catchScore = 0;/*                         */int loseScore = 0;
  
  //Off Game
  Text gameOverTxt("GAME OVER", font, 100), restart("Aperte F1 para voltar e Enter para sair", font, 12);
  gameOverTxt.setPosition(150,250);/*           */restart.setPosition(window.getSize().x - restart.getCharacterSize()*28, 3);
  gameOverTxt.setFillColor({252,254,178});/*   */restart.setFillColor(textColor);

  //Pause
  Text pauseTxt("PAUSE", font, 100);
  pauseTxt.setPosition(200,250);
  pauseTxt.setFillColor({252,254,178});
  

  //ADD SOUNDS
  SoundBuffer clickBuffer, fallBuffer;
  clickBuffer.loadFromFile("Archives/Sounds/./click.wav");  
  fallBuffer.loadFromFile("Archives/Sounds/./click-error.wav");
  
  Sound click (clickBuffer); 
  Sound fall(fallBuffer);

  Music music;
  music.openFromFile("Archives/Sounds/./soundtrack.wav");



  //MAKE OBJECTS
  
  //Smiles
  Texture sample;
  sample.loadFromFile("Archives/sprites/./sample.jpg");
  Sprite sampleImage(sample);

  size_t maxObj = 5; int numOfObj = 0;
  RectangleShape *smile = new RectangleShape[maxObj];
  for(size_t i = 0; i < maxObj ; i++ ) smile[i] = makesSquare(sampleImage, window);

  //Background in game
  Texture backText;
  backText.loadFromFile("Archives/sprites/./background.jpg");
  Sprite backImage(backText);
  
  RectangleShape background(Vector2f(window.getSize().x , window.getSize().y));
  background.setTexture(backImage.getTexture());

  //Background off game
  Texture gameOverText;
  gameOverText.loadFromFile("Archives/sprites/./gameover.jpg");
  Sprite gameOverImage(gameOverText);

  RectangleShape gameOver (Vector2f(window.getSize().x, window.getSize().y));
  gameOver.setTexture(gameOverImage.getTexture()); 
  
  //Carrot
  Texture carrotText;
  carrotText.loadFromFile("Archives/sprites/./carrot.png");
  Sprite carrotImage(carrotText);

  RectangleShape carrot(Vector2f(70,50));
  carrot.setTexture(carrotImage.getTexture());


  //OTHER PARAMETERS
  Vector2i mouseCoord;            //Mouse coordantes to
  Vector2f pixelMouseCoord;      //carrot end clicks

  float maxTimer = 20.0f; float timer = maxTimer;  //Make objects
  
  bool pressed = false;         //Control mouse  BUTTOM

  float speed = 2.0f;    int controlSpeed = 1;

  float xPosition;

  bool del = false;


  /*
  LOGIC: PRESS? -> MOVE -> IF BUTTOM -> YES -> TOP
           ^                   |               |
           |                  NO               |
           |                  |                |
           -------------------------------------
  */



//////////////////////////////GAME////////////////////////////

  while(window.isOpen()){
    Event event;

    while(window.pollEvent(event)){
      if(event.type == Event::Closed) window.close();  //Close Window

      //CONTROL MOUSE BUTTOM:call Run()

      if(event.type == event.MouseButtonPressed) pressed = false;

      mouseCoord = Mouse::getPosition(window); //Recive Mouse coord
      pixelMouseCoord = window.mapPixelToCoords(mouseCoord); //Accurace the coord if window had a Resized
      
      carrot.setPosition(pixelMouseCoord.x - 15,pixelMouseCoord.y - 10);

      if(Keyboard::isKeyPressed(Keyboard::Enter) && stats == Stats::inGame) stats = Stats::pause;
    }

  if(music.getStatus() == Music::Stopped || music.getStatus() == Music::Paused) music.play();

  
  if(stats == Stats::inGame){                   ///////IN GAME//////
      
      //INIT MUSIC
      if(music.getStatus() == Music::Stopped || music.getStatus() == Music::Paused) music.play();

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
        del = false;
        xPosition = rand()%(static_cast<int>(window.getSize().x) - static_cast<int>(smile->getSize().x) - 10) + 10;

        //CONDITION TO GAIN POINTS
        if(Mouse::isButtonPressed(Mouse::Left)){
          if(smile[i].getGlobalBounds().contains(carrot.getPosition()) && !pressed){
            click.play();
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
          fall.play();
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
        stats = Stats::endGame;
      }


      //APPLYING ALL UPDATES
      window.clear();
      window.draw(background);

      for(size_t i = 0 ; i < numOfObj ; i++) window.draw(smile[i]);
      window.draw(carrot);
      window.draw(points);
      window.draw(lose);
      
      window.display();
  
  } else if (stats == Stats::endGame){          ///////GAME OVER////////
    music.stop();

    window.clear();
    window.draw(gameOver);
    window.setMouseCursorVisible(true);

    window.draw(gameOverTxt);
    window.draw(restart);
    window.draw(points);

    window.display();

    if(Keyboard::isKeyPressed(Keyboard::F1)){
      speed = 2.0;
      float xPosition = rand()%(static_cast<int>(window.getSize().x) - static_cast<int>(smile->getSize().x) - 10) + 10;
      for(size_t i = 0 ; i < numOfObj ; i++) window.draw(smile[i]);
      numOfObj = 0;
      controlSpeed = 1;
      catchScore = 0;
      loseScore = 0;
      points.setString("Catch: 0");
      window.setMouseCursorVisible(false);
      
      stats = Stats::inGame; 

    }else if(Keyboard::isKeyPressed(Keyboard::Enter)) window.close();

  } else if (stats == Stats::pause){            //////////////PAUSE///////////////
    music.pause();

    window.clear();
    window.draw(gameOver);
    window.draw(carrot);
    window.draw(points);
    window.draw(lose);
    window.draw(pauseTxt);

    window.display();

    if(Keyboard::isKeyPressed(Keyboard::Escape)) stats = Stats::inGame;

  }

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
