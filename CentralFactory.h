#ifndef CENTRALFACTORY_H
#define CENTRALFACTORY_H

#include "Tile.h"
#include <vector>
#include <memory>
class CentralFactory {

public:
  CentralFactory();
  CentralFactory(CentralFactory& other);
  // ~CentralFactory();
  bool isEmpty();
  void addTile(std::shared_ptr<Tile> tile);
  void removeFront();
  int getSize();
  // return a number of how many tiles u took from the centralFactory
  int takeTiles(std::shared_ptr<Tile> tile);
  void clear();
  std::shared_ptr<Tile> getTile(int i);
  std::vector<std::shared_ptr<Tile>> removeAllSameColour(Colour tileCode);

private:
  std::vector<std::shared_ptr<Tile>> factory;
};
#endif
