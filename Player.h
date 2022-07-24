#ifndef PLAYER_H
#define PLAYER_H

#include "Board.h"
#include "Tile.h"
#include <iostream>
#include <memory>
#include <vector>

/*
 *This class represent a signg player.
 *The player contains socre and board, and some functions about
 *push tiles, calculate socres.
 */
class Player {
public:
  Player(std::string name, bool advanced);
  Player(Player& other);
  bool canPushTileToPatternLine(int lineNum, Colour colour, int mosaicLineNum);
  char printPatternLine(int a, int c);
  // mingyang wang part
  std::vector<std::shared_ptr<Tile>>
  pushTilesIntoPatternline(std::vector<std::shared_ptr<Tile>> tiles,
                           int storageRow);

  std::vector<std::shared_ptr<Tile>>
  pushRestOfTilesToBroken(std::vector<std::shared_ptr<Tile>> tiles,
                          int mosaicNum);

  // zhipeng part

  void calculateEachLine(int lineNum, int mosaicLineNum, int wallNum);
  void roundEnd();

  std::shared_ptr<Board> getBoard();

  std::string printScore();

  std::vector<std::shared_ptr<Tile>> getRestOfTiles(int mosaicNum);
  std::string getName();
  void takeFToken(std::shared_ptr<Tile> tile);
  void calculateBroken();
  int getSocre();
  void setSocre(int i);

private:
  std::string name;
  int score;
  std::shared_ptr<Board> board;
};
#endif
