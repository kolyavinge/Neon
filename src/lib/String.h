#pragma once

#include <lib/Object.h>

// from WinNls.h
enum class Encoding {
    utf7 = 65000,
    utf8 = 65001
};

class String : public Object {

    wchar_t* _symb;
    int _count;
    int _capacity;
    char _tmp[1024];

public:
    static String empty;

    String();
    String(const wchar_t* str);
    String(const char* str, Encoding encoding = Encoding::utf8);
    String(const String& copy);
    ~String() override;

    bool equals(Object& x) override;
    int getHashCode() override;
    String& operator=(const String& copy);
    int getLength() const;
    wchar_t& operator[](int index);
    String& append(const wchar_t* appended);
    String& append(const wchar_t appended);
    String& append(const String& appended);
    int indexOf(const wchar_t ch);
    int lastIndexOf(const wchar_t ch);
    String substring(int startIndex, int count);
    bool startsWith(const wchar_t* str);
    bool startsWith(String& str);
    bool endsWith(const wchar_t* str);
    bool endsWith(String& str);
    void invert();
    void clear();
    void fillZero(int count);
    void prepareEnoughCapacity(int enoughCapacity);
    const char* getCharPointer();
    wchar_t* getWCharPointer();

private:
    void set(const String& copy);
    int getLength(const wchar_t* str);
    int getLength(const char* str);
    void resizeIfNeeded(int newCount);
};
