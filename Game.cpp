#include "Game.h"
#include "Board.h"
#include "GameEngine.h"
#include "Player.h"
#include "Tile.h"
#include <fstream>
#include <iostream>
void Game::playGame(std::ifstream& files, std::string gameMode,
                    bool advancedMode, bool activatedAI, bool random,
                    int seed) {
  // start new game after initialize the players, and creating necessary
  // variables that will be used later.

  // the inputFromUser is for saving the game
  std::string inputFromUser = "";
  std::string fileLocation = "";
  std::string player1Name = "";
  std::string player2Name = "";
  // This variable is for saving the tiles read from Text file
  std::string tilesBagFromTxt = "";
  // two switches changes when mode changes.
  bool readFromText = false;
  bool isTesting = false;
  std::shared_ptr<Player> player1;
  std::shared_ptr<Player> player2;
  int counter = 0;
  int roundNum = 5;
  int mosaicLineNum = 5;
  if (advancedMode) {
    mosaicLineNum = 6;
  }
  std::string tmpString;
  std::shared_ptr<GameEngine> game = std::make_shared<GameEngine>();
  // Loading and Testing  extracts data from txt and input
  // the game mode will be switched to playing if the loading is completed
  // which means you can play from what u saved last time
  if (gameMode == "Playing") {
    readFromText = false;
    isTesting = false;

  } else if (gameMode == "Testing") {
    readFromText = true;
    isTesting = true;
  } else if (gameMode == "Loading") {
    readFromText = true;
    isTesting = false;
  }
  // if testing or loading
  if (readFromText == true) {
    std::string tmp;
    files >> advancedMode;
    // if the advanced mode turned on, the mosaicLineNum
    // that used in many functions' parameters will also be changed
    if (advancedMode) {
      mosaicLineNum = 6;
    }
    files >> activatedAI;
    files >> random;
    files >> seed;
    files >> tilesBagFromTxt;
    game->addTilesToTileBag(tilesBagFromTxt);

    files >> player1Name;
    inputFromUser += player1Name;
    inputFromUser += "\n";
    files >> player2Name;
    inputFromUser += player2Name;
    inputFromUser += "\n";
  }
  // Newgame input, if eof is entered, quit the game
  else if (readFromText == false) {
    std::cout << "the name for player1:" << std::endl;
    std::cout << ">";
    std::cin >> player1Name;
    if (std::cin.eof()) {
      roundNum = 0;
      std::cout << "Good Bye" << std::endl;
    } else {
      inputFromUser += player1Name;
      inputFromUser += "\n";
      std::cout << "the name for player2:" << std::endl;
      std::cout << ">";

      std::cin >> player2Name;
      if (std::cin.eof()) {
        roundNum = 0;
        std::cout << "Good Bye" << std::endl;
      }
      inputFromUser += player2Name;
      inputFromUser += "\n";
    }
    game->addTilesToTileBag(advancedMode);
  }
  player1 = std::make_shared<Player>(player1Name, advancedMode);
  player2 = std::make_shared<Player>(player2Name, advancedMode);

  game->takeTilesFromTileBagIntoFactories();

  std::shared_ptr<Player> currentPlayer;
  currentPlayer = player1;

  bool roundEnded = false;
  for (int rounds = 0; rounds < roundNum; rounds++) {
    std::string turn;
    // these 3 input are in string format, which will be validated and changed
    // to certain types later
    std::string factoryNumInput;
    int factoryNum;
    std::string tileCodeInput;
    Colour tileCode;
    std::string storageRowInput;
    int storageRow;
    std::string wallNumInput;
    int wallNum;
    // while round is not ended and there are still tiles in the factories
    while (game->factoriesNotEmpty() && roundEnded == false) {
      // change current player whenmove is validated
      if (counter % 2 == 0) {
        currentPlayer = player1;
      } else if (counter % 2 == 1) {
        currentPlayer = player2;
      }
      // print information for Playing and Loading mode only
      if (isTesting == false) {
        std::cout << "TURN FOR PLAYER: " << currentPlayer->getName()
                  << std::endl;
        this->printFactories(game);
        this->printMosaic(currentPlayer, advancedMode);
      }
      // if the game is testing or load mode,input data from the txt
      if ((readFromText == true && !files.eof())) {

        if (!files.eof()) {
          files >> turn;
          if (files.eof()) {
            turn = "";
            readFromText = false;
          }
        }
        files >> factoryNumInput;
        files >> tileCodeInput;
        files >> storageRowInput;

      }
      // else if game is in Playing mode, input data from terminal
      else if (readFromText == false && roundEnded == false) {
        std::cout << ">";
        std::cin >> turn;
        if (std::cin.eof()) {
          roundEnded = true;
          rounds = roundNum;
        }
      }

      // if player input save, then save the game
      if (turn == "save") {
        std::cin >> fileLocation;
        std::cout << "game saved at:" << std::endl;
        std::cout << fileLocation << std::endl;
        std::ofstream output(fileLocation);
        output << advancedMode << " " << activatedAI << " " << random << " "
               << seed << std::endl;
        output << game->getTilesInTileBag() << inputFromUser;
        output.close();
        roundEnded = true;
        rounds = roundNum;
      }
      // if player input corerctly, continue the game

      else if (turn == "turn") {

        if (readFromText == false) {
          std::cin >> factoryNumInput;
          if (std::cin.eof()) {
            roundEnded = true;
            rounds = roundNum;
          }
        }
        // check the factories number input is correct
        if (game->validateFactoriesInput(factoryNumInput) &&
            roundEnded == false) {
          factoryNum = transformNumber(factoryNumInput);

          if (readFromText == false) {
            std::cin >> tileCodeInput;
            if (std::cin.eof()) {
              roundEnded = true;

              rounds = roundNum;
            }
          }
          // check the colour  input is correct

          if (game->validateColourCodeInput(factoryNum, tileCodeInput,
                                            advancedMode) &&
              roundEnded == false) {

            tileCode = transformColour(tileCodeInput);
            if (readFromText == true && files.peek() != EOF) {

            } else {
              std::cin >> storageRowInput;
              if (std::cin.eof()) {
                roundEnded = true;
                rounds = roundNum;

                readFromText = false;
              }
            }
            if (game->validateStorageRowInput(factoryNum, tileCode,
                                              storageRowInput, currentPlayer,
                                              mosaicLineNum) &&
                roundEnded == false) {
              storageRow = transformNumber(storageRowInput);

              int wallNum;
              wallNum = transformNumber(wallNumInput);
              inputFromUser += "turn";
              inputFromUser += " ";
              inputFromUser += factoryNumInput;
              inputFromUser += " ";
              inputFromUser += tileCodeInput;
              inputFromUser += " ";
              inputFromUser += storageRowInput;
              inputFromUser += "\n";

              // taking tiles from central factorieas

              if (factoryNum == 0) {
                // if that central factory have a F token, player will take
                // it first
                if (!game->getCentralFactories()->isEmpty() &&
                    game->getCentralFactories()->getTile(0)->getTileColour() ==
                        F) {
                  // take F token to the game board of the player in pointer
                  // function
                  std::shared_ptr<Tile> tmp =
                      game->getCentralFactories()->getTile(0);
                  currentPlayer->takeFToken(tmp);
                  // remove the pointer of the F token in central factory
                  game->getCentralFactories()->removeFront();
                }

                std::vector<std::shared_ptr<Tile>> tiles;
                // take tiles from central factory
                tiles = game->takeTilesFromCentralFactories(tileCode);
                // count the how many tiles are going to broken

                // put the extra tiles into broken
                tiles = currentPlayer->pushRestOfTilesToBroken(
                    currentPlayer->pushTilesIntoPatternline(tiles, storageRow),
                    mosaicLineNum);
                if (tiles.size() > 0) {
                  game->addTilesToBoxLid(tiles.back());
                  tiles.back() = nullptr;
                  tiles.pop_back();
                }

                counter++;
              } else if (0 < factoryNum && factoryNum <= mosaicLineNum) {
                // taking tiles from 1-5 factorieas

                std::vector<std::shared_ptr<Tile>> tiles;
                tiles = game->takeTilesFromFactories(tileCode, factoryNum);
                // take the rest of the tiles in factory to central factory

                game->putRestTilesIntoCentralFactory(factoryNum);
                // count the how many tiles are going to broken

                // currentPlayer->pushTilesIntoPatternline( tiles,
                //                                         storageRow);

                // put the extra tiles into broken
                currentPlayer->pushRestOfTilesToBroken(
                    currentPlayer->pushTilesIntoPatternline(tiles, storageRow),
                    mosaicLineNum);

                // change the current player
                counter++;
              }

              // from this line to the end of loop are for input validation
              if (!isTesting) {
                std::cout << "Turn successful." << std::endl;
                std::cout << std::endl;
              }
            } else if (!std::cin.eof()) {
              std::cout << "wrong storage row!" << std::endl;
            }
          } else if (!std::cin.eof()) {
            std::cout << "Wrong tilecode input!" << std::endl;
          }
        } else if (!std::cin.eof()) {

          std::cout << "factory number has to be 0-5,and cant be empty!"
                    << std::endl;
        }
      } else if (turn == "") {
      } else {
        std::cout << "Invalid turn input!" << std::endl;
      }
      // testing and game ended if the theres no more data in the file
      if (isTesting && files.eof() && turn == "") {
        this->printFactories(game);
        this->printMosaic(player1, advancedMode);
        std::cout << player1->printScore() << std::endl;
        this->printMosaic(player2, advancedMode);
        std::cout << player2->printScore() << std::endl;
        roundEnded = true;
        rounds = roundNum;
      }
    }

    // this function is doing several things, see in the player class.
    if (!std::cin.eof() && turn != "save" && !game->factoriesNotEmpty()) {
      std::shared_ptr<Player> players[2] = {player1, player2};
      bool numInputIncorrect;

      for (int currentPlayer = 0; currentPlayer < 2; currentPlayer++) {
        // if not in advanced mode, ends in normal way.
        if (!advancedMode) {

          players[currentPlayer]->roundEnd();
        }
        // if advanced mode is turned on, ends in another way with different
        // functions.
        else if (advancedMode) {
          for (int i = 0; i < mosaicLineNum; i++) {
            numInputIncorrect = true;
            // if the line can be pushed, terminal will ask for input from user
            if (players[currentPlayer]->getBoard()->getPatternLineTile(i, i) !=
                nullptr) {
              Colour tileColourToPush = players[currentPlayer]
                                            ->getBoard()
                                            ->getPatternLineTile(i, i)
                                            ->getTileColour();
              if (!isTesting) {
                printMosaic(players[currentPlayer], advancedMode);
              }
              // ask for input until the right one is entered
              while (numInputIncorrect && !std::cin.eof()) {
                if (!isTesting) {
                  std::cout << "input the tile position for line " << i + 1
                            << std::endl;
                }
                if (readFromText) {
                  files >> wallNumInput;
                  if (wallNumInput == "") {
                    readFromText = false;
                  }
                } else {
                  std::cin >> wallNumInput;
                }
                if (std::cin.eof()) {
                  roundEnded = true;
                  readFromText = false;
                }
                // if the wall number input is correct, then continue
                if (game->validateWallNumInput(tileColourToPush, i,
                                               players[currentPlayer],
                                               mosaicLineNum, wallNumInput) &&
                    roundEnded == false && wallNumInput != "") {
                  wallNum = transformNumber(wallNumInput);

                  players[currentPlayer]->calculateEachLine(i, mosaicLineNum,
                                                            wallNum);

                  players[currentPlayer]->getBoard()->pushOneLineIntoWall(
                      i, wallNum);
                  if (!isTesting) {
                    printMosaic(players[currentPlayer], advancedMode);
                  }
                  inputFromUser += wallNumInput;
                  inputFromUser += "\n";
                  numInputIncorrect = false;
                } else if (wallNumInput == "") {
                } else {
                  std::cout << "wrong wall Num input!" << std::endl;
                }
              }
            }
          }

          players[currentPlayer]->calculateBroken();
          if (players[currentPlayer]->getSocre() < 0) {
            players[currentPlayer]->setSocre(0);
          }
        }
        // put rest of tiles into box lid

        game->putRestTileIntoBoxLid(players[currentPlayer], mosaicLineNum);
      }
      // printing information when testing ended

      if (files.eof() && isTesting) {
        this->printFactories(game);
        this->printMosaic(player1, advancedMode);
        std::cout << player1->printScore() << std::endl;
        this->printMosaic(player2, advancedMode);
        std::cout << player2->printScore() << std::endl;
        numInputIncorrect = false;
        roundEnded = true;
        rounds = roundNum;
        isTesting = false;
      }
      // shufle the bag when the bag is empty
      if (game->bagIsEmpty() && turn != "") {

        game->takeTilesFromBoxLidIntoTileBag();

        game->shuffleBag(seed, random);
      }
      if (turn != "") {
        game->takeTilesFromTileBagIntoFactories();
      }
    }
    if (isTesting) {
      roundEnded = false;
    }
  }
  // print game over information
  if (!std::cin.eof() && roundEnded == false && !isTesting) {
    std::cout << this->printGameOver(player1, player2) << std::endl;
  }
};

