#include "eater.hpp"

int main(){

  Eater *eater = new Eater;

  eater->run_game();

  delete eater;
  eater = nullptr;

  return 0;
}
