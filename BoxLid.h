#ifndef BOX_LID_H
#define BOX_LID_H
#include "LinkedList.h"
#include "Tile.h"
#include <memory>
#include <vector>

class BoxLid {

public:
  BoxLid();
  ~BoxLid();
  BoxLid(BoxLid& other);

  int getSize();
  std::shared_ptr<Tile> getTile(int index);

  void addBackTile(std::shared_ptr<Tile> tile);

  std::shared_ptr<Tile> takeFrontTile();

private:
  std::shared_ptr<LinkedList> boxLid;
};
#endif // TILE_BAG_H
