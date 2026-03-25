#include <lib/HashCode.h>

HashCode::HashCode() {
    _result = 1430287;
}

void HashCode::add(char value) {
    add((int)value);
}

void HashCode::add(wchar_t value) {
    add((int)value);
}

void HashCode::add(int value) {
    _result = _result * 7302013 ^ value;
}

void HashCode::add(float value) {
    int bytes = *(int*)&value;
    add(bytes);
}

void HashCode::add(double value) {
    int bytes = *(int*)&value;
    add(bytes);
}

int HashCode::getResult() {
    return _result;
}
