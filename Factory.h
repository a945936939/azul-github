#ifndef FACTORY_H
#define FACTORY_H
#define FACTORYLENGTH 4
#include "LinkedList.h"
#include "Tile.h"
#include <vector>

class Factory {

public:
  Factory();
  Factory(Factory& other);
  ~Factory();

  int getSize();
  void setNull(int x);
  std::shared_ptr<Tile> getTile(int index);
  void removeFront();
  bool isEmpty();
  void insert(std::shared_ptr<Tile> tile);
  std::vector<std::shared_ptr<Tile>> removeAllSameColour(Colour tileCode);
  void clear();

private:
  std::shared_ptr<Tile> factory[4];
};
#endif
