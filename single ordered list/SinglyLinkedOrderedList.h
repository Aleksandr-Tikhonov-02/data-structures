#ifndef _SINGLYLINKEDORDEREDLIST_
#define _SINGLYLINKEDORDEREDLIST_
#include <iostream>

class SinglyLinkedOrderedList
{
private:
    struct Node
    {
        int item_;
        Node* next_;
        explicit Node(int item, Node* next = nullptr) : item_(item), next_(next) { };
    };
    int count_;
    Node* head_;
    Node* tail_;
    void deleteNode(Node* x);
    void deleteNode(Node*& prev, Node*& curr);
    void insertNodeAfter(Node* x, int key);
    Node* searchNode(int item);
    void insertTail(Node* x);
    Node* maximum()const { return tail_; };
    Node* minimum()const { return head_; };
    Node* successorNode(int item)const;
    Node* predecessorNode(int item)const;
public:
    SinglyLinkedOrderedList() : count_(0), head_(nullptr), tail_(nullptr) {  }
    SinglyLinkedOrderedList(const SinglyLinkedOrderedList& src);
    void swap(SinglyLinkedOrderedList& list);
    SinglyLinkedOrderedList& operator = (const SinglyLinkedOrderedList& list);
    virtual ~SinglyLinkedOrderedList();

    int getCount()const { return count_; };
    void insertTail(int item);
    bool insertItem(int item);
    bool deleteItem(int item);
    bool searchItem(int item);
    void orConnection(SinglyLinkedOrderedList& list);
    void deleteLocatedInTheSecond(SinglyLinkedOrderedList& list);
    void andConnection(SinglyLinkedOrderedList& list);
    bool operator==(SinglyLinkedOrderedList& list);
    friend std::ostream& operator <<(std::ostream& stream, SinglyLinkedOrderedList& list);
};
#endif
