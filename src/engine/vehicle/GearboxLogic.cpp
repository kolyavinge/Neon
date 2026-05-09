#include <engine/vehicle/GearboxLogic.h>

void GearboxLogic::shift(Gearbox& gearbox, bool isShiftedUp, bool isShiftedDown) {
    // для автоматической коробки логику переключения написать тут

    if (isShiftedUp) {
        gearbox.shiftUp();
    } else if (isShiftedDown) {
        gearbox.shiftDown();
    }
}
