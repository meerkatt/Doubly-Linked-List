//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////
//               MP : Doubly Linked List : Student Test Cases               //
//                                                                          //
// Written By :                         Environment :                       //
// Date ......:                         Compiler ...:                       //
//////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//                             Framework Set-up                             //
//////////////////////////////////////////////////////////////////////////////
#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif
#include "catch.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                 Includes                                 //
//////////////////////////////////////////////////////////////////////////////
#include "doubly_linked_list.hpp"
#include "node.hpp"

//////////////////////////////////////////////////////////////////////////////
//                                Test Cases                                //
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////

TEST_CASE("Testing Constructor", "[constructor]") {
  SECTION("Default Constructor") {
    DoublyLinkedList list;

    REQUIRE(list.size() == 0);
    REQUIRE(list.empty() == true);
  }
  SECTION("Parameterized Constructor Normal") {
    char x = 'x';
    DoublyLinkedList list(x);

    REQUIRE(list.getHead()->data == x);
    REQUIRE(list.getTail()->data == x);
    REQUIRE(list.size() == 1);
    REQUIRE(list.empty() == false);
  }
  SECTION("Parameterized Constructor List") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList list(values);

    REQUIRE(list.getHead()->data == '1');
    REQUIRE(list.getHead()->next->prev->data == '1');
    REQUIRE(list.getHead()->next->data == '2');
    REQUIRE(list.getHead()->next->next->prev->data == '2');
    REQUIRE(list.getHead()->next->next->data == '3');
    REQUIRE(list.getHead()->next->next->next->prev->data == '3');
    REQUIRE(list.getHead()->next->next->next->data == '4');

    REQUIRE(list.getTail()->data == '4');
    REQUIRE(list.size() == 4);
    REQUIRE(list.empty() == false);
  }
  SECTION("Parameterized Constructor List (Edge)") {
    std::vector<char> values;
    DoublyLinkedList list(values);
    REQUIRE(list.size() == 0);
    REQUIRE(list.empty() == true);
  }
  SECTION("Deep Copy  Constructor Base") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList list(values);
    DoublyLinkedList copy(list);
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
  }
  SECTION("Deep Copy Constructor Edge") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList list(values);
    DoublyLinkedList copy(list);
    copy.getHead()->data = 2;
    copy.getTail()->data = 3;
    REQUIRE(copy.getHead()->data != list.getHead()->data);
    REQUIRE(copy.getTail()->data != list.getTail()->data);
  }
}

TEST_CASE("Testing Assignment Operator", "[operator]") {
  SECTION("Deep Copy Assignment Empty") {
    std::vector<char> values;
    DoublyLinkedList list(values);
    DoublyLinkedList copy = list;
    REQUIRE(copy.getHead() == nullptr);
    REQUIRE(copy.getTail() == nullptr);
  }
  SECTION("Deep Copy Assignment Base") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList list(values);
    DoublyLinkedList copy = list;
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
    copy.getHead()->data = 2;
    copy.getTail()->data = 3;
    REQUIRE(copy.getHead()->data != list.getHead()->data);
    REQUIRE(copy.getTail()->data != list.getTail()->data);
  }
  SECTION("Deep Copy Assignment Edge 1") {
    std::vector<char> values;
    values.push_back('1');
    DoublyLinkedList list(values);
    DoublyLinkedList copy = list;
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
  }
  SECTION("Deep Copy Assignment Edge 2") {
    std::vector<char> values;
    values.push_back('1');
    DoublyLinkedList list(values);
    values.push_back('2');
    DoublyLinkedList copy(values);
    copy = list;
    REQUIRE(copy.getHead()->data == list.getHead()->data);
    REQUIRE(copy.getTail()->data == list.getTail()->data);
  }
}