Game::Game() {}
void Game::printMenu() {
  std::cout << std::endl;
  std::cout << "Menu" << std::endl;
  std::cout << "-----" << std::endl;
  std::cout << "1. New Game" << std::endl;
  std::cout << "2. Load Game" << std::endl;
  std::cout << "3. Credits" << std::endl;
  std::cout << "4. Quit" << std::endl;
  std::cout << std::endl;
}
void Game::printCredits() {
  std::cout << "-------------------------------" << std::endl;

  std::cout << "Name      :  "
            << "Yinglin Duan" << std::endl;
  std::cout << "Student ID:  "
            << "s3779079" << std::endl;
  std::cout << "Email     :  "
            << "s3779079@student.rmit.edu.au" << std::endl;
  std::cout << std::endl;
  std::cout << "Name      :  "
            << "Zhipeng Guo" << std::endl;
  std::cout << "Student ID:  "
            << "s3655706" << std::endl;
  std::cout << "Email     :  "
            << "s3655706@student.rmit.edu.au" << std::endl;
  std::cout << std::endl;
  std::cout << "Name      :  "
            << "Mingyang Wang" << std::endl;
  std::cout << "Student ID:  "
            << "s3632157" << std::endl;
  std::cout << "Email     :  "
            << "s3632157@student.rmit.edu.au" << std::endl;

  std::cout << "-------------------------------" << std::endl;
}

