#ifndef EATER_H
#define EATER_H

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

using namespace sf;

class Eater{

public:
  Eater();
  ~Eater();
  
  enum class Stats {inGame, endGame,pause};
  Stats stats = Stats::inGame;

  RenderWindow window;
  Event event;
  
  Font font;
    
  Text points, lose,gameOverTxt, restart, pauseTxt;
  Color textColor, text2Color;  

  SoundBuffer clickBuffer, fallBuffer;
  Sound click, fall;
  Music music;

  Texture sample, backText, gameOverText, carrotText;
  Sprite backImage, gameOverImage, carrotImage;
  
  size_t maxObj = 5, numOfObj = 0;
  RectangleShape *smile = new RectangleShape[maxObj];
  RectangleShape background, gameOver, carrot;

  Vector2i mouseCoord;
  Vector2f pixelMouseCoord;
  float maxTimer, timer, speed;
  bool pressed, del;
  int catchScore, loseScore, controlSpeed, xPosition;
  


  void code_game();
  void game_over();
  void pause_game();
  void loop_events();
  void run_game();

};

RectangleShape makesSquare(Sprite &image, RenderWindow &window);






#endif
