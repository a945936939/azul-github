#ifndef TILE_H
#define TILE_H
#include <string>
enum Colour { B, Y, R, U, L, O, F };
class Tile {
public:
  Tile();
  Tile(Colour colour);

  Colour getTileColour();
  std::string getTileColourString();
  Colour copyTile(Tile tile);

private:
  Colour colour;
};
#endif