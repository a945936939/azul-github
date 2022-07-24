#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "Tile.h"
#include <memory>
class Node {
public:
  Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next);
  std::shared_ptr<Node> next;
  std::shared_ptr<Tile> tile;
};
class LinkedList {

  std::shared_ptr<Node> head;
  std::shared_ptr<Node> tail;

public:
  LinkedList();
  ~LinkedList();
  bool isEmpty();
  void addBack(std::shared_ptr<Tile> tile);
  std::shared_ptr<Tile> getFrontNodeCopy();
  void removeFront();

  void clear();
};
#endif
