#include "DoubleLinkedList.hpp"

void DoubleLinkedList::insertTail(Node* x)
{
  x->prev_ = tail_;
  if (tail_ != nullptr) {
    tail_->next_ = x;
  }
  else {
    head_ = x;
  }
  tail_ = x;
  count_++;
}
void DoubleLinkedList::insertHead(Node* x)
{
  x->next_ = head_;
  if (head_ != nullptr) {
    head_->prev_ = x;
  }
  else {
    tail_ = x;
  }
  head_ = x;
  count_++;
}
void DoubleLinkedList::deleteNode(Node* x)
{
  if (x == nullptr) {
    throw ("DoubleLinkedList::deleteNode  - неверно задан адрес удаляемого узла");
  }
  if (x->prev_ != nullptr) {
    // удаляется НЕ голова списка
    (x->prev_)->next_ = x->next_;
  }
  else {
    // удаляется голова списка,  второй элемент становится первым
    head_ = x->next_;
  }
  if (x->next_ != nullptr) {
    // удаляется НЕ хвост
    (x->next_)->prev_ = x->prev_;
  }
  else {
    // удаляется хвост
    tail_ = x->prev_;
  }
  delete x;      //
  count_--;     // число элементов списка уменьшилось
}
DoubleLinkedList::Node* DoubleLinkedList::searchNode(int item)
{
  Node* x = head_;
  while (x != nullptr && x->item_ != item) {
    x = x->next_;
  }
  return x;
}
DoubleLinkedList::Node* DoubleLinkedList::replaceNode(DoubleLinkedList::Node* x, int item)
{
  if (x == nullptr) {
    throw ("DoubleLinkedList::deleteNode  - неверно задан адрес удаляемого узла");
  }
  x->item_ = item;
  return x;
}
void DoubleLinkedList::swap(DoubleLinkedList& list)
{
  Node* tempHead = head_;
  Node* tempTail = tail_;
  this->head_ = list.head_;
  this->tail_ = list.tail_;
  list.head_ = tempHead;
  list.tail_ = tempTail;
}
DoubleLinkedList& DoubleLinkedList::operator=(const DoubleLinkedList& list)
{
  if (this == &list)
  {
    return *this;
  }
  DoubleLinkedList tempList(list);
  swap(tempList);
  this->count_ = list.getCount();
  return *this;
}
DoubleLinkedList::DoubleLinkedList(DoubleLinkedList&& src) noexcept
{
  this->count_ = src.count_;
  this->head_ = src.head_;
  this->tail_ = src.tail_;
  src.head_ = nullptr;
  src.tail_ = nullptr;
  src.count_ = 0;
}
DoubleLinkedList& DoubleLinkedList::operator=(DoubleLinkedList&& src) noexcept
{
  if (src == *this)
  {
    return *this;
  }

  swap(src);

  return *this;
}
DoubleLinkedList::DoubleLinkedList(const DoubleLinkedList& src) : DoubleLinkedList()
{
  Node* current = src.head_;
  for (int i = 0; i < src.getCount(); i++)
  {
    this->insertTail(current->item_);
    current = current->next_;
  }
  this->count_ = src.count_;
}
int DoubleLinkedList::headItem() const
{
  if (head_ != nullptr) {
    return head_->item_;
  }
  throw ("headItem - список пуст!");
}
int& DoubleLinkedList::headItem()
{
  if (head_ != nullptr) {
    return head_->item_;
  }
  throw ("headItem - список пуст!");
}
int DoubleLinkedList::tailItem() const
{
  if (tail_ != nullptr) {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}
int& DoubleLinkedList::tailItem()
{
  if (tail_ != nullptr) {
    return tail_->item_;
  }
  throw ("tailItem - список пуст!");
}
void DoubleLinkedList::insertHead(int item)
{
  insertHead(new Node(item));
}
void DoubleLinkedList::insertTail(int item)
{
  insertTail(new Node(item));
}
bool DoubleLinkedList::deleteHead()
{
  if (head_ == nullptr) {
    return 0;
  }
  deleteNode(head_);
  return 1;
}
bool DoubleLinkedList::deleteTail()
{
  if (tail_ == nullptr) {
    return 0;
  }
  deleteNode(tail_);
  return 1;
}
bool DoubleLinkedList::deleteItem(const int item, bool all)
{
  if (this->head_ == nullptr || this->head_->next_ == nullptr)
  {
    throw("список должен содержать как минимум 2 элемента");
  }
  Node* current = head_;
  Node* next = current->next_;
  int count = 0;
  while (next)
  {
    if (current->item_ == item)
    {
      deleteNode(current);
      current = next;
      next = next->next_;
      count++;
      if (!all)
      {
        break;
      }
    }
    else
    {
      current = current->next_;
      next = next->next_;
    }
  }
  if (current->item_ == item && !all && count == 0)
  {
    deleteNode(current);
  }
  if (current->item_ == item && all)
  {
    deleteNode(current);
  }
  return 0;
}
bool DoubleLinkedList::searchItem(int item)
{
  return (searchNode(item) != nullptr);
}
bool DoubleLinkedList::replaceItem(int itemOld, int itemNew, bool all)
{
  if (this->head_ == nullptr)
  {
    throw("список пуст");
  }
  Node* current = head_;
  while (current)
  {
    if (current->item_ == itemOld)
    {
      current->item_ = itemNew;
      if (!all)
      {
        break;
      }
    }
    current = current->next_;
  }
  return 0;
}
void DoubleLinkedList::outAll()
{
  Node* current = head_;
  while (current != nullptr) {
    std::cout << current->item_ << ' ';
    current = current->next_;
  }
  std::cout << std::endl;
}
bool DoubleLinkedList::operator==(DoubleLinkedList& list)
{
  if (this->count_ != list.count_)
  {
    return false;
  }
  Node* that = this->head_;
  Node* another = list.head_;
  while ((that != nullptr) || (another !=nullptr))
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
DoubleLinkedList& DoubleLinkedList::addList(DoubleLinkedList& list)
{

  DoubleLinkedList tmplist(list);
  this->count_ += list.getCount();
  this->tail_->next_ = tmplist.head_;
  tmplist.head_->prev_ = this->tail_;
  this->tail_ = tmplist.tail_;
  tmplist.head_ = nullptr;
  tmplist.tail_ = nullptr;
  tmplist.count_ = 0;
  return *this;
}
DoubleLinkedList::~DoubleLinkedList()
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
std::ostream& operator<<(std::ostream& stream, DoubleLinkedList& list)
{
  DoubleLinkedList::Node* current = list.head_;
  if (current == nullptr)
  {
    stream << "List is empty";
  }
  while (current != nullptr)
  {
    stream << current->item_ << " ";
    current = current->next_;;
  }
  return stream;
}
