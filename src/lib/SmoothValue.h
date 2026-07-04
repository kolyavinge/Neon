#pragma once

#include <lib/system.h>

// проста€ интерпол€ци€ двух значений
template<class T>
class SmoothValue : public Object {

    T _currentValue;
    T _destinationValue;

public:
    SmoothValue() {
        _currentValue = {};
        _destinationValue = {};
    }

    SmoothValue(T initCurrentValue) {
        _currentValue = initCurrentValue;
        _destinationValue = initCurrentValue;
    }

    T getCurrentValue() {
        return _currentValue;
    }

    void setCurrentValue(T value) {
        _currentValue = value;
    }

    T getDestinationValue() {
        return _destinationValue;
    }

    void setDestinationValue(T value) {
        _destinationValue = value;
    }

    void set(T value) {
        _currentValue = value;
        _destinationValue = value;
    }

    void update(T step) {
        _currentValue = getUpdated(_currentValue, _destinationValue, step);
    }

    static T getUpdated(T currentValue, T destinationValue, T step) {
        if (currentValue == destinationValue) return currentValue;
        if (currentValue < destinationValue) {
            currentValue += step;
            if (currentValue > destinationValue) {
                currentValue = destinationValue;
            }
        } else {
            currentValue -= step;
            if (currentValue < destinationValue) {
                currentValue = destinationValue;
            }
        }

        return currentValue;
    }
};
