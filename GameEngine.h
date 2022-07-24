#ifndef GAMEENGINE_H
#define GAMEENGINE_H
#include "BoxLid.h"
#include "CentralFactory.h"
#include "Factory.h"
#include "Player.h"
#include "TileBag.h"

#include <memory>

/*
 *This class controls most of the functionality of this game.
 *Take tiles from all factories and push rest of into central or broken.
 *For example,the rest of tiles after taken, and tiles out of space on current
 *row.
 */
class GameEngine {
public:
  GameEngine();
  ~GameEngine();

  std::vector<std::shared_ptr<Tile>> takeTilesFromFactories(Colour tileCode,
                                                            int factoryNum);
  std::vector<std::shared_ptr<Tile>>
  takeTilesFromCentralFactories(Colour tileCode);
  void putRestTilesIntoCentralFactory(int factoryNum);
  void putRestTilesIntoBroken(Colour colour);
  void takeTilesFromTileBagIntoFactories();
  void putRestTileIntoTilebag(std::shared_ptr<Player> player, int mosaicNum);
  void addTilesToTileBag(std::string tilesFromTxt);
  void addTilesToTileBag(bool advancedMode);
  void addTilesToBoxLid( std::shared_ptr<Tile> tile);

  void addFactory();
  bool factoriesNotEmpty();
  std::shared_ptr<Factory> getFactories(int i);
  std::shared_ptr<CentralFactory> getCentralFactories();
  std::string getTilesInTileBag();
  bool validateFactoriesInput(std::string factoryNum);
  bool validateColourCodeInput(int factoryNum, std::string colour,
                               bool advanced);
  bool validateStorageRowInput(int factoryNum, Colour colour,
                               std::string storageRowInput,
                               std::shared_ptr<Player> player,
                               int mosaicLineNum);
  bool validateWallNumInput(Colour colour, int storageRow,
                            std::shared_ptr<Player> player, int mosaicLineNum,
                            std::string wallNumInput);

  bool bagIsEmpty();
  void shuffleBag(int seed, bool random);
  void putRestTileIntoBoxLid(std::shared_ptr<Player> player, int mosaicNum);
  void takeTilesFromBoxLidIntoTileBag();

private:
  std::shared_ptr<Tile> first;
  std::shared_ptr<TileBag> tileBag;
  std::shared_ptr<BoxLid> boxLid;
  std::shared_ptr<Factory> factories[5];
  std::shared_ptr<CentralFactory> centralFactory;
  std::string tilesInTileBag;
};

#endif // UTILITY_H
