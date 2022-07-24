#ifndef TILE_BAG_H
#define TILE_BAG_H
#include "LinkedList.h"
#include "Tile.h"
#include <memory>
#include <vector>

class TileBag {

public:
  TileBag();
  ~TileBag();
  TileBag(TileBag& other);
  bool checkBagEmpty();
  void shuffleBag();
  std::shared_ptr<Tile> getTile(int index);

  void addBackTile(std::shared_ptr<Tile> tile);
  void addBackTile(char tile);
  void setTileNull(int index);
  std::shared_ptr<Tile> takeFrontTile();

private:
  std::vector<std::shared_ptr<Tile>> tileBag;
};
#endif
