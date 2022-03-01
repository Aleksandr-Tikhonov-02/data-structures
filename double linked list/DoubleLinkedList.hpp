#ifndef _DOUBLELINKEDLIST_
#define _DOUBLELINKEDLIST_
#include <iostream>

class DoubleLinkedList
{
private:
  struct Node
  {
    int item_;
    Node* next_;
    Node* prev_;

    Node(int item, Node* next = nullptr, Node* prev = nullptr) : item_(item), next_(next), prev_(prev) { }
  };
  int count_;
  Node* head_;
  Node* tail_;
  Node* head() const { return head_; }
  Node* tail() const { return tail_; }
  void insertTail(Node* x);
  void insertHead(Node* x);
  void deleteNode(Node* x);
  Node* searchNode(int item);
  Node* replaceNode(Node* x, int item);

public:
  DoubleLinkedList() : count_(0), head_(nullptr), tail_(nullptr) {  }
  DoubleLinkedList(const DoubleLinkedList& src);
  void swap(DoubleLinkedList& list);
  DoubleLinkedList& operator = (const DoubleLinkedList& list);
  DoubleLinkedList(DoubleLinkedList&& src) noexcept;
  DoubleLinkedList& operator=(DoubleLinkedList&& src) noexcept;

  int getCount()const { return count_; };
  int headItem() const;
  int& headItem();
  int tailItem() const;
  int& tailItem();
  void insertHead(int item);
  void insertTail(int item);
  bool deleteHead();
  bool deleteTail();
  bool deleteItem(const int item, bool all);
  bool searchItem(int item);
  bool replaceItem(int itemOld, int itemNew, bool all);
  void outAll();
  bool operator ==(DoubleLinkedList& list);
  DoubleLinkedList& addList(DoubleLinkedList& list);
  friend std::ostream& operator <<(std::ostream& stream, DoubleLinkedList& list);
  virtual ~DoubleLinkedList();
};
#endif

