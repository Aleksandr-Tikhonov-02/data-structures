#ifndef __VECTOR__
#define __VECTOR__

#include <iosfwd>

template <class T>
class Vector
{
private:
	int size_;
	T* arr_;
	int capacity_;
public:

	Vector();
	Vector(int size);
	Vector(const Vector& other);
	Vector<T>& operator=(const Vector<T>& other);
	~Vector();

	void push_back(T temp);
	void print();
	int size();
	int getCapacity();

	const T& operator[](int i);
};

template<class T>
Vector<T>::Vector()
{
	arr_ = new T[10];
	size_ = 0;
	capacity_ = 10;
}

template<class T>
Vector<T>::Vector(int size)
{
	arr_ = new T[size];
	size_ = 0;
	capacity_ = size;
}

template<class T>
Vector<T>::Vector(const Vector& other)
{
	this->size_ = other.size_;
	this->capacity_ = other.capacity_;

	for (int i = 0; i < size_; i++)
	{
		this->arr_[i] = other.arr_;
	}
}

template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	if (this = &other)
	{
		return *this;
	}
	this->size_ = other.size_;
	this->capacity_ = other.capacity_;
	for (int i = 0; i < size_; i++)
	{
		this->arr_[i] = other.arr_;
	}
}



template<class T>
Vector<T>::~Vector()
{
	delete[] arr_;
}

template <class T>
void Vector<T>::push_back(T temp)
{
	if (size_ < capacity_)
	{
		arr_[size_] = temp;
		size_++;
	}
	else
	{
		T* temparr = new T[2*capacity_];
		for (int i = 0; i < capacity_; i++)
		{
			temparr[i] = arr_[i];
		}
		temparr[size_++] = temp;
		if (arr_ != nullptr)
		{
			delete[] arr_;
		}
		capacity_ *= 2;
		arr_ = temparr;
	}
}

template <class T>
void  Vector<T>::print()
{
	for (int i = 0; i < size_; i++)
	{
		std::cout << arr_[i] << "\n";
	}
}

template <class T>
int  Vector<T>::size()
{
	return size_;
}

template<class T>
int Vector<T>::getCapacity()
{
	return capacity_;
}

template <class T>
const T& Vector<T>::operator[](int i)
{
	return *(arr_ + i);
}

#endif 