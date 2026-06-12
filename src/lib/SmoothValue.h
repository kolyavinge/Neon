#pragma once

#include <lib/system.h>

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
        _destinationValue = {};
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

    void update(T step) {
        if (_currentValue == _destinationValue) return;
        if (_currentValue < _destinationValue) {
            _currentValue += step;
            if (_currentValue > _destinationValue) {
                _currentValue = _destinationValue;
            }
        } else {
            _currentValue -= step;
            if (_currentValue < _destinationValue) {
                _currentValue = _destinationValue;
            }
        }
    }
};
