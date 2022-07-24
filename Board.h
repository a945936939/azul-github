#ifndef BOARD_H
#define BOARD_H
#include "Factory.h"
#include <vector>

#define LENGTH_OF_BROKEN 7
class Board {

public:
  Board(int mosaicLineNum, int brokenLineNum);
  ~Board();
  void cleanBoard();
  std::vector<std::shared_ptr<Tile>> getRestOfTiles(int mosaicNum);
  int calculateEachLine(int patternLine);
  bool canPushTileToPatternLine(int lineNum, Colour colour, int mosaicLineNum);
  bool shouldPushLine(int LineNum);
  void pushOneLineIntoWall(int lineNum);
  void pushOneLineIntoWall(int lineNum, int wallNum);

  // printing the board
  char printPatternLineTile(int a, int c);
  char printBrokenLineTile(int i);
  char printWallTile(int a, int b);
  // change the board
  void setPatternLineTile(int storageRow, int i, std::shared_ptr<Tile> tile);
  void setBrokenLineTile(int i, std::shared_ptr<Tile> tile);
  void setWallTile(int a, int b, std::shared_ptr<Tile> tile);
  std::shared_ptr<Tile> getPatternLineTile(int a, int c);
  std::shared_ptr<Tile> getBrokenLineTile(int i);
  std::shared_ptr<Tile> getWallTile(int a, int b);
  int getNumOfEmptySpaceOnRow(int rowNumber);
  Colour getColorOfTileOnRow(int rowNumber);

private:
  int lineNum = 0;
  int brokenLineNum = 0;

  std::shared_ptr<Tile>** patternLine;
  std::shared_ptr<Tile>** wall;
  std::shared_ptr<Tile>* broken;
};

#endif
