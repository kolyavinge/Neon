#include <lib/Numeric.h>
#include <lib/calc/Math.h>
#include <lib/exceptions.h>

bool Numeric::floatEquals(float a, float b, float eps) {
    return Math::abs(a - b) < eps;
}

bool Numeric::between(int x, int left, int right) {
    return left <= x && x <= right;
}

bool Numeric::between(float x, float left, float right) {
    return left <= x && x <= right;
}

float Numeric::clamp(float x, float left, float right) {
    if (x < left) return left;
    if (x > right) return right;

    return x;
}

String Numeric::intToString(const int value) {
    String result;
    intToString(value, result);

    return result;
}

void Numeric::intToString(const int value, String& result) {
    intToStringRec(Math::abs(value), value < 0, result);
}

float Numeric::getSign(float value) {
    return value < 0.0f ? -1.0f : 1.0f;
}

void Numeric::makePositiveSign(float& value) {
    if (value < 0.0f) value = -value;
}

void Numeric::makeNegativeSign(float& value) {
    if (value > 0.0f) value = -value;
}

void Numeric::intToStringRec(const int remainAbs, bool isNegative, String& result) {
    if (remainAbs > 9) {
        int lastDigit = remainAbs % 10;
        intToStringRec(remainAbs / 10, isNegative, result);
        result.append(getChar(lastDigit));
    } else {
        if (isNegative) {
            result.append(L'-');
        }
        result.append(getChar(remainAbs));
    }
}

wchar_t Numeric::getChar(int digit) {
    switch (digit) {
        case 0: return L'0';
        case 1: return L'1';
        case 2: return L'2';
        case 3: return L'3';
        case 4: return L'4';
        case 5: return L'5';
        case 6: return L'6';
        case 7: return L'7';
        case 8: return L'8';
        case 9: return L'9';
        default: throw ArgumentException();
    }
}
