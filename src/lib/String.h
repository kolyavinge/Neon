#pragma once

#include <lib/Object.h>

class String : public Object {

    static const int _initCapacity = 16;

    wchar_t* _symb;
    int _count;
    int _capacity;
    char _tmp[1024];

public:
    String();
    String(int capacity);
    String(const wchar_t* str);
    String(const char* str);
    String(const String& copy);
    ~String() override;

    bool equals(Object& x) override;
    int getHashCode() override;
    String& operator=(const String& copy);
    int getLength();
    wchar_t& operator[](int index);
    String& append(const wchar_t* appended);
    String& append(const wchar_t appended);
    String& append(String& appended);
    int indexOf(const wchar_t ch);
    int lastIndexOf(const wchar_t ch);
    String substring(int startIndex, int count);
    void invert();
    void clear();
    char* getCharBuf();
    wchar_t* getWCharBuf();

private:
    void set(const String& copy);
    int getLength(const wchar_t* str);
    int getLength(const char* str);
    void resizeIfNeeded(int newCount);
};
