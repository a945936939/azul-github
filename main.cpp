#include "Board.h"
#include "Game.h"
#include "GameEngine.h"
#include "Player.h"
#include <fstream>
#include <iostream>
int main(int argc, char* argv[]) {

  // the game mode is for checking whether the game is in playing, loading or
  // testing

  std::ifstream file;
  std::string choice = "-1";
  std::string gameMode = "";
  bool advancedMode = false;
  bool activatedAI = false;
  bool random = false;
  int seed = 3;
  std::shared_ptr<Game> game = std::make_shared<Game>();
  // testing mode from terminal
  int i = 0;
  while (i < argc) {
    std::string tmp;
    tmp = argv[i];
    /* code */
    if (tmp == "-s") {
      random = true;
      if (argv[i + 1] != nullptr) {
        seed = std::atoi(argv[i + 1]);
      } else {
        std::cout << "input seed number plz" << std::endl;
        i--;
      }

    } else if (tmp == "--adv") {
      advancedMode = true;
    } else if (tmp == "--ai") {
      activatedAI = true;
    } else if (tmp == "-t" && i == 1) {
      std::string fileLocation = argv[i + 1];
      std::ifstream file(fileLocation);
      // check if file could not be opened
      if (file.fail()) {
        std::cout << "check your file name!" << std::endl;
      } else {
        gameMode = "Testing";
        game->playGame(file, gameMode, advancedMode, activatedAI, random, seed);
        choice = "0";
      }
      i = argc;
    }
    i++;
  }

  // Open the menu

  while (choice != "0") {

    std::cout << "Welcome to Azul!" << std::endl;
    std::cout << "--------------------" << std::endl;
    game->printMenu();
    std::cout << ">";

    std::cin >> choice;
    std::cout << std::endl;
    if (std::cin.eof()) {
      choice = "0";
    } else if (choice == "1") {
      // enter the play mode
      gameMode = "Playing";
      game->playGame(file, gameMode, advancedMode, activatedAI, random, seed);
      if (std::cin.eof()) {
        choice = "0";
      }
    } else if (choice == "2") {
      std::cout << "Enter the filename from which load a game" << std::endl;
      std::string fileLocation;
      std::cin >> fileLocation;

      if (std::cin.eof()) {
        choice = "0";
      } else {
        std::ifstream file(fileLocation);
        if (file.fail()) {
          // file could not be opened
          std::cout << "chekck your file name!" << std::endl;
        } else {
          // enter the game by load mode
          gameMode = "Loading";
          game->playGame(file, gameMode, advancedMode, activatedAI, random,
                         seed);
        }
      }
      if (std::cin.eof()) {
        choice = "0";
      }
    }

    else if (choice == "3") {

      game->printCredits();
      if (std::cin.eof()) {
        choice = "0";
      }
    } else if (choice == "4") {
      std::cout << "See you next time.." << std::endl;
      choice = "0";
    } else {
      std::cout << "Invaild input" << std::endl;
    }
  }
  if (choice != "4") {
    std::cout << "Good Bye!" << std::endl;
  }

  return EXIT_SUCCESS;
}
