#include "MyString.h"



MyString::MyString()
{
	length_ = 0;
	str_ = nullptr;
}

MyString::MyString(const char* otherStr)
{
	length_ = strlen(otherStr);
	str_ = new char[length_ + 1];
	for (int i = 0; i < length_; i++)
	{
		str_[i] = otherStr[i];
	}
	str_[length_] = '\0';
}

MyString::MyString(const MyString& other)
{
	length_ = strlen(other.str_);
	this->str_ = new char[length_ + 1];

	for (int i = 0; i < length_; i++)
	{
		this->str_[i] = other.str_[i];
	}

	this->str_[length_] = '\0';
}

MyString::MyString(MyString&& other) noexcept
{
	this->length_ = other.length_;
	this->str_ = other.str_;
	other.length_ = 0;
	other.str_ = nullptr;
}

MyString::~MyString()
{
	delete[] str_;
}

int MyString::getLength()
{
	return length_;
}

char* MyString::getStr()
{
	return str_;
}



MyString MyString::operator+(const MyString& other)
{
	MyString newstr;
	int length1 = strlen(this->str_);
	int length2 = strlen(other.str_);
	newstr.length_ = length1 + length2;
	newstr = new char[length1 + length2 + 1];
	int i = 0;
	for (i; i < length1; i++)
	{
		newstr.str_[i] = this->str_[i];
	}
	for (int j = 0; j < length2; j++, i++)
	{
		newstr.str_[i] = other.str_[j];
	}
	newstr.str_[length1 + length2] = '\0';
	return newstr;
}

MyString& MyString::operator=(const MyString& other)
{
	if (str_ != nullptr)
	{
		delete[] str_;
	}
	length_ = strlen(other.str_);
	str_ = new char[length_ + 1];
	for (int i = 0; i < length_; i++)
	{
		str_[i] = other.str_[i];
	}
	str_[length_] = '\0';
	return *this;
}

bool MyString::operator==(const MyString& other)
{
	if (length_ != other.length_)
	{
		return false;
	}
	for (int i = 0; i < length_; i++)
	{
		if (str_[i] != other.str_[i])
		{
			return false;
		}
	}
	return true;
}

bool MyString::operator!=(const MyString& other)
{
	return !(this->operator==(other));
}

const char& MyString::operator[](int index)
{
	return str_[index];
}

std::ostream& operator <<(std::ostream& stream, const MyString& mstr)
{
	stream << mstr.str_;
	return stream;
}
