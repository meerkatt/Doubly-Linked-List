#include <iostream>
#include <stdexcept>
#include <vector>

#include "doubly_linked_list.hpp"

using namespace std;

int main() {
  std::vector<char> values;
  values.push_back('1');
  values.push_back('2');
  values.push_back('3');
  DoublyLinkedList list(values);
  values.push_back('2');
  DoublyLinkedList copy(values);
  copy = list;
  // REQUIRE(copy.getHead()->data == list.getHead()->data);
  // REQUIRE(copy.getTail()->data == list.getTail()->data);
  std::cout << copy.size() << std::endl;
  std::cout << copy.getHead()->data << std::endl;
  std::cout << copy.getTail()->data << std::endl;
}
