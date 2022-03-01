#ifndef __BINARY_SEARCH_TREE_H
#define __BINARY_SEARCH_TREE_H

#include <iostream>
#include <algorithm>
#include <vector>
#include "Stack.h"
#include "StackArray.h"

template <class T>
class BinarySearchTree
{
public:

	BinarySearchTree();
	BinarySearchTree(const BinarySearchTree<T>& scr) = delete;
	BinarySearchTree(BinarySearchTree<T>&& scr) noexcept;
	BinarySearchTree <T>& operator= (const BinarySearchTree <T>& src) = delete;
	BinarySearchTree <T>& operator= (BinarySearchTree <T>&& src) noexcept;
	virtual ~BinarySearchTree();

	bool iterativeSearch(const T& key) const;
	bool insert(const T& key);
	bool deleteKey(const T& key);
	void print(std::ostream& out) const;
	int getCount() const;
	int getHeight() const;
	void iterativeInorderWalk() const;
	void recursiveInorderWalk() const;
	bool operator== (const BinarySearchTree <T>& src);
private:

	template <class T>
	struct Node {
		T key_;
		Node<T>* left_;
		Node<T>* right_;
		Node<T>* p_;
		explicit Node(T key, Node* left = nullptr, Node* right = nullptr, Node* p = nullptr) :
			key_(key), left_(left), right_(right), p_(p)
		{  }
		bool operator==(const Node<T>& other) { return (this->key_ = other->key_) ? true : false; };
	};
	Node<T>* root_;
	void swap(BinarySearchTree <T>& left, BinarySearchTree <T>& right);
	void deleteSubtree(Node<T>* node);
	Node<T>* iterativeSearchNode(const T& key) const;
	Node<T>* Minimum(Node<T>* current) const;
	void printNode(std::ostream& out, Node<T>* root) const;
	int getCountSubTree(const Node<T>* node) const;
	int getHeightSubTree(Node<T>* node) const;
	void recursiveInorderWalk(Node<T>* node) const;
};

template <class T>
BinarySearchTree<T>::BinarySearchTree() : root_(nullptr)
{}

template <class T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& scr) noexcept :
	root_(scr.root_)
{
	scr.root_ = nullptr;
}

template<class T>
BinarySearchTree<T>& BinarySearchTree<T>::operator=(BinarySearchTree<T>&& src) noexcept
{
	if (src == *this)
	{
		return *this;
	}
	swap(*this, src);
	return *this;
}

template <class T>
BinarySearchTree<T>::~BinarySearchTree()
{
	deleteSubtree(root_);
}

template <class T>
void BinarySearchTree<T>::deleteSubtree(Node<T>* node)
{
	Node<T>* current = node;
	while (node)
	{
		if (current->left_)
		{
			current = current->left_;
		}
		else if (current->right_)
		{
			current = current->right_;
		}
		else
		{
			if (!current->p_)
			{
				delete current;
				break;
			}
			if ((current->p_->left_ != nullptr) && (current->p_->left_ == current))
			{
				current = current->p_;
				delete current->left_;
				current->left_ = nullptr;
			}
			else
			{
				current = current->p_;
				delete current->right_;
				current->right_ = nullptr;
			}
		}
	}
}

template <class T>
void BinarySearchTree<T>::swap(BinarySearchTree <T>& left, BinarySearchTree <T>& right)
{
	std::swap(left.root_, right.root_);
}

template <class T>
bool BinarySearchTree<T>::iterativeSearch(const T& key)  const
{
	return (iterativeSearchNode(key) != nullptr);
}

template <class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::iterativeSearchNode(const T& key) const
{
	Node<T>* current = root_;
	while (current != nullptr)
	{
		if (key < current->key_)
		{
			current = current->left_;
		}
		else if (key > current->key_)
		{
			current = current->right_;
		}
		else
		{
			break;
		}
	}
	return current;
}

template<class T>
BinarySearchTree<T>::Node<T>* BinarySearchTree<T>::Minimum(Node<T>* current) const
{
	if (current == nullptr)
	{
		return nullptr;
	}
	while (current->left_ != nullptr)
	{
		current = current->left_;
	}
	return current;
}

template <class T>
bool BinarySearchTree<T>::insert(const T& key)
{
	Node<T>* current = root_;
	Node<T>* parrent = nullptr;
	if (root_ == nullptr)
	{
		root_ = new Node<T>(key);
		return true;
	}
	while (current != nullptr)
	{
		if (key < current->key_)
		{
			parrent = current;
			current = current->left_;
		}
		else if (key > current->key_)
		{
			parrent = current;
			current = current->right_;
		}
		else
		{
			return false;
		}
	}
	if (parrent->key_ > key)
	{
		parrent->left_ = new Node<T>(key, nullptr, nullptr, parrent);
		return true;
	}
	else
	{
		parrent->right_ = new Node<T>(key, nullptr, nullptr, parrent);
		return true;
	}
}

