#pragma once

#include <functional>
#include <lib/system.h>

enum class Events {
    onResizeScreen,
    _count
};

class EventArgs : public Object {};

class ResizeScreenEventArgs : public EventArgs {

public:
    int width, height;
    ResizeScreenEventArgs(int w, int h);
};

class EventManager : public Object {

    Array<List<std::function<void(EventArgs&)>>, (int)Events::_count> _handlers;

public:
    void attachToEvent(Events event, std::function<void(EventArgs&)> handler);
    void raiseEvent(Events event, EventArgs& args);
};
