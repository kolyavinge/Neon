// сначала нужно подключать эти файлы
#include <lib/windows.h>
#include <memory>
#include <vector>
#pragma warning(push)
#pragma warning(disable : 4365 4623 4668 5039 5246)
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Gaming.Input.h>
#pragma warning(pop)
// сначала нужно подключать эти файлы

#include <lib/input/Joystick.h>

void Joystick::updatePressedKeys() {
    using namespace winrt::Windows::Gaming::Input;

    auto joyList = RawGameController::RawGameControllers();
    if (joyList.Size() == 0) return;

    RawGameController joy = joyList.GetAt(0);

    int buttonCount = joy.ButtonCount();
    int switchCount = joy.SwitchCount();
    int axisCount = joy.AxisCount();

    static std::unique_ptr<bool[]> buttonStates = std::make_unique<bool[]>((size_t)buttonCount);
    static std::vector<GameControllerSwitchPosition> switchStates((size_t)switchCount);
    static std::vector<double> axisStates((size_t)axisCount);

    winrt::array_view<bool> buttonsView(buttonStates.get(), buttonStates.get() + buttonCount);
    winrt::array_view<GameControllerSwitchPosition> switchesView(switchStates.data(), switchStates.data() + switchCount);
    winrt::array_view<double> axisView(axisStates.data(), axisStates.data() + axisCount);

    joy.GetCurrentReading(buttonsView, switchesView, axisView);

    _pressedKeys[(int)Keys::left] = axisStates[3] == 0.0;
    _pressedKeys[(int)Keys::right] = axisStates[3] == 1.0;
    _pressedKeys[(int)Keys::up] = axisStates[4] == 0.0;
    _pressedKeys[(int)Keys::down] = axisStates[4] == 1.0;
    _pressedKeys[(int)Keys::button1] = buttonStates[0];
    _pressedKeys[(int)Keys::button2] = buttonStates[1];
    _pressedKeys[(int)Keys::button3] = buttonStates[2];
    _pressedKeys[(int)Keys::button4] = buttonStates[3];
    _pressedKeys[(int)Keys::button5] = buttonStates[4];
    _pressedKeys[(int)Keys::button6] = buttonStates[5];
    _pressedKeys[(int)Keys::button7] = buttonStates[6];
    _pressedKeys[(int)Keys::button8] = buttonStates[7];
}
