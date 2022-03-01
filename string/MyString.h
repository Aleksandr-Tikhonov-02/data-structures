#ifndef __STRING__
#define __STRING__

#include <iosfwd>

class MyString
{
public:
	MyString();
	MyString(const char* str);
	MyString(const MyString& other);
	MyString(MyString&& other) noexcept;
	~MyString();

	int getLength();
	char* getStr();

	MyString operator+(const MyString& other);
	MyString& operator=(const MyString& other);
	bool operator==(const MyString& other);
	bool operator!=(const MyString& other);
	const char& operator[](int index);
	friend std::ostream& operator<<(std::ostream& stream, const MyString& mstr);

private:
	char* str_;
	int length_;
};

#endif
