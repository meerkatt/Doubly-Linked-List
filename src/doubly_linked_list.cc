#include <iomanip>
#include <sstream>
#include <stdexcept>
using std::endl;
using std::ostream;
using std::ostringstream;
using std::setfill;
using std::setw;
using std::string;

#include "doubly_linked_list.hpp"

DoublyLinkedList::DoublyLinkedList(char val) {
  Node* first = new Node(val);
  head_ = tail_ = first;
  ++size_;
}

DoublyLinkedList::DoublyLinkedList(const std::vector<char>& values) {
  if (values.size() <= 0) {
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  Node* curr = new Node(values.at(0));
  head_ = curr;
  ++size_;

  for (size_t idx = 1; idx < values.size(); ++idx) {
    Node* temp = new Node(values.at(idx));
    curr->next = temp;
    curr->next->prev = curr;
    ++size_;
    curr = curr->next;
  }
  tail_ = curr;
}

DoublyLinkedList::DoublyLinkedList(const DoublyLinkedList& rhs) {
  if (rhs.getHead() == nullptr) {
    size_ = 0;
    head_ = nullptr;
    tail_ = nullptr;
    return;
  }
  Node* curr = new Node(rhs.getHead()->data);
  Node* rhs_temp = rhs.getHead()->next;
  head_ = curr;
  ++size_;

  for (size_t idx = 1; idx < rhs.size(); ++idx) {
    Node* temp = new Node(rhs_temp->data);
    curr->next = temp;
    curr->next->prev = curr;
    ++size_;
    curr = curr->next;
    rhs_temp = rhs_temp->next;
  }
  tail_ = curr;
}

DoublyLinkedList::~DoublyLinkedList() { clear(); }

void DoublyLinkedList::push_back(char val) {
  Node* temp = new Node(val);
  if (tail_ == nullptr) {
    tail_ = head_ = temp;
    ++size_;
    return;
  }
  tail_->next = temp;
  temp->prev = tail_;
  tail_ = temp;
  ++size_;
}
void DoublyLinkedList::push_front(char val) {
  Node* temp = new Node(val);
  if (head_ == nullptr) {
    head_ = tail_ = temp;
    ++size_;
    return;
  }
  head_->prev = temp;
  temp->next = head_;
  head_ = temp;
  ++size_;
}

void DoublyLinkedList::pop_back() {
  if (head_ == nullptr) {
    throw std::runtime_error("empty list");
  }
  if (tail_->prev == nullptr) {
    delete tail_;
    head_ = tail_ = nullptr;
    --size_;
    return;
  }
  Node* curr = tail_->prev;
  delete tail_;
  curr->next = nullptr;
  tail_ = curr;
  --size_;
}

void DoublyLinkedList::pop_front() {
  if (head_ == nullptr) {
    throw std::runtime_error("empty list");
  }
  if (head_->next == nullptr) {
    delete head_;
    head_ = tail_ = nullptr;
    --size_;
    return;
  }
  Node* curr = head_->next;
  delete head_;
  curr->prev = nullptr;
  head_ = curr;
  --size_;
}

void DoublyLinkedList::clear() {
  if (head_ == nullptr) {
    return;
  }
  while (head_ != tail_) {
    pop_front();
  }
  pop_front();
}

char& DoublyLinkedList::find(char val) {
  if (head_ == nullptr) {
    throw std::runtime_error("Not Found");
  }
  Node* curr = head_;
  while (curr->data != val) {
    if (curr->next == nullptr || curr == nullptr) {
      throw std::runtime_error("Not Found");
    }
    curr = curr->next;
  }
  char& c = curr->data;
  return c;
}

void DoublyLinkedList::insert_at(size_t idx, char val) {
  if (idx > size_) {
    throw std::runtime_error("invalid index");
  } else if (idx == size_) {
    push_back(val);
    return;
  } else if (idx == 0) {
    push_front(val);
    return;
  }
  size_t count = 1;
  Node* curr = head_;
  while (count < idx) {
    curr = curr->next;
    ++count;
  }
  Node* temp = curr->next;
  curr->next = new Node(val);
  curr->next->prev = curr;
  curr = curr->next;
  curr->next = temp;
  temp->prev = curr;
  ++size_;
}
void DoublyLinkedList::erase_at(size_t idx) {
  if (idx >= size_) {
    throw std::runtime_error("invalid index");
  } else if (idx == size_ - 1) {
    pop_back();
    return;
  } else if (idx == 0) {
    pop_front();
    return;
  }
  size_t count = 1;
  Node* curr = head_;
  while (count < idx) {
    curr = curr->next;
    ++count;
  }
  Node* temp = curr->next;
  curr->next = temp->next;
  temp->next->prev = curr;
  delete temp;
  temp = nullptr;
  --size_;
}

char& DoublyLinkedList::back() {
  if (tail_ == nullptr) {
    throw std::runtime_error("Not Found");
  }
  char& c = tail_->data;
  return c;
}
char& DoublyLinkedList::front() {
  if (head_ == nullptr) {
    throw std::runtime_error("Not Found");
  }
  char& c = head_->data;
  return c;
}

Node* DoublyLinkedList::getHead() const { return head_; }
Node* DoublyLinkedList::getTail() const { return tail_; }

void DoublyLinkedList::setHead(Node* head) { head_ = head; }
void DoublyLinkedList::setTail(Node* tail) { tail_ = tail; }
void DoublyLinkedList::setSize(size_t size) { size_ = size; }

DoublyLinkedList& DoublyLinkedList::operator=(const DoublyLinkedList& rhs) {
  if (this->head_ == rhs.getHead()) {
    return *this;
  }

  clear();
  if (rhs.empty()) {
    return *this;
  }
  Node* curr = rhs.getHead();

  while (curr->next) {
    this->push_back(curr->data);
    curr = curr->next;
  }
  this->push_back(curr->data);
  return *this;
  /*
  DoublyLinkedList assignment(rhs);
  Node* curr = head_;
  Node* rhs_temp = rhs.getHead();
  head_->data = rhs_temp->data;
  size_t count = 1;
  while (rhs_temp->next) {
    if (size_ > count) {
      curr = curr->next;
      rhs_temp = rhs_temp->next;
      curr->data = rhs_temp->data;
    }
    if (size_ <= count) {
      ++size_;
      rhs_temp = rhs_temp->next;
      curr->next->prev = curr;
      curr = curr->next;
      curr->data = rhs_temp->data;
    }
    ++count;
  }
  tail_ = curr;
  size_ = count;
  */
}

// Functions provided to you
ostream& operator<<(ostream& os, const DoublyLinkedList& ll) {
  constexpr unsigned int width = 16;
  os << "Doubly Linked List" << endl;
  os << "Head: " << ll.head_ << "\t Tail: " << ll.tail_ << endl;
  os << "Size: " << ll.size_ << endl;
  if (ll.head_ == nullptr) return (os << "Empty" << endl);
  const Node* curr = ll.head_;
  os << "Nodes (accessible from head to tail):" << endl << endl;
  os << setw(width) << setfill(' ') << ' ' << ' ' << center("prev", width - 1)
     << ' ' << center("data", width - 1) << ' ' << center("next", width - 1)
     << endl;
  while (curr != nullptr) {
    ostringstream oss;
    oss << (curr->prev);
    string prev = oss.str();
    oss.str("");
    oss << (curr->next);
    string next = oss.str();
    oss.str("");
    oss << (curr->data);
    string data = oss.str();
    oss.str("");
    oss << curr;
    string address = oss.str();
    os << setw(width) << setfill(' ') << ' ' << '.' << setw(width)
       << setfill('-') << '.' << setw(width) << '.' << setw(width) << '.'
       << endl;
    os << setw(width) << setfill(' ') << center(address, width - 1) << '|'
       << setw(width - 1) << setfill(' ') << center(prev, width - 1) << '|'
       << setw(width - 1) << center(data, width - 1) << '|' << setw(width - 1)
       << center(next, width - 1) << '|' << endl;
    os << setw(width) << setfill(' ') << ' ' << '\'' << setw(width)
       << setfill('-') << '\'' << setw(width) << '\'' << setw(width) << '\''
       << endl;
    os << endl;
    curr = curr->next;
  }
  return os;
}

std::string center(const std::string& str, decltype(str.length()) col_width) {
  // quick and easy (but error-prone) implementation
  decltype(str.length()) padl = (col_width - str.length()) / 2;
  decltype(str.length()) padr = (col_width - str.length()) - padl;
  string strf = string(padl, ' ') + str + string(padr, ' ');
  return strf;
}