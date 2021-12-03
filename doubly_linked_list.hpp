#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <cstdlib>  // provides definition for size_t, the maximum size of a theoretically possible object of any type
#include <iostream>
#include <string>
#include <vector>

#include "node.hpp"
#include "stdexcept"

class DoublyLinkedList {
public:
  DoublyLinkedList() = default;
  DoublyLinkedList(char val);
  explicit DoublyLinkedList(const std::vector<char>& values);
  DoublyLinkedList(const DoublyLinkedList& rhs);
  DoublyLinkedList& operator=(const DoublyLinkedList& rhs);
  ~DoublyLinkedList();

  Node* getHead() const;
  Node* getTail() const;
  void setHead(Node* head);
  void setTail(Node* tail);
  void setSize(size_t size);
  char& back();
  char& front();
  void pop_back();
  void pop_front();

  void push_back(char val);
  void push_front(char val);

  void insert_at(size_t idx, char val);
  void erase_at(size_t idx);

  char& find(char val);
  void clear();

  size_t size() const { return size_; }
  bool empty() const { return (head_ == nullptr); };

  friend std::ostream& operator<<(
      std::ostream& os,
      const DoublyLinkedList& ll);  // friend b/c we don't have iterators yet!

private:
  Node* head_ = nullptr;
  Node* tail_ = nullptr;
  size_t size_ = 0;
};

std::ostream& operator<<(std::ostream& os, const DoublyLinkedList& ll);
std::string center(const std::string& str, decltype(str.length()) col_width);

#endif