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
    _pressedKeys[(int)Keys::w] = isKeyPressed('W');
    _pressedKeys[(int)Keys::a] = isKeyPressed('A');
    _pressedKeys[(int)Keys::s] = isKeyPressed('S');
    _pressedKeys[(int)Keys::d] = isKeyPressed('D');
    _pressedKeys[(int)Keys::left] = isKeyPressed(KeyboardKeys::left);
    _pressedKeys[(int)Keys::up] = isKeyPressed(KeyboardKeys::up);
    _pressedKeys[(int)Keys::right] = isKeyPressed(KeyboardKeys::right);
    _pressedKeys[(int)Keys::down] = isKeyPressed(KeyboardKeys::down);
    _pressedKeys[(int)Keys::enter] = isKeyPressed(KeyboardKeys::enter);
    _pressedKeys[(int)Keys::space] = isKeyPressed(KeyboardKeys::space);
    _pressedKeys[(int)Keys::escape] = isKeyPressed(KeyboardKeys::escape);
    _pressedKeys[(int)Keys::backspace] = isKeyPressed(KeyboardKeys::backspace);
}

bool Keyboard::isKeyPressed(unsigned char key) {
    return (_winKeyStates[key] & 128) > 0;
}