void Game::printMosaic(std::shared_ptr<Player> currentPlayer, bool advanced) {
  int lineNum = 5;
  int brokenLineNum = 7;
  if (advanced) {
    lineNum = 6;
    brokenLineNum = 8;
    /* code */
  }

  std::cout << std::endl;

  std::cout << "MOSAIC FOR " << currentPlayer->getName() << ":" << std::endl;
  // print patternline + wall
  for (int a = 0; a < lineNum; a++) {
    std::cout << a + 1 << ": ";

    for (int b = 0; b < lineNum - 1 - a; b++) {
      std::cout << "  ";
    }
    for (int c = 0; c < a + 1; c++) {
      std::cout << currentPlayer->getBoard()->printPatternLineTile(a, a - c)
                << +" ";
    }
    std::cout << "||";
    for (int c = 0; c < lineNum; c++) {
      std::cout << currentPlayer->getBoard()->printWallTile(a, c) << +" ";
    }
    std::cout << std::endl;
  }
  std::cout << "broken: ";

  // pritn broken line
  for (int i = 0; i < brokenLineNum; i++) {
    std::cout << currentPlayer->getBoard()->printBrokenLineTile(i) << " ";
  }
  std::cout << std::endl;
}

void Game::printFactories(std::shared_ptr<GameEngine> game) {
  std::cout << "Factories: " << std::endl;
  // print centralFactory
  std::cout << 0 << ": ";
  if (game->getFactories(0) == nullptr) {
    std::cout << ' ' << std::endl;
  } else {

    for (int j = 0; j < game->getCentralFactories()->getSize(); j++) {
      Colour tileCode =
          game->getCentralFactories()->getTile(j)->getTileColour();
      char title = 'R';
      if (tileCode == R) {
        title = 'R';
      } else if (tileCode == Y) {
        title = 'Y';
      } else if (tileCode == B) {
        title = 'B';
      } else if (tileCode == L) {
        title = 'L';
      } else if (tileCode == U) {
        title = 'U';
      } else if (tileCode == F) {
        title = 'F';
      } else if (tileCode == O) {
        title = 'O';
      }

      std::cout << title << " ";
    }
    std::cout << ' ' << std::endl;
  }
  // print factories

  for (int i = 0; i < 5; i++) {

    std::cout << i + 1 << ": ";
    for (int j = 0; j < FACTORYLENGTH; j++) {
      std::shared_ptr<Factory> factory = game->getFactories(i);
      if (factory->getTile(j) == nullptr) {

        std::cout << " ";
      } else {

        std::shared_ptr<Tile> tile = game->getFactories(i)->getTile(j);

        Colour tileCode = tile->getTileColour();

        char title = '\0';
        if (tileCode == R) {
          title = 'R';
        } else if (tileCode == Y) {
          title = 'Y';
        } else if (tileCode == B) {
          title = 'B';
        } else if (tileCode == L) {
          title = 'L';
        } else if (tileCode == U) {
          title = 'U';
        } else if (tileCode == F) {
          title = 'F';
        } else if (tileCode == O) {
          title = 'O';
        }
        std::cout << title << " ";
      }
      // delete factory;
    }
    std::cout << std::endl;
  }
}
// change the input from string to colour
Colour Game::transformColour(std::string input) {
  Colour tmp = R;
  if (input == "R") {
    tmp = R;
  } else if (input == "U") {
    tmp = U;
  } else if (input == "B") {
    tmp = B;
  } else if (input == "L") {
    tmp = L;
  } else if (input == "Y") {
    tmp = Y;
  } else if (input == "O") {
    tmp = O;
  }
  return tmp;
};
// change the input from string to integer

int Game::transformNumber(std::string input) {
  int tmp = 9;
  if (input == "0") {
    tmp = 0;
  } else if (input == "1") {
    tmp = 1;
  } else if (input == "2") {
    tmp = 2;
  } else if (input == "3") {
    tmp = 3;
  } else if (input == "4") {
    tmp = 4;
  } else if (input == "5") {
    tmp = 5;
  } else if (input == "6") {
    tmp = 6;
  }
  return tmp;
};
std::string Game::printGameOver(std::shared_ptr<Player> player1,
                                std::shared_ptr<Player> player2) {
  std::string result = "=== GAME OVER ===\n";
  result += "Final Scores: \n";
  result += player1->printScore();
  result += "\n";
  result += player2->printScore();
  result += "\n";

  if (player1->printScore() > player2->printScore()) {
    result += "Player ";
    result += player1->getName();
    result += " wins!";
    result += "\n";
  } else if (player1->printScore() < player2->printScore()) {
    result += "Player ";
    result += player1->getName();
    result += " wins!";
    result += "\n";
  } else {
    result += "draw!";
    result += "\n";
  }

  return result;
}
