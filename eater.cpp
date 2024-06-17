#include "eater.hpp"

RectangleShape makesSquare(Sprite &image, RenderWindow &window) {
  RectangleShape square;
  square.setSize(Vector2f(100, 100));
  square.setPosition(
    (rand() % (static_cast<int>(window.getSize().x) - static_cast<int>(square.getSize().x) - 20) + 10),
    10);
  square.setTexture(image.getTexture());
  square.setFillColor(Color(255, 51, 153));

  return square;
}

Eater::Eater() {
  stats = Stats::inGame;

  srand(time(NULL));

  // WINDOW
  window.create(VideoMode(960, 640), "Não Deixe cair!",Style::Titlebar | Style::Close);
  window.setFramerateLimit(60);          // Set limit frame
  window.setPosition(Vector2i(200, 80)); // Set window position
  window.setMouseCursorVisible(false);

  // ADD TEXT
  font.loadFromFile("Archives/Fonts/./KingGaming.ttf");
  textColor = {252, 174, 178};
  text2Color = {252, 254, 178};

  // In game
  points.setString("Catch: 0"); /*              */lose.setString("Loses: 0");
  points.setFont(font); /*                     */lose.setFont(font);
  points.setCharacterSize(20); /*       */lose.setCharacterSize(20);
  points.setPosition(5, 3); /*         */lose.setPosition(window.getSize().x - lose.getCharacterSize() * 6, 3);
  points.setFillColor(textColor); /* */lose.setFillColor(textColor);
  catchScore = 0; /*                       */loseScore = 0;

  // Off Game
  gameOverTxt.setString("GAME OVER"); /*              */restart.setString("Aperte F1 para voltar e Enter para sair");
  gameOverTxt.setFont(font); /*                      */restart.setFont(font);
  gameOverTxt.setCharacterSize(100); /*       */restart.setCharacterSize(12);
  gameOverTxt.setPosition(150, 250); /*      */restart.setPosition(window.getSize().x - restart.getCharacterSize() * 28, 3);
  gameOverTxt.setFillColor(text2Color); /* */restart.setFillColor(textColor);

  // Pause
  pauseTxt.setString("PAUSE");
  pauseTxt.setFont(font);
  pauseTxt.setCharacterSize(100);
  pauseTxt.setPosition(200, 250);
  pauseTxt.setFillColor({252, 254, 178});

  // ADD SOUNDS
  clickBuffer.loadFromFile("Archives/Sounds/./click.wav");
  fallBuffer.loadFromFile("Archives/Sounds/./click-error.wav");

  click.setBuffer(clickBuffer);
  fall.setBuffer(fallBuffer);

  music.openFromFile("Archives/Sounds/./soundtrack.wav");

  // MAKE OBJECTS

  // Smiles
  sample.loadFromFile("Archives/sprites/./sample.jpg");
  Sprite sampleImage(sample);

  maxObj = 5;
  numOfObj = 0;
  for (size_t i = 0; i < maxObj; i++)
    smile[i] = makesSquare(sampleImage, window);

  // Background in game
  backText.loadFromFile("Archives/sprites/./background.jpg");
  backImage.setTexture(backText);
  background.setSize(Vector2f(window.getSize().x, window.getSize().y));
  background.setTexture(backImage.getTexture());

  // Background off game
  gameOverText.loadFromFile("Archives/sprites/./gameover.jpg");
  gameOverImage.setTexture(gameOverText);
  gameOver.setSize(Vector2f(window.getSize().x, window.getSize().y));
  gameOver.setTexture(gameOverImage.getTexture());

  // Carrot
  carrotText.loadFromFile("Archives/sprites/./carrot.png");
  carrotImage.setTexture(carrotText);
  carrot.setSize(Vector2f(70, 50));
  carrot.setTexture(carrotImage.getTexture());

  // OTHER PARAMETERS
  maxTimer = 20.0f;
  timer = maxTimer; // Make objects

  pressed = false; //TODO MOUSE BUTTON

  speed = 2.0f;
  controlSpeed = 1;
}

Eater::~Eater() {
  delete[] this->smile;
  this->smile = nullptr;
}

/////////////////////////////////////////////////GAME////////////////////////////////////////////////

