#include "CentralFactory.h"
#include <iostream>
CentralFactory::CentralFactory() {}
bool CentralFactory::isEmpty() {
  bool result = true;
  if (factory.empty() || factory.back()->getTileColour() == F) {
    result = true;
  } else {
    result = false;
  }
  return result;
};
void CentralFactory::removeFront() {
  factory[0] = nullptr;
  factory.erase(factory.begin());
};

std::
    vector<std::shared_ptr<Tile>>
    /*
     *When player promote a tilecode, take all same tilecode in central factory
     */
    CentralFactory::removeAllSameColour(Colour tileCode) {
  std::vector<std::shared_ptr<Tile>> tiles{};
  int counter = 0;
  int f = factory.size();
  for (int i = 0; i < f; i++) {

    if (factory[i]->getTileColour() == tileCode) {
      tiles.push_back(factory[i]);
      factory[i] = nullptr;
      counter++;
    }
  }

  int i = 0;
  int s = factory.size();
  while (i < s) {

    if (factory[i] == nullptr) {
      factory.erase(factory.begin() + i);

      i--;
      s--;
    }
    i++;
  }

  return tiles;
};

void CentralFactory::addTile(std::shared_ptr<Tile> tile) {
  factory.push_back(tile);
};
int CentralFactory::takeTiles(std::shared_ptr<Tile> tile) {
  int counter = 0;
  int i = 0;
  int f = factory.size();

  for (int b = 0; b < f; b++) {
    if (factory[i] == tile) {
      factory.erase(factory.begin() + i);
      b++;
      counter++;
    } else {
      i++;
    }
  }
  return counter;
};
std::shared_ptr<Tile> CentralFactory::getTile(int i) {
  return this->factory[i];
};
int CentralFactory::getSize() {
  int counter = 0;
  int f = factory.size();

  counter = f;
  return counter;
}
void CentralFactory::clear(){

};
