#ifndef GAME_H
#define GAME_H

#include "GameEngine.h"
#include "Player.h"

class Game {

public:
  Game();
  void printMenu();
  void printCredits();

  void playGame(std::ifstream& file, std::string gameMode, bool advancedMode,
                bool activatedAI, bool random, int seed);
  void printMosaic(std::shared_ptr<Player> currentPlayer, bool advanced);
  void printFactories(std::shared_ptr<GameEngine> game);
  Colour transformColour(std::string input);
  int transformNumber(std::string input);
  std::string printGameOver(std::shared_ptr<Player> player1,
                            std::shared_ptr<Player> player2);
};

#endif // MENU_H