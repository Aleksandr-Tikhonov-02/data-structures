#include "SinglyLinkedOrderedList.h"


void SinglyLinkedOrderedList::deleteNode(SinglyLinkedOrderedList::Node* x)
{
    if (x == nullptr)
    {
        throw ("Неверно задан адрес удаляемого узла");
    }
    Node* current = head_;
    bool found = true;
    if (x == current)
    {
        head_ = current->next_;
    }
    while (found && current->next_ != nullptr)
    {
        if (current->next_ == x)
        {
            if (x->next_ != nullptr)
            {
                current->next_ = x->next_;
                found = false;
            }
            else
            {
                tail_ = current;
                tail_->next_ = nullptr;
                found = false;
            }
        }
        current = current->next_;
    }
    delete x;
    count_--;
}
void SinglyLinkedOrderedList::deleteNode(Node*& prev, Node*& curr)
{
    if (prev == nullptr && curr->next_ == nullptr)
    {
        delete curr;
        curr = nullptr;
        head_ = nullptr;
        tail_ = nullptr;
        count_--;
    }
    else if (prev == nullptr)
    {
        prev = curr;
        curr = curr->next_;
        delete prev;
        prev = nullptr;
        head_ = curr;
        count_--;
    }
    else if (curr->next_ == nullptr)
    {
        tail_ = prev;
        delete curr;
        curr = nullptr;
        prev->next_ = nullptr;
        count_--;
    }
    else
    {
        prev->next_ = curr->next_;
        delete curr;
        curr = prev->next_;
        count_--;
    }
}
void SinglyLinkedOrderedList::insertNodeAfter(SinglyLinkedOrderedList::Node* x, int key)
{
    if (count_ == 0)
    {
        Node* headNode = new Node(key);
        head_ = headNode;
        tail_ = headNode;
        count_++;
    }
    else if (x == nullptr)
    {
        Node* newNode = new Node(key, head_);
        head_ = newNode;
        count_++;
    }
    else if (key > tail_->item_)
    {
        Node* newNode = new Node(key, nullptr);
        tail_->next_ = newNode;
        tail_ = newNode;
        count_++;
    }
    else
    {
        Node* newNode = new Node(key, x->next_);
        x->next_ = newNode;
        count_++;
    }
}
SinglyLinkedOrderedList::Node* SinglyLinkedOrderedList::successorNode(int item) const
{
    if (head_ == nullptr)
    {
        return nullptr;
    }
    if (item >= tail_->item_)
    {
        return nullptr;
    }
    Node* current = head_;
    while (current != nullptr)
    {
        if (current->item_ > item)
        {
            return current;
        }
        current = current->next_;
    }
}
SinglyLinkedOrderedList::Node* SinglyLinkedOrderedList::predecessorNode(int item) const
{
    if (head_ == nullptr)
    {
        return nullptr;
    }
    if (item > tail_->item_)
    {
        return tail_;
    }
    if (item <= head_->item_)
    {
        return nullptr;
    }
    Node* previous = nullptr;
    Node* current = head_;
    while (current != nullptr)
    {
        if (current->item_ >= item && previous->item_ < item)
        {
            return previous;
        }
        previous = current;
        current = current->next_;
    }
}
SinglyLinkedOrderedList::Node* SinglyLinkedOrderedList::searchNode(int item)
{
    Node* current = head_;
    while (current != nullptr)
    {
        if (current->item_ == item)
        {
            return current;
        }
        current = current->next_;
    }
    return nullptr;
}
void SinglyLinkedOrderedList::insertTail(Node* x)
{
    if (tail_ != nullptr) 
    {
        tail_->next_ = x;
    }
    else 
    {
        head_ = x;
    }
    tail_ = x;
    count_++;
}
void SinglyLinkedOrderedList::swap(SinglyLinkedOrderedList& list)
{
    Node* tempHead = head_;
    Node* tempTail = tail_;
    this->head_ = list.head_;
    this->tail_ = list.tail_;
    list.head_ = tempHead;
    list.tail_ = tempTail;
}
SinglyLinkedOrderedList::SinglyLinkedOrderedList(const SinglyLinkedOrderedList& src)
{
    Node* current = src.head_;
    for (int i = 0; i < src.getCount(); i++)
    {
        this->insertTail(current->item_);
        current = current->next_;
    }
    this->count_ = src.count_;
}
SinglyLinkedOrderedList& SinglyLinkedOrderedList::operator=(const SinglyLinkedOrderedList& list)
{
    if (this == &list)
    {
        return *this;
    }
    SinglyLinkedOrderedList tempList(list);
    swap(tempList);
    this->count_ = list.getCount();
    return *this;
}
void SinglyLinkedOrderedList::insertTail(int item)
{
    insertTail(new Node(item));
}
bool SinglyLinkedOrderedList::insertItem(int item)
{
    if (searchItem(item))
    {
        return false;
    }
    insertNodeAfter(predecessorNode(item), item);
    return true;
}
bool SinglyLinkedOrderedList::deleteItem(int item)
{
    Node* current = head_;
    while (current != nullptr)
    {
        if (current->item_ == item)
        {
            deleteNode(current);
            return true;
        }
        current = current->next_;
    }
    return false;
}
bool SinglyLinkedOrderedList::searchItem(int item)
{
    return (searchNode(item) != nullptr);
}
bool SinglyLinkedOrderedList::operator==(SinglyLinkedOrderedList& list)
{
    if (this->count_ != list.count_)
    {
        return false;
    }
    Node* that = this->head_;
    Node* another = list.head_;
    while ((that != nullptr) && (another != nullptr))
    {
        if (that->item_ != another->item_)
        {
            return false;
        }
        that = that->next_;
        another = another->next_;
    }
    return true;
}
void SinglyLinkedOrderedList::orConnection(SinglyLinkedOrderedList& list)
{
    if (head_ == nullptr || list.head_ == nullptr)
    {
        return;
    }
    Node* previousThat = nullptr;
    Node* that = this->head_;
    Node* previousAnother = nullptr;
    Node* another = list.head_;
    while (that != nullptr && another != nullptr)
    {
        if (that->item_ < another->item_)
        {
            previousThat = that;
            that = that->next_;
        }
        else if ((that->item_ == another->item_))
        {
            list.deleteNode(previousAnother, another);
        }
        else
        {
            previousThat->next_ = new Node(another->item_, that);
            count_++;
            list.deleteNode(previousAnother, another);
        }
    }
}
void SinglyLinkedOrderedList::deleteLocatedInTheSecond(SinglyLinkedOrderedList& list)
{
    if (head_ == nullptr || list.head_ == nullptr)
    {
        return;
    }
    Node* previousThat = nullptr;
    Node* that = this->head_;
    Node* previousAnother = nullptr;
    Node* another = list.head_;
    while (that != nullptr && another != nullptr)
    {
        if (that->item_ < another->item_)
        {
            previousThat = that;
            that = that->next_;
        }
        if ((that->item_ == another->item_))
        {
            this->deleteNode(previousThat, that);
            list.deleteNode(previousAnother, another);
        }
        else
        {
            list.deleteNode(previousAnother, another);
        }
    }
}
void SinglyLinkedOrderedList::andConnection(SinglyLinkedOrderedList& list)
{
    if (head_ == nullptr || list.head_ == nullptr)
    {
        return;
    }
    Node* previousThat = nullptr;
    Node* that = this->head_;
    Node* previousAnother = nullptr;
    Node* another = list.head_;
    while (that != nullptr && another != nullptr)
    {
        if (that->item_ < another->item_)
        {
            this->deleteNode(previousThat, that);
        }
        else if (that->item_ > another->item_)
        {
            list.deleteNode(previousAnother, another);
        }
        else
        {
            if (that->next_ == nullptr)
            {
                list.deleteNode(previousAnother, another);
                return;
            }
            list.deleteNode(previousAnother, another);
            previousThat = that;
            that = that->next_;
        }
    }
}
SinglyLinkedOrderedList::~SinglyLinkedOrderedList()
{
    Node* current = nullptr;
    Node* next = head_;
    while (next != nullptr)
    {
        current = next;
        next = next->next_;
        delete current;
    }
}
std::ostream& operator<<(std::ostream& stream, SinglyLinkedOrderedList& list)
{
    SinglyLinkedOrderedList::Node* current = list.head_;
    if (current == nullptr)
    {
        stream << "List is empty";
    }
    while (current != nullptr)
    {
        stream << current->item_ << " ";
        current = current->next_;
    }
    return stream;
}


