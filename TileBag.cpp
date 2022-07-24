#include "TileBag.h"
#include <iostream>
TileBag::TileBag() {}

// TileBag::TileBag(TileBag& other) { tileBag = new LinkedList(*other.tileBag);
// }

/*
 *Adding tiles into tilebag in the last position.
 */
void TileBag::addBackTile(std::shared_ptr<Tile> tile) {
  this->tileBag.push_back(tile);
}
/*
 *Initialize tilebag, adding tiles into List.
 */
void TileBag::addBackTile(char tile) {

  if (tile == 'R') {
    std::shared_ptr<Tile> tiles = std::make_shared<Tile>(R);
    addBackTile(tiles);
  }
  if (tile == 'B') {
    std::shared_ptr<Tile> tiles = std::make_shared<Tile>(B);
    addBackTile(tiles);
  }
  if (tile == 'L') {
    std::shared_ptr<Tile> tiles = std::make_shared<Tile>(L);
    addBackTile(tiles);
  }
  if (tile == 'U') {
    std::shared_ptr<Tile> tiles = std::make_shared<Tile>(U);
    addBackTile(tiles);
  }
  if (tile == 'Y') {
    std::shared_ptr<Tile> tiles = std::make_shared<Tile>(Y);
    addBackTile(tiles);
  }
  if (tile == 'O') {
    std::shared_ptr<Tile> tiles = std::make_shared<Tile>(O);
    addBackTile(tiles);
  }
}
std::shared_ptr<Tile> TileBag::takeFrontTile() {
  std::shared_ptr<Tile> tile = nullptr;
  tile = this->tileBag.front();
  tileBag.front() = nullptr;
  tileBag.erase(tileBag.begin());
  return tile;
}
bool TileBag::checkBagEmpty() {
  bool result = true;
  if (tileBag.empty()) {
    result = true;
  } else {
    result = false;
  }
  return result;
}
TileBag::~TileBag() {}
std::shared_ptr<Tile> TileBag::getTile(int index) { return tileBag.at(index); }
void TileBag::setTileNull(int index) { tileBag.at(index) = nullptr; }
