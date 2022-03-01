#ifndef _QUEUE_
#define _QUEUE_

#include <exception>

class QueueOverflow : public std::exception
{
public:
	QueueOverflow() : std::exception("Queue Overflow") {}
};

class QueueUnderflow : public std::exception
{
public:
	QueueUnderflow() : std::exception("Queue Underflow") {}
};

class WrongQueueSize : public std::exception
{
public:
	WrongQueueSize() : std::exception("Wrong Queue Size") {}
};

template <class T>
class Queue
{
public:
	virtual ~Queue() {}

	virtual void enQueue(const T& e) = 0; 
	virtual T deQueue() = 0; 
	virtual bool isEmpty() const = 0;
};

#endif 
