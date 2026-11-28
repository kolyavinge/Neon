#include <common/EventManager.h>

ResizeScreenEventArgs::ResizeScreenEventArgs(int w, int h) {
    width = w;
    height = h;
}

void EventManager::attachToEvent(Events event, std::function<void(EventArgs&)> handler) {
    _handlers[(int)event].add(handler);
}

void EventManager::raiseEvent(Events event, EventArgs& args) {
    List<std::function<void(EventArgs&)>>& eventHandlers = _handlers[(int)event];
    for (int i = 0; i < eventHandlers.getCount(); i++) {
        eventHandlers[i](args);
    }
}
