#include "Board.h"
#include <iostream>

Board::Board(const int mosaicLineNum, const int brokenLineNum) {
  // std::shared_ptr<Tile> tmp[5][5];
  patternLine = new std::shared_ptr<Tile>*[mosaicLineNum];
  wall = new std::shared_ptr<Tile>*[mosaicLineNum];

  for (int i = 0; i < mosaicLineNum; i++) {
    patternLine[i] = new std::shared_ptr<Tile>[i + 1];
  }

  for (int i = 0; i < mosaicLineNum; i++) {
    wall[i] = new std::shared_ptr<Tile>[mosaicLineNum];
  }

  broken = new std::shared_ptr<Tile>[brokenLineNum];
  this->lineNum = mosaicLineNum;
  this->brokenLineNum = brokenLineNum;
};
Board::~Board() {

  for (int i = 0; i < this->lineNum; i++) {
    delete[] patternLine[i];
  }
  for (int a = 0; a < this->lineNum; a++) {

    delete[] wall[a];
  }

  // delete patternLine;
  // delete wall;
  delete[] patternLine;
  delete[] wall;
  delete[] broken;
}

/*
 *This method is for checking if tile exist current row on wall,
 *if not, return true .
 */
bool Board::canPushTileToPatternLine(int lineNum, Colour colour,
                                     int mosaicLineNum) {
  bool result = true;
  // if the patternline is empty
  if (patternLine[lineNum - 1][0] == nullptr) {

    for (int i = 0; i < mosaicLineNum; i++) {
      // checking horizontal
      if (wall[lineNum - 1][i] != nullptr) {
        if (wall[lineNum - 1][i]->getTileColour() == colour) {
          result = false;
          i = mosaicLineNum;
        }
      }
    }

  }
  // if the patternline is not empty
  else if (patternLine[lineNum - 1][0]->getTileColour() == colour) {
    result = true;

  } else {

    result = false;
  }
  return result;
}

char Board::printWallTile(int a, int b) {
  char tmp = 'R';
  if (wall[a][b] == nullptr) {
    tmp = '.';
  } else {
    Colour colour = wall[a][b]->getTileColour();

    if (colour == B) {
      tmp = 'B';
    } else if (colour == Y) {
      tmp = 'Y';
    } else if (colour == R) {
      tmp = 'R';
    } else if (colour == U) {
      tmp = 'U';
    } else if (colour == L) {
      tmp = 'L';
    } else if (colour == F) {
      tmp = 'F';
    } else if (colour == O) {
      tmp = 'O';
    }
  }
  return tmp;
};
void Board::setWallTile(int a, int b, std::shared_ptr<Tile> tile) {
  wall[a][b] = tile;
};
void Board::setPatternLineTile(int storageRow, int i,
                               std::shared_ptr<Tile> tile) {
  if (patternLine[storageRow][i] == nullptr) {
  }
  patternLine[storageRow][i] = tile;
};

char Board::printPatternLineTile(int a, int c) {

  char result = 'B';
  if (patternLine[a][c] == nullptr) {
    result = '.';

  } else {
    Colour tmp = patternLine[a][c]->getTileColour();
    if (tmp == B) {
      result = 'B';
    } else if (tmp == Y) {
      result = 'Y';
    } else if (tmp == R) {
      result = 'R';
    } else if (tmp == U) {
      result = 'U';
    } else if (tmp == L) {
      result = 'L';
    } else if (tmp == F) {
      result = 'F';
    } else if (tmp == O) {
      result = 'O';
    }
  }
  return result;
}

char Board::printBrokenLineTile(int i) {
  char result = 'B';
  if (broken[i] == nullptr) {
    result = ' ';

  } else {
    Colour tmp = broken[i]->getTileColour();
    if (tmp == B) {
      result = 'B';
    } else if (tmp == Y) {
      result = 'Y';
    } else if (tmp == R) {
      result = 'R';
    } else if (tmp == U) {
      result = 'U';
    } else if (tmp == L) {
      result = 'L';
    } else if (tmp == F) {
      result = 'F';
    } else if (tmp == O) {
      result = 'O';
    }
  }
  return result;
}
void Board::setBrokenLineTile(int i, std::shared_ptr<Tile> tile) {
  broken[i] = tile;
};

