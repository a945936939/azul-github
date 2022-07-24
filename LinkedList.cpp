#include "LinkedList.h"
#include <iostream>
Node::Node(std::shared_ptr<Tile> tile, std::shared_ptr<Node> next) {
  this->tile = tile;
  this->next = next;
}

LinkedList::LinkedList() {

  head = nullptr;
  tail = nullptr;
}
LinkedList::~LinkedList() { clear(); }
/*
 *If list is null, should  adding new Node into List
 */
bool LinkedList::isEmpty() {
  bool result = true;
  if (head == nullptr && tail == nullptr) {
    result = true;
  } else {
    result = false;
  }
  return result;
}
void LinkedList::clear() { head = nullptr; }
/*
 *Adding new Node to tail.
 */
void LinkedList::addBack(std::shared_ptr<Tile> tile) {
  //
  if (isEmpty()) {
    std::shared_ptr<Node> tmp = std::make_shared<Node>(tile, nullptr);
    head = tmp;
    tail = tmp;
  } else {
    std::shared_ptr<Node> tmp = std::make_shared<Node>(tile, nullptr);
    tail->next = tmp;
    tail = tmp;
  }
}
std::shared_ptr<Tile> LinkedList::getFrontNodeCopy() { return head->tile; }

void LinkedList::removeFront() {
  if (!isEmpty()) {
    head = head->next;
  }
}