void Eater::code_game() {
  if (music.getStatus() == Music::Stopped || music.getStatus() == Music::Paused)
    music.play();
  // ADJUST INIT OF SMILES
  if (numOfObj < maxObj) {
    if (timer > maxTimer) {
      timer = 0;
      numOfObj++;
    } else {
      timer += 1.0f;
    }
  }

  // CHECK ALL SMILES
  for (size_t i = 0; i < numOfObj; i++) {
    del = false;
    xPosition = rand() % (static_cast<int>(window.getSize().x) - static_cast<int>(smile->getSize().x) - 10) +10;

    // CONDITION TO GAIN POINTS
    if (Mouse::isButtonPressed(Mouse::Left)) {
      if (smile[i].getGlobalBounds().contains(carrot.getPosition()) && !pressed) {
        click.play();
        del = true;
        catchScore++;
        controlSpeed++;
        points.setString("Catch: " + std::to_string(catchScore));
        pressed = true;
      }
    }

    // MOVEMENT
    smile[i].move(0, speed);

    // CONDITION TO GAIN LOSE POINTS
    if ((smile[i].getPosition().y + smile->getSize().y) > window.getSize().y) {
      fall.play();
      del = true;
      loseScore++;
      lose.setString("Loses: " + std::to_string(loseScore));
    }

    // GO TO THE TOP OF WINDOW
    if (del) {
      smile[i].setPosition(xPosition, 10);
    }

    // INCREASE SPEED/DIFICULT
    if (controlSpeed % 10 == 0) {
      speed += .2f;
      controlSpeed++;
    }
  }

  // GAME OVER
  if (loseScore == 10) {
    stats = Stats::endGame;
  }

  // APPLYING ALL UPDATES
  window.clear();
  window.draw(background);

  for (size_t i = 0; i < numOfObj; i++)
    window.draw(smile[i]);
  window.draw(carrot);
  window.draw(points);
  window.draw(lose);

  window.display();
}

///////////////////////////////////GAME OVER////////////////////////

void Eater::game_over() {
  music.stop();

  window.clear();
  window.draw(gameOver);
  window.setMouseCursorVisible(true);

  window.draw(gameOverTxt);
  window.draw(restart);
  window.draw(points);

  window.display();

  if (Keyboard::isKeyPressed(Keyboard::F1)) {
    speed = 2.0;
    float xPosition = rand() % (static_cast<int>(window.getSize().x) - static_cast<int>(smile->getSize().x) - 10) + 10;
    
    for (size_t i = 0; i < numOfObj; i++) window.draw(smile[i]);
    
    numOfObj = 0;
    controlSpeed = 1;
    catchScore = 0;
    loseScore = 0;
    points.setString("Catch: 0");
    window.setMouseCursorVisible(false);

    stats = Stats::inGame;
  }

  if (Keyboard::isKeyPressed(Keyboard::Return))
    window.close();
}

////////////////////////////////////////////////////////PAUSE///////////////////////////////

void Eater::pause_game() {

  music.pause();

  window.clear();
  window.draw(gameOver);
  window.draw(carrot);
  window.draw(points);
  window.draw(lose);
  window.draw(pauseTxt);

  window.display();

  if (Keyboard::isKeyPressed(Keyboard::Escape))
    stats = Stats::inGame;
}

void Eater::loop_events() {

  Event *event = new Event;

  while (window.pollEvent(*event)) {
    if (event->type == Event::Closed)
      window.close(); // Close Window

    if (event->type == event->MouseButtonPressed)
      pressed = false;

    mouseCoord = Mouse::getPosition(window); // Receive Mouse coord
    pixelMouseCoord = window.mapPixelToCoords(mouseCoord); // Accurace the coord if window had a Resized

    carrot.setPosition(pixelMouseCoord.x - 15, pixelMouseCoord.y - 10);

    if (Keyboard::isKeyPressed(Keyboard::Enter) && stats == Stats::inGame)
      stats = Stats::pause;
  }

  delete event;
}

void Eater::run_game() {
  while (window.isOpen()) {
    loop_events();
    if (stats == Stats::inGame) {
      code_game();
    }
    if (stats == Stats::endGame) {
      game_over();
    }
    if (stats == Stats::pause) {
      pause_game();
    }
  }
}
