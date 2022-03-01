#ifndef _QUEUE_ARRAY_
#define _QUEUE_ARRAY_

#include "Queue.h"

template <typename T>
class QueueArray final : public Queue<T> 
{
private:
	T* array_; 
	int head_ = 1;
	int tail_ = 0;
	int size_;
	void swap(QueueArray<T>& right);
public:
	QueueArray(int size);
	QueueArray(const QueueArray<T>& src) = delete;
	QueueArray(QueueArray<T>&& src) noexcept;
	QueueArray<T>& operator= (const QueueArray<T>& src) = delete;
	QueueArray<T>& operator= (QueueArray<T>&& src) noexcept;
	virtual ~QueueArray() override { delete[] array_; }

	void print();
	void enQueue(const T& e) override;
	T deQueue() override;
	bool isEmpty() const override { return tail_ == 0; }
	bool operator== (const QueueArray<T>& src);
	
};

#endif 

template<typename T>
void QueueArray<T>::swap(QueueArray<T>& right)
{
	std::swap(*this.array_, right.array_);
	std::swap(*this.head_, right.head_);
	std::swap(*this.tail_, right.tail_);
	std::swap(*this.size_, right.size_);
}

template <typename T>
QueueArray<T>::QueueArray(int size):
	size_(size), head_(1), tail_(0)
{
	try 
	{
		array_ = new T[size + 1];
	}
	catch (...) 
	{
		throw WrongQueueSize();
	}
}

template<typename T>
QueueArray<T>::QueueArray(QueueArray<T>&& src) noexcept:
	array_(src.array_),
	head_(src.head_),
	tail_(src.tail_),
	size_(src.size_)
{
	src.array_ = nullptr;
}

template<typename T>
QueueArray<T>& QueueArray<T>::operator=(QueueArray<T>&& src) noexcept
{
	if (src == *this)
	{
		return *this;
	}
	swap(src);
	return *this;
}

template<typename T>
void QueueArray<T>::print()
{
	if (head_ == 1)
	{
		for (int i = 1; i <= size_; i++)
		{
			std::cout << this->array_[i] << ' ';
		}
	}
	else
	{
		for (int i = head_; i <= size_; i++)
		{
			std::cout << this->array_[i] << ' ';
		}
		for (int i = 1; i <= tail_; i++)
		{
			std::cout << this->array_[i] << ' ';
		}
	}
	std::cout << "\n";
}

template<typename T>
void QueueArray<T>::enQueue(const T& e)
{
	if ((head_ == tail_ + 1 && tail_ != 0) || (head_ == 1 && tail_ == size_))
	{
		throw QueueOverflow();
	}
	if (tail_ == size_)
	{
		array_[1] = e;
		tail_ = 1;
	}
	else if (tail_ == 0)
	{
		tail_ = head_;
		array_[tail_] = e;
	}
	else
	{
		array_[++tail_] = e;
	}
}

template<typename T>
T QueueArray<T>::deQueue()
{
	if (tail_ == 0)
	{
		throw QueueUnderflow(); 
	}
	if (head_ == tail_)
	{
		tail_ = 0;
		return array_[head_];
	}
	if (head_ == size_)
	{
		head_ = 1;
		return array_[size_];
	}
	else
	{
		return array_[head_++];
	}
}

template<typename T>
inline bool QueueArray<T>::operator==(const QueueArray<T>& src)
{
	if (this->size_ != src.size_ || this->head_ != src.head_ || this->tail_ != src.tail_)
	{
		return false;
	}
	if (head_ == 1)
	{
		for (int i = 1; i <= size_; i++)
		{
			if (this->array_[i] != src.array_[i])
			{
				return false;
			}
		}
	}
	else
	{
		for (int i = head_; i <= size_; i++)
		{
			if (this->array_[i] != src.array_[i])
			{
				return false;
			}
		}
		for (int i = 1; i <= tail_; i++)
		{
			if (this->array_[i] != src.array_[i])
			{
				return false;
			}
		}
	}
	return true;
}