TEST_CASE("push_back", "[push_back]") {
  SECTION("Empty") {
    DoublyLinkedList list;
    list.push_back('a');
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'a');
    REQUIRE(list.size() == 1);
  }
  SECTION("base") {
    DoublyLinkedList list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');

    REQUIRE(list.size() == 4);
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'd');
  }
}

TEST_CASE("push_front", "[push_front]") {
  SECTION("Empty") {
    DoublyLinkedList list;
    list.push_front('a');
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'a');
    REQUIRE(list.size() == 1);
  }
  SECTION("base") {
    DoublyLinkedList list;
    list.push_front('a');
    list.push_front('b');
    list.push_front('c');
    list.push_front('d');

    REQUIRE(list.size() == 4);
    REQUIRE(list.getHead()->data == 'd');
    REQUIRE(list.getTail()->data == 'a');
  }
}

TEST_CASE("pop_back", "[push_back]") {
  SECTION("Empty") {
    DoublyLinkedList list;
    REQUIRE_THROWS_AS(list.pop_back(), std::runtime_error);
  }
  SECTION("base") {
    DoublyLinkedList list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');
    list.pop_back();

    REQUIRE(list.size() == 3);
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'c');
  }
  SECTION("multiple") {
    DoublyLinkedList list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');
    list.pop_back();
    list.pop_back();

    REQUIRE(list.size() == 2);
    REQUIRE(list.getHead()->data == 'a');
    REQUIRE(list.getTail()->data == 'b');
  }
  SECTION("Edge 1") {
    DoublyLinkedList list;
    list.push_back('a');
    list.push_back('b');
    list.push_back('c');
    list.push_back('d');
    list.pop_back();
    list.pop_back();
    list.pop_back();

    REQUIRE(list.size() == 1);
    REQUIRE(list.getHead() == list.getTail());
  }
  SECTION("Edge 2") {
    DoublyLinkedList list;
    list.push_back('a');
    list.pop_back();
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
    REQUIRE(list.size() == 0);
  }
}

TEST_CASE("insert_at", "[insert]") {
  SECTION("Empty") {
    DoublyLinkedList list;
    list.insert_at(0, 'x');
    REQUIRE(list.getHead()->data == 'x');
    REQUIRE(list.getTail()->data == 'x');
  }
  SECTION("base") {
    DoublyLinkedList list;
    list.insert_at(0, 'x');
    list.insert_at(1, 'y');
    REQUIRE(list.getHead()->data == 'x');
    REQUIRE(list.getTail()->data == 'y');
    REQUIRE(list.size() == 2);
  }
  SECTION("base 2") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList list(values);
    list.insert_at(1, 'x');
    REQUIRE(list.size() == 5);
    REQUIRE(list.getHead()->data == '1');
    REQUIRE(list.getTail()->data == '4');
    REQUIRE(list.getHead()->next->data == 'x');
  }
}

TEST_CASE("erase_at", "[erase]") {
  SECTION("Empty") {
    DoublyLinkedList list;
    REQUIRE_THROWS_AS(list.erase_at(0), std::runtime_error);
  }
  SECTION("base") {
    DoublyLinkedList list;
    list.insert_at(0, 'x');
    list.erase_at(0);
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
    REQUIRE(list.size() == 0);
  }
  SECTION("base 2") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList list(values);
    list.erase_at(1);
    REQUIRE(list.size() == 3);
    REQUIRE(list.getHead()->data == '1');
    REQUIRE(list.getTail()->data == '4');
    REQUIRE(list.getHead()->next->data == '3');
  }
}

TEST_CASE("clear", "[clear]") {
  SECTION("Empty") {
    DoublyLinkedList list;
    list.clear();
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
  }
  SECTION("base") {
    std::vector<char> values;
    values.push_back('1');
    values.push_back('2');
    values.push_back('3');
    values.push_back('4');
    DoublyLinkedList list(values);
    list.clear();
    REQUIRE(list.size() == 0);
    REQUIRE(list.getHead() == nullptr);
    REQUIRE(list.getTail() == nullptr);
  }
}
