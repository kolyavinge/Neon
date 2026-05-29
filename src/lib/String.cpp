#pragma warning(push)
#pragma warning(disable : 5204 4820 4365 4514 5039 4668)
#include <comdef.h>
#pragma warning(pop)

#include <lib/HashCode.h>
#include <lib/Memory.h>
#include <lib/String.h>

String String::empty = String();

String::String() : String(_initCapacity) {}

String::String(int capacity) {
    _count = 0;
    _capacity = capacity;
    _symb = Memory::allocate<wchar_t>(_capacity);
    Memory::zero<char>(_tmp, 1024);
}

String::String(const wchar_t* str) {
    _count = getLength(str);
    _capacity = 2 * _count;
    if (_capacity == 0) {
        _capacity = _initCapacity;
    }
    _symb = Memory::allocate<wchar_t>(_capacity);
    Memory::copy<wchar_t>(str, _symb, _count);
}

String::String(const char* str) {
    _count = getLength(str);
    _capacity = 2 * _count;
    if (_capacity == 0) {
        _capacity = _initCapacity;
    }
    _symb = Memory::allocate<wchar_t>(_capacity);
    size_t outSize;
    mbstowcs_s(&outSize, _symb, (size_t)(_count + 1), str, (size_t)_count);
}

String::String(const String& copy) {
    _symb = nullptr;
    set(copy);
}

String::~String() {
    Memory::release(_symb);
}

bool String::equals(Object& x) {
    String& str = (String&)x;
    if (_count != str._count) return false;
    for (int i = 0; i < _count; i++) {
        if (_symb[i] != str._symb[i]) {
            return false;
        }
    }

    return true;
}

int String::getHashCode() {
    HashCode hash;
    for (int i = 0; i < _count; i++) {
        hash.add(_symb[i]);
    }
    int result = hash.getResult();

    return result;
}

String& String::operator=(const String& copy) {
    set(copy);
    return *this;
}

int String::getLength() {
    return _count;
}

wchar_t& String::operator[](int index) {
    return _symb[index];
}

String& String::append(const wchar_t* appended) {
    int appendedCount = getLength(appended);
    int newCount = _count + appendedCount + 1; // +1 - zero terminated
    resizeIfNeeded(newCount);
    Memory::copy<wchar_t>(appended, &_symb[_count], appendedCount);
    _count += appendedCount;

    return *this;
}

String& String::append(const wchar_t appended) {
    int newCount = _count + 1 + 1; // +1 - zero terminated
    resizeIfNeeded(newCount);
    _symb[_count] = appended;
    _count++;

    return *this;
}

String& String::append(String& appended) {
    int newCount = _count + appended._count + 1; // +1 - zero terminated
    resizeIfNeeded(newCount);
    Memory::copy<wchar_t>(appended._symb, &_symb[_count], appended._count);
    _count += appended._count;

    return *this;
}

int String::indexOf(const wchar_t ch) {
    for (int i = 0; i < _count; i++) {
        if (_symb[i] == ch) return i;
    }

    return -1;
}

int String::lastIndexOf(const wchar_t ch) {
    for (int i = _count - 1; i >= 0; i--) {
        if (_symb[i] == ch) return i;
    }

    return -1;
}

String String::substring(int startIndex, int count) {
    if (startIndex + count > _count) throw ArgumentException(L"startIndex and count must be inside string bounds.");
    String result(count + 1); // +1 - zero terminated
    result._count = count;
    Memory::copy<wchar_t>(&_symb[startIndex], result._symb, count);

    return result;
}

bool String::startsWith(const wchar_t* str) {
    int strLength = getLength(str);
    if (_count < strLength) throw ArgumentException(L"str is too long string.");
    for (int i = 0; i < strLength; i++) {
        if (_symb[i] != str[i]) return false;
    }

    return true;
}

bool String::startsWith(String& str) {
    return startsWith(str.getWCharPointer());
}

bool String::endsWith(const wchar_t* str) {
    int strLength = getLength(str);
    if (_count < strLength) throw ArgumentException(L"str is too long string.");
    for (int i = _count - 1, j = strLength - 1; j >= 0; i--, j--) {
        if (_symb[i] != str[j]) return false;
    }

    return true;
}

bool String::endsWith(String& str) {
    return endsWith(str.getWCharPointer());
}

void String::invert() {
    for (int i = 0; i < _count / 2; i++) {
        wchar_t tmp = _symb[i];
        _symb[i] = _symb[_count - i - 1];
        _symb[_count - i - 1] = tmp;
    }
}

void String::clear() {
    _count = 0;
    Memory::zero<wchar_t>(_symb, _capacity);
}

void String::fillZero(int count) {
    prepareEnoughCapacity(count);
    _count = count;
    Memory::zero<wchar_t>(_symb, count);
}

void String::prepareEnoughCapacity(int enoughCapacity) {
    if (enoughCapacity <= 0) throw ArgumentException(L"enoughCapacity must be greater than zero.");
    if (_capacity > enoughCapacity) return;
    _capacity = enoughCapacity;
    Memory::resize<wchar_t>(_symb, _count, _capacity);
}

const char* String::getCharPointer() {
    _bstr_t bstr = _symb; // convert wchar_t -> char
    strcpy_s(_tmp, bstr);

    return _tmp;
}

wchar_t* String::getWCharPointer() {
    return _symb;
}

void String::set(const String& copy) {
    _count = copy._count;
    _capacity = copy._capacity;
    if (_symb != nullptr) {
        Memory::release(_symb);
    }
    _symb = Memory::allocate<wchar_t>(_capacity);
    Memory::copy<wchar_t>(copy._symb, _symb, _capacity);
}

int String::getLength(const wchar_t* str) {
    int len = 0;
    for (int i = 0; str[i] != L'\0'; i++) len++;
    return len;
}

int String::getLength(const char* str) {
    int len = 0;
    for (int i = 0; str[i] != '\0'; i++) len++;
    return len;
}

void String::resizeIfNeeded(int newCount) {
    if (newCount > _capacity) {
        _capacity = 2 * newCount;
        Memory::resize<wchar_t>(_symb, _count, _capacity);
        Memory::zero<wchar_t>(&_symb[_count], (_capacity - _count));
    }
}