template <class T>
bool BinarySearchTree<T>::deleteKey(const T& key)
{
	Node<T>* current = iterativeSearchNode(key);
	if (current == nullptr)
	{
		return false;
	}
	Node<T>* parrent = current->p_;
	if (current->left_ == nullptr && current->right_ == nullptr && parrent == nullptr)
	{
		delete current;
		root_ = nullptr;
		return true;
	}
	if (current->left_ != nullptr && current->right_ == nullptr && parrent == nullptr)
	{
		root_ = current->left_;
		delete current;
		root_->p_ = nullptr;
		return true;
	}
	if (current->left_ == nullptr && current->right_ != nullptr && parrent == nullptr)
	{
		root_ = current->right_;
		delete current;
		root_->p_ = nullptr;
		return true;
	}
	if (current->left_ != nullptr && current->right_ != nullptr)
	{
		Node<T>* insteadNode = Minimum(current->right_);
		Node<T>* parentOfInsteadNode = insteadNode->p_;
		current->key_ = insteadNode->key_;
		if (parentOfInsteadNode == current)
		{
			current->right_ = nullptr;
			return true;
		}
		if (insteadNode->right_)
		{
			parentOfInsteadNode->left_ = insteadNode->right_;
			delete insteadNode;
			parentOfInsteadNode->left_->p_ = parentOfInsteadNode;
			return true;
		}
		else
		{
			delete insteadNode;
			parentOfInsteadNode->left_ = nullptr;
			return true;
		}
	}

	if (current->left_ == nullptr && current->right_ == nullptr && parrent != nullptr)
	{
		if (current->p_->left_ == current)
		{
			delete current;
			parrent->left_ = nullptr;
		}
		else
		{
			delete current;
			parrent->right_ = nullptr;
		}
		return true;
	}
	if (current->left_ != nullptr && current->right_ == nullptr && parrent != nullptr)
	{
		if (current->p_->left_ == current)
		{
			parrent->left_ = current->left_;
			delete current;
			parrent->left_->p_ = parrent;
		}
		else
		{
			parrent->right_ = current->left_;
			delete current;
			parrent->right_->p_ = parrent;
		}
		return true;
	}
	if (current->left_ == nullptr && current->right_ != nullptr && parrent != nullptr)
	{
		if (current->p_->left_ == current)
		{
			parrent->left_ = current->right_;
			delete current;
			parrent->left_->p_ = parrent;
		}
		else
		{
			parrent->right_ = current->right_;
			delete current;
			parrent->right_->p_ = parrent;
		}
		return true;
	}
}

template <class T>
void BinarySearchTree<T>::print(std::ostream& out) const
{
	printNode(out, root_);
	out << std::endl;
}

template <class T>
void BinarySearchTree<T>::printNode(std::ostream& out, Node<T>* root) const
{
	out << '(';
	if (root != nullptr)
	{
		out << root->key_;
		printNode(out, root->left_);
		printNode(out, root->right_);
	}
	out << ')';
}

template <class T>
int BinarySearchTree<T>::getCount() const
{
	return getCountSubTree(this->root_);
}

template <class T>
int BinarySearchTree<T>::getCountSubTree(const Node<T>* node) const
{
	if (node == nullptr)
		return 0;
	return (1 + getCountSubTree(node->left_) + getCountSubTree(node->right_));
}

template <class T>
int BinarySearchTree<T>::getHeight() const
{
	return getHeightSubTree(this->root_);
}

template <class T>
int BinarySearchTree<T>::getHeightSubTree(Node<T>* node) const
{
	int left = 0, right = 0;
	if (!node)
	{
		return 0;
	}
	if (node->left_)
	{
		left = getHeightSubTree(node->left_);
	}
	if (node->right_)
	{
		right = getHeightSubTree(node->right_);
	}
	return (std::max(left, right) + 1);
}

template <class T>
void BinarySearchTree<T>::iterativeInorderWalk() const
{
	StackArray<Node<T>*> stack(getHeight());
	Node<T>* current = root_;
	while (!stack.isEmpty() || current != nullptr)
	{
		if (current != nullptr)
		{
			stack.push(current);
			current = current->left_;
		}
		else
		{
			current = stack.pop();
			std::cout << current->key_ << ' ';
			current = current->right_;
		}
	}
}

template <class T>
void BinarySearchTree<T>::recursiveInorderWalk() const
{
	return recursiveInorderWalk(this->root_);
}

template <class T>
void BinarySearchTree<T>::recursiveInorderWalk(Node<T>* node) const
{
	if (node != nullptr)
	{
		std::cout << "(";
		recursiveInorderWalk(node->left_);
		std::cout << node->key_;
		recursiveInorderWalk(node->right_);
		std::cout << ")";
	}
}
template <class T>
bool BinarySearchTree<T>::operator== (const BinarySearchTree <T>& src)
{
	if (this->getCount() != src.getCount() || this->getHeight() != src.getHeight())
	{
		return false;
	}
	int count = getCount();
	std::vector<T> thatArray;
	std::vector<T> srcArray;
	StackArray<Node<T>*> stack(getHeight());
	Node<T>* current = root_;
	int i = 0;
	while (!stack.isEmpty() || current != nullptr)
	{
		if (current != nullptr)
		{
			stack.push(current);
			current = current->left_;
		}
		else
		{
			current = stack.pop();
			thatArray.push_back(current->key_);
			i++;
			current = current->right_;
		}
	}
	i = 0;
	current = src.root_;
	while (!stack.isEmpty() || current != nullptr)
	{
		if (current != nullptr)
		{
			stack.push(current);
			current = current->left_;
		}
		else
		{
			current = stack.pop();
			srcArray.push_back(current->key_);
			i++;
			current = current->right_;
		}
	}

	if (thatArray == srcArray)
	{
		return true;
	}
	return false;
}

#endif