#pragma once

#include <lib/system.h>
#include <model/world/RectElement.h>

class Track : public Object {

    List<RectElement> _groundElements;

public:
    virtual String getName() = 0;
    Collection<RectElement>& getGroundElements();

protected:
    void addGroundElements(Collection<RectElement>& ground);
};
