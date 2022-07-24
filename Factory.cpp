#include "Factory.h"
#include <iostream>
#include <vector>
Factory::Factory() {}
Factory::~Factory() {
  factory[0] = nullptr;
  factory[1] = nullptr;
  factory[2] = nullptr;
  factory[3] = nullptr;
}

bool Factory::isEmpty() {

  int i = 0;
  int counter = 0;
  bool result = true;

  while (i < FACTORYLENGTH) {

    if (factory[i] != nullptr) {
      counter++;
    }
    i++;
  }
  if (counter > 0) {
    result = false;
  } else {
    result = true;
  }

  return result;
};
void Factory::setNull(int x) { factory[x] = nullptr; };
void Factory::removeFront() { factory[0] = nullptr; }
std::vector<std::shared_ptr<Tile>>
Factory::removeAllSameColour(Colour tileCode) {
  std::vector<std::shared_ptr<Tile>> tiles{};
  int counter = 0;
  for (int i = 0; i < FACTORYLENGTH; i++) {
    if (factory[i]->getTileColour() == tileCode) {
      tiles.push_back(factory[i]);
      counter++;
      factory[i] = nullptr;
    }
  }
  return tiles;
};
void Factory::insert(std::shared_ptr<Tile> tile) {
  int i = 0;
  while (i < FACTORYLENGTH) {
    if (factory[i] == nullptr) {
      factory[i] = tile;
      i = 5;
    }
    i++;
  }
}

int Factory::getSize() { return FACTORYLENGTH; };

std::shared_ptr<Tile> Factory::getTile(int index) {
  return factory[index];
}