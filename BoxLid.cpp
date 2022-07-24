#include "BoxLid.h"
#include <iostream>
BoxLid::BoxLid() { boxLid = std::make_shared<LinkedList>(); }

BoxLid::BoxLid(BoxLid& other) {}

BoxLid::~BoxLid() {}

/*
 *Adding tiles into tilebag in the last position.
 */
void BoxLid::addBackTile(std::shared_ptr<Tile> tile) {
  this->boxLid->addBack(tile);
}

std::shared_ptr<Tile> BoxLid::takeFrontTile() {
  std::shared_ptr<Tile> tile = nullptr;
  tile = this->boxLid->getFrontNodeCopy();
  this->boxLid->removeFront();

  return tile;
}
