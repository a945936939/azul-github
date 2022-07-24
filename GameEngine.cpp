#include "GameEngine.h"
#include <random>
GameEngine::GameEngine() {
  Colour f = F;

  this->first = std::make_shared<Tile>(f);
  this->tileBag = std::make_shared<TileBag>();
  this->boxLid = std::make_shared<BoxLid>();

  this->addFactory();

  this->centralFactory = std::make_shared<CentralFactory>();
  this->centralFactory->addTile(first);
};
GameEngine::~GameEngine(){};

std::vector<std::shared_ptr<Tile>>
GameEngine::takeTilesFromFactories(Colour tileCode, int factoryNum) {

  return factories[factoryNum - 1]->removeAllSameColour(tileCode);
}

std::vector<std::shared_ptr<Tile>>
GameEngine::takeTilesFromCentralFactories(Colour tileCode) {
  return centralFactory->removeAllSameColour(tileCode);
}
void GameEngine::putRestTilesIntoBroken(Colour colour){};
/*
 *This method put rest tiles after player taken
 */
void GameEngine::putRestTilesIntoCentralFactory(int factoryNum) {
  std::shared_ptr<Tile> tile;
  for (int i = 0; i < FACTORYLENGTH; i++) {
    if (factories[factoryNum - 1]->getTile(i) != nullptr) {
      tile = factories[factoryNum - 1]->getTile(i);
      centralFactory->addTile(tile);
      factories[factoryNum - 1]->setNull(i);
    }
  }
}

bool GameEngine::factoriesNotEmpty() {
  bool factoriesNotEmpty = true;

  int i = 0;
  while (i < 5 && factories[i]->isEmpty() == true) {
    i++;
  }

  if (i == 5 && centralFactory->isEmpty() == true) {
    factoriesNotEmpty = false;
  } else {
    factoriesNotEmpty = true;
  }

  return factoriesNotEmpty;
}
/*
 *This method puts tiles to tile bag after round end.
 *chekc if tile is F, the add to central factory, and put others into tileBag.
 */
void GameEngine::putRestTileIntoTilebag(std::shared_ptr<Player> player,
                                        int mosaicNum) {
  std::vector<std::shared_ptr<Tile>> tiles = player->getRestOfTiles(mosaicNum);
  while (!tiles.empty()) {
    if (tiles.front()->getTileColour() == F) {
      centralFactory->addTile(tiles.front());
      tiles.front() = nullptr;
      tiles.erase(tiles.begin());
    }
    this->tileBag->addBackTile(tiles.back());
    tiles.back() = nullptr;
    tiles.pop_back();
  }
}
void GameEngine::putRestTileIntoBoxLid(std::shared_ptr<Player> player,
                                       int mosaicNum) {
  std::vector<std::shared_ptr<Tile>> tiles = player->getRestOfTiles(mosaicNum);
  while (!tiles.empty()) {
    if (tiles.front()->getTileColour() == F) {
      centralFactory->addTile(tiles.front());
      tiles.front() = nullptr;
      tiles.erase(tiles.begin());
    }
    this->boxLid->addBackTile(tiles.back());
    tiles.back() = nullptr;
    tiles.pop_back();
  }
}
void GameEngine::takeTilesFromTileBagIntoFactories() {

  for (int i = 0; i < 5; i++) {
    for (int j = 0; j < 4; j++) {

      std::shared_ptr<Tile> tile = this->tileBag->takeFrontTile();
      factories[i]->insert(tile);
    }
  }
}
void GameEngine::addTilesToTileBag(bool advanced) {
  std::shared_ptr<Tile> tile;
  // so that the total tiles created is 60
  int a = 12;
  int b = 5;
  if (advanced) {
    a = 14;
    b = 6;
  }
  for (int i = 0; i < a; i++) {
    for (int j = 0; j < b; j++) {
      if (i == 13) {
        j += 2;
      }
      if (j == 0) {
        tile = std::make_shared<Tile>(B);
        this->tileBag->addBackTile(tile);
        tilesInTileBag += "B";
      } else if (j == 1) {
        tile = std::make_shared<Tile>(Y);
        this->tileBag->addBackTile(tile);
        tilesInTileBag += "Y";
      } else if (j == 2) {
        tile = std::make_shared<Tile>(R);
        this->tileBag->addBackTile(tile);
        tilesInTileBag += "R";
      } else if (j == 3) {
        tile = std::make_shared<Tile>(U);
        this->tileBag->addBackTile(tile);
        tilesInTileBag += "U";
      } else if (j == 4) {
        tile = std::make_shared<Tile>(L);
        this->tileBag->addBackTile(tile);
        tilesInTileBag += "L";
      } else if (j == 5 && advanced) {
        tile = std::make_shared<Tile>(O);
        this->tileBag->addBackTile(tile);
        tilesInTileBag += "O";
      }
    }
  }
  tilesInTileBag += '\n';
}
void GameEngine::addTilesToTileBag(std::string tilesFromTxt) {

  int i = 0;
  while (tilesFromTxt[i] != '\0') {
    tileBag->addBackTile(tilesFromTxt[i]);
    tilesInTileBag += tilesFromTxt[i];
    i++;
  }
  tilesInTileBag += '\n';
}
void GameEngine::addFactory() {
  for (int i = 0; i < 5; i++) {
    this->factories[i] = std::make_shared<Factory>();
  }
}
std::string GameEngine::getTilesInTileBag() { return this->tilesInTileBag; };

