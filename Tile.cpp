#include <iostream>

#include <string>

#include "Tile.h"

Tile::Tile() {}

Tile::Tile(Colour colour) { this->colour = colour; }
Colour Tile::getTileColour() { return this->colour; }
std::string Tile::getTileColourString() {
  std::string i = "S";
  if (getTileColour() == R) {
    i = "R";
  } else if (getTileColour() == B) {
    i = "B";
  } else if (getTileColour() == L) {
    i = "L";
  } else if (getTileColour() == U) {
    i = "U";
  } else if (getTileColour() == Y) {
    i = "Y";
  } else if (getTileColour() == O) {
    i = "O";
  }

  return i;
}
