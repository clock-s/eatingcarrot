#ifndef EATER_H
#define EATER_H

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

  enum class Stats {initGame, inGame, endGame, pause};
  Stats stats;
  
  RenderWindow window;
  
  Font font;
    
  Text points, lose,gameOverTxt, restart, pauseTxt;
  Color textColor;  

  SoundBuffer clickBuffer, fallBuffer;
  Sound click, fall;
  Music music;

  Texture sample, backText, gameOverText, carrotText;
  Sprite backImage, gameOverImage, carrotImage;

  RectangleShape *smile = new RectangleShape[maxObj];
  RectangleShape background, gameOver, carrot;

  Vector2i mouseCoord;
  Vector2f pixelMouseCoord;
  float maxTimer, timer, speed, controlSpeed, xPosition;
  bool pressed, del;
  int catchScore, loseScore;
  size_t maxObj, numOfObj;

  
  RectangleShape makesSquare(Sprite &image, RenderWindow &window);


  void code_game();
  void game_over();
  void pause_game();
  void loop_events();
  void run_game();

};




#endif