std::shared_ptr<CentralFactory> GameEngine::getCentralFactories() {
  return this->centralFactory;
};

bool GameEngine::validateFactoriesInput(std::string factoryNum) {
  bool result = true;
  int tmp = 9;
  if (factoryNum == "0") {
    tmp = 0;
  } else if (factoryNum == "1") {
    tmp = 1;
  } else if (factoryNum == "2") {
    tmp = 2;
  } else if (factoryNum == "3") {
    tmp = 3;
  } else if (factoryNum == "4") {
    tmp = 4;
  } else if (factoryNum == "5") {
    tmp = 5;
  } else {
    result = false;
  }
  if (tmp == 0 && (!centralFactory->isEmpty())) {
    result = true;
  } else if (tmp > 0 && tmp <= 5 && !factories[tmp - 1]->isEmpty()) {

    result = true;
  } else if (tmp == 0 && centralFactory->isEmpty()) {
    result = false;
  } else {

    result = false;
  }
  return result;
};
/*
 *This method checks if the colour input right
 */
bool GameEngine::validateColourCodeInput(int factoryNum, std::string colour,
                                         bool advanced) {
  bool result = false;

  if (colour == "Y" || colour == "B" || colour == "L" || colour == "R" ||
      colour == "U" || (colour == "O" && advanced)) {

    if (factoryNum == 0) {

      int s = centralFactory->getSize();

      for (int i = 0; i < s; i++) {
        if (centralFactory->getTile(i)->getTileColourString() == colour) {
          result = true;
          i = s;
        }
      }
    } else if (factoryNum > 0 && factoryNum <= 5) {
      for (int i = 0; i < FACTORYLENGTH; i++) {
        if (getFactories(factoryNum - 1)->getTile(i)->getTileColourString() ==
            colour) {
          result = true;
          i = FACTORYLENGTH;
        }
      }
    }
  }
  return result;
};
bool GameEngine::validateStorageRowInput(int factoryNum, Colour colour,
                                         std::string storageRowInput,
                                         std::shared_ptr<Player> player,
                                         int mosaicLineNum) {

  bool result = false;
  int tmp = 9;
  if (storageRowInput == "1") {
    tmp = 1;
  } else if (storageRowInput == "2") {
    tmp = 2;
  } else if (storageRowInput == "3") {
    tmp = 3;
  } else if (storageRowInput == "4") {
    tmp = 4;
  } else if (storageRowInput == "5") {
    tmp = 5;
  } else if (storageRowInput == "6" && mosaicLineNum == 6) {
    tmp = 6;
  }
  if (tmp > 0 && tmp <= mosaicLineNum) {
    if (player->canPushTileToPatternLine(tmp, colour, mosaicLineNum)) {
      result = true;
    }
  }
  return result;
};

bool GameEngine::validateWallNumInput(Colour colour, int storageRow,
                                      std::shared_ptr<Player> player,
                                      int mosaicLineNum,
                                      std::string wallNumInput) {

  bool result = true;
  int tmp = 9;
  if (wallNumInput == "1") {
    tmp = 1;
  } else if (wallNumInput == "2") {
    tmp = 2;
  } else if (wallNumInput == "3") {
    tmp = 3;
  } else if (wallNumInput == "4") {
    tmp = 4;
  } else if (wallNumInput == "5") {
    tmp = 5;
  } else if (wallNumInput == "6") {
    tmp = 6;
  }
  if (tmp == 9) {
    result = false;
  } else if (player->getBoard()->getWallTile(storageRow, tmp - 1) != nullptr) {
    result = false;
  } else if (player->getBoard()->getWallTile(storageRow, tmp - 1) == nullptr) {
    for (int i = 0; i < mosaicLineNum; i++) {
      if (player->getBoard()->getWallTile(i, tmp - 1) != nullptr) {
        if (player->getBoard()->getWallTile(i, tmp - 1)->getTileColour() ==
            colour) {
          result = false;
          i = mosaicLineNum;
        }
      }
    }
  }

  return result;
};
std::shared_ptr<Factory> GameEngine::getFactories(int i) {
  return this->factories[i];
};

bool GameEngine::bagIsEmpty() {
  bool result = true;

  if (this->tileBag->checkBagEmpty()) {
    result = true;
  } else {
    result = false;
  }
  return result;
};
void GameEngine::shuffleBag(int seed, bool random) {
  std::shared_ptr<TileBag> shuffledTileBag = std::make_shared<TileBag>();

  std::default_random_engine engine1(seed);

  std::random_device engine2;

  std::uniform_int_distribution<int> uniform_dist(0, 19);
  int i = 0;
  while (i < 20) {
    int randIndex;
    if (random) {
      randIndex = uniform_dist(engine1);

    } else {
      randIndex = uniform_dist(engine2);
    }
    if (tileBag->getTile(randIndex) != nullptr) {
      shuffledTileBag->addBackTile(tileBag->getTile(randIndex));
      tileBag->setTileNull(randIndex);
      i++;
    }
  }
  tileBag = shuffledTileBag;
};
void GameEngine::takeTilesFromBoxLidIntoTileBag() {
  for (int i = 0; i < 20; i++) {
    tileBag->addBackTile(boxLid->takeFrontTile());
  }
}
void GameEngine::addTilesToBoxLid(std::shared_ptr<Tile> tile) {

  boxLid->addBackTile(tile);
}
