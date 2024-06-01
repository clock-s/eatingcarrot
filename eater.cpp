#include "eater.hpp"

Eater::Eater(){

  stats = Stats::inGame;
  
  //WINDOW
  window.create(VideoMode(960,640), "Não Deixe cair!", Style::Titlebar | Style::Close);
  window.setFramerateLimit(60); //Set limit frame
  window.setPosition(Vector2i(200,80)); //Set window position 
  window.setMouseCursorVisible(false);



  //ADD TEXT
  font.loadFromFile("Archives/Fonts/./KingGaming.ttf");
  
  //In game
  points.setString("Catch: 0");/**/lose.setString("Loses: 0");
  points.setFont(font);/**/lose.setFont(font);
  points.setCharacterSize(20);/**/lose.setCharacterSize(20);

  textColor = {253,174,178};
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
}


