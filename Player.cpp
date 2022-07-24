#include "Player.h"
#include <iostream>
#include <vector>

Player::Player(std::string name, bool advanced) {
  this->name = name;
  this->score = 0;
  int mosaicLineNum = 5;
  int brokenLineNum = 7;
  if (advanced) {
    mosaicLineNum = 6;
    brokenLineNum = 8;
  }
  this->board = std::make_shared<Board>(mosaicLineNum, brokenLineNum);
}

char Player::printPatternLine(int a, int c) {
  return board->printPatternLineTile(a, c);
}
/*
 *This method is for checking if tiles on current row have same colour
 *and there is no empty space on this row, then it can be pushed.
 */
bool Player::canPushTileToPatternLine(int lineNum, Colour colour,
                                      int mosaicLineNum) {
  return board->canPushTileToPatternLine(lineNum, colour, mosaicLineNum);
}
/*
 *This method pushs tiles to patternline
 *First, get how many valid space on this row, and get which point should put
 *this method return number of tiles that will go to the broken line
 */
std::vector<std::shared_ptr<Tile>>
Player::pushTilesIntoPatternline(std::vector<std::shared_ptr<Tile>> tiles,
                                 int storageRow) {
  int size = tiles.size();
  if (size != 0) {
    int numOfEmptySpaceOnRow = this->board->getNumOfEmptySpaceOnRow(storageRow);
    if (size <= numOfEmptySpaceOnRow) {

      // storageRow - numOfEmptySpaceOnRow means starting which point
      for (int i = storageRow - numOfEmptySpaceOnRow;
           i < (storageRow - numOfEmptySpaceOnRow + size); i++) {

        board->setPatternLineTile(storageRow - 1, i, tiles.front());

        tiles.back() = nullptr;
        tiles.pop_back();
      }
    }
    if (numOfEmptySpaceOnRow == 0) {
      // numOfTilesGoToBroken = tiles.size();
    }
    if (size > numOfEmptySpaceOnRow && numOfEmptySpaceOnRow > 0) {
      for (int i = storageRow - numOfEmptySpaceOnRow; i < storageRow; i++) {
        board->setPatternLineTile(storageRow - 1, i, tiles.front());

        tiles.back() = nullptr;
        tiles.pop_back();
      }
    }
  }

  return tiles;
}
std::vector<std::shared_ptr<Tile>>
Player::pushRestOfTilesToBroken(std::vector<std::shared_ptr<Tile>> tiles,
                                int mosaicNum) {
  if (this->board->getBrokenLineTile(0) == nullptr) {
    int size = tiles.size();
    for (int i = 0; i < size; i++) {
      this->board->setBrokenLineTile(i, tiles.back());
      tiles.back() = nullptr;
      tiles.pop_back();
    }
  } else {
    int size = tiles.size();

    int count = 0;
    for (int i = 0; i < mosaicNum + 1; i++) {
      if (this->board->getBrokenLineTile(i) != nullptr) {
        count++;
      }
    }
    for (int i = count; i < (count + size); i++) {
      this->board->setBrokenLineTile(i, tiles.back());
      tiles.back() = nullptr;
      tiles.pop_back();
    }
  }

  return tiles;
}

/*the calculation of the game.the basic logic is that:
check is there any tiles in the up and down direction. if there is, score +1.
And, we need to count the tile itself too, so no matter how many tiles counted
in the vertical/horizontal direction, we always need to count one more points
for the tile itself,just once.if two directions both have tiles, then count
twice(horizontal + vertical)

*/
void Player::calculateEachLine(int storageRow, int mosaicLineNum, int wallNum) {
  // std::shared_ptr<Tile>** wall = board->getWall();

  Colour colour = board->getPatternLineTile(storageRow, 0)->getTileColour();
  int index = 0;
  if (colour == B) {
    index = 0;
  } else if (colour == Y) {
    index = 1;
  } else if (colour == R) {
    index = 2;
  } else if (colour == U) {
    index = 3;
  } else if (colour == L) {
    index = 4;
  }
  int counterNorth = 1;
  int counterSouth = 1;
  int counterEast = 1;
  int counterWest = 1;
  int horizontal = 0;
  int vertical = 0;
  // down
  int positionNum = (index + storageRow) % mosaicLineNum;
  if (mosaicLineNum == 6) {
    positionNum = wallNum - 1;
  }
  while ((storageRow + counterSouth) < mosaicLineNum &&
         board->getWallTile(storageRow + counterSouth, positionNum) !=
             nullptr) {
    score++;
    counterSouth++;
    vertical = 1;
  }
  // up
  while ((storageRow - counterNorth) >= 0 &&
         board->getWallTile(storageRow - counterNorth, positionNum) !=
             nullptr) {
    vertical = 1;
    score++;
    counterNorth++;
  }

  // right
  while (((positionNum) + counterEast) < mosaicLineNum &&
         board->getWallTile(storageRow, positionNum + counterEast) !=

             nullptr) {
    horizontal = 1;
    score++;
    counterEast++;
  }
  // left

  while (((positionNum)-counterWest) >= 0 &&
         board->getWallTile(storageRow, positionNum - counterWest) !=

             nullptr) {
    horizontal = 1;
    score++;
    counterWest++;
  }

  score += horizontal + vertical;
  if (horizontal == 0 && vertical == 0) {
    score += 1;
  }
};
std::vector<std::shared_ptr<Tile>> Player::getRestOfTiles(int mosaicNum) {

  return this->board->getRestOfTiles(mosaicNum);
}
std::string Player::printScore() {

  std::string s;
  std::string a = std::to_string(this->score);
  s = "Player " + name + "scores: " + a;
  return s;
};

void Player::roundEnd() {
  for (int lineNum = 0; lineNum < 5; lineNum++) {
    if (this->board->shouldPushLine(lineNum)) {

      calculateEachLine(lineNum, 5, 0);
      this->board->pushOneLineIntoWall(lineNum);
    }
  }
  calculateBroken();
  if (score < 0) {
    score = 0;
  }
};

void Player::calculateBroken() {
  int i = 0;
  while (board->getBrokenLineTile(i) != nullptr) {
    if (i == 0 || i == 1) {

      score -= 1;
    }
    if (i == 2 || i == 3 || i == 4) {

      score -= 2;
    }
    if (i == 5 || i == 6) {

      score -= 3;
    }
    if (i == 7) {

      score -= 4;
    }
    i++;
  }
};
void Player::takeFToken(std::shared_ptr<Tile> tile) {
  this->board->setBrokenLineTile(0, tile);
};

std::shared_ptr<Board> Player::getBoard() { return this->board; }

std::string Player::getName() { return this->name; }
int Player::getSocre() { return this->score; }
void Player::setSocre(int i) { this->score = i; }
