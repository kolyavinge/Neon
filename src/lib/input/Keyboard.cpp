#pragma warning(push)
#pragma warning(disable : 5039 4668)
#include <windows.h>
#pragma warning(pop)
#include <lib/input/Keyboard.h>

class KeyboardKeys {

public:
    inline static const unsigned char left = 0x25;
    inline static const unsigned char up = 0x26;
    inline static const unsigned char right = 0x27;
    inline static const unsigned char down = 0x28;
    inline static const unsigned char enter = 0x0D;
    inline static const unsigned char space = 0x20;
    inline static const unsigned char escape = 0x1B;
    inline static const unsigned char backspace = 0x08;
};

void Keyboard::updatePressedKeys() {
    Assert::isTrue(GetKeyboardState(_winKeyStates.getBuf()));
    _pressedKeys[(int)Keys::w] = isKeyboardKeyPressed('W');
    _pressedKeys[(int)Keys::a] = isKeyboardKeyPressed('A');
    _pressedKeys[(int)Keys::s] = isKeyboardKeyPressed('S');
    _pressedKeys[(int)Keys::d] = isKeyboardKeyPressed('D');
    _pressedKeys[(int)Keys::left] = isKeyboardKeyPressed(KeyboardKeys::left);
    _pressedKeys[(int)Keys::up] = isKeyboardKeyPressed(KeyboardKeys::up);
    _pressedKeys[(int)Keys::right] = isKeyboardKeyPressed(KeyboardKeys::right);
    _pressedKeys[(int)Keys::down] = isKeyboardKeyPressed(KeyboardKeys::down);
    _pressedKeys[(int)Keys::enter] = isKeyboardKeyPressed(KeyboardKeys::enter);
    _pressedKeys[(int)Keys::space] = isKeyboardKeyPressed(KeyboardKeys::space);
    _pressedKeys[(int)Keys::escape] = isKeyboardKeyPressed(KeyboardKeys::escape);
    _pressedKeys[(int)Keys::backspace] = isKeyboardKeyPressed(KeyboardKeys::backspace);
}

bool Keyboard::isKeyboardKeyPressed(unsigned char key) {
    return (_winKeyStates[key] & 128) > 0;
}