int Board::getNumOfEmptySpaceOnRow(int rowNumber) {
  int numOfEmptySpaceOnRow = 0;

  for (int b = 0; b < rowNumber; b++) {
    if (patternLine[rowNumber - 1][b] == nullptr) {
      numOfEmptySpaceOnRow++;
    }
  }

  return numOfEmptySpaceOnRow;
}
Colour Board::getColorOfTileOnRow(int rowNumber) {

  Colour tmp = patternLine[rowNumber - 1][0]->getTileColour();

  return tmp;
}

bool Board::shouldPushLine(int LineNum) {
  bool result = true;
  if (printPatternLineTile(LineNum, LineNum) != '.') {
    result = true;
  } else {
    result = false;
  }
  return result;
};
/*
 *This method pushs tile to exact point on wall.
 *First make sure no empty space on current row on patterline
 *Then take the colour and make new tile to the wall,and set nullptr
 *to first element of current row on patterline.
 */
void Board::pushOneLineIntoWall(int storageRow, int wallNum) {
  std::shared_ptr<Tile> returnTile = nullptr;
  returnTile = this->patternLine[storageRow][0];
  wall[storageRow][wallNum - 1] = returnTile;
  this->patternLine[storageRow][0] = nullptr;
}
void Board::pushOneLineIntoWall(int lineNum) {
  std::shared_ptr<Tile> returnTile = nullptr;

  if (this->patternLine[lineNum][lineNum] != nullptr) {
    if (this->patternLine[lineNum][0]->getTileColour() == R) {

      returnTile = this->patternLine[lineNum][0];
      this->patternLine[lineNum][0] = nullptr;
      this->wall[lineNum][(lineNum + 2) % 5] = returnTile;
    }

    else if (this->patternLine[lineNum][0]->getTileColour() == Y) {

      returnTile = this->patternLine[lineNum][0];
      this->patternLine[lineNum][0] = nullptr;
      this->wall[lineNum][(lineNum + 1) % 5] = returnTile;
    } else if (this->patternLine[lineNum][0]->getTileColour() == B) {

      returnTile = this->patternLine[lineNum][0];

      this->patternLine[lineNum][0] = nullptr;

      this->wall[lineNum][lineNum % 5] = returnTile;
    }

    else if (this->patternLine[lineNum][0]->getTileColour() == L) {

      returnTile = this->patternLine[lineNum][0];
      this->patternLine[lineNum][0] = nullptr;
      this->wall[lineNum][(lineNum + 4) % 5] = returnTile;
    } else if (this->patternLine[lineNum][0]->getTileColour() == U) {

      returnTile = this->patternLine[lineNum][0];
      this->patternLine[lineNum][0] = nullptr;
      this->wall[lineNum][(lineNum + 3) % 5] = returnTile;
    }
  }
}

std::vector<std::shared_ptr<Tile>> Board::getRestOfTiles(int mosaicNum) {
  std::vector<std::shared_ptr<Tile>> tiles{};
  for (int i = 0; i < LENGTH_OF_BROKEN; i++) {
    if (broken[i] != nullptr) {
      tiles.push_back(broken[i]);
      broken[i] = nullptr;
    }
  }

  for (int a = 0; a < mosaicNum; a++) {
    for (int b = 0; b < a + 1; b++) {
      if (patternLine[a][a] != nullptr) {
        if (patternLine[a][b] != nullptr) {

          std::shared_ptr<Tile> tmp = patternLine[a][b];
          tiles.push_back(tmp);
          patternLine[a][b] = nullptr;
        }
      }
    }
  }
  return tiles;
};

void Board::cleanBoard() {
  // clean patternLine
  for (int a = 0; a < 5; a++) {
    for (int b = 0; b < 5; b++) {
      while (patternLine[a][b] != nullptr) {

        patternLine[a][b] = nullptr;
      }
    }
  }
  // clean wall
  for (int a = 0; a < 5; a++) {
    for (int b = 0; b < a + 1; b++) {
      while (patternLine[a][b] != nullptr) {
        patternLine[a][b] = nullptr;
      }
    }
  }
};

std::shared_ptr<Tile> Board::getPatternLineTile(int a, int c) {
  return patternLine[a][c];
};
std::shared_ptr<Tile> Board::getBrokenLineTile(int i) { return broken[i]; };
std::shared_ptr<Tile> Board::getWallTile(int a, int b) { return wall[a][b]; };
