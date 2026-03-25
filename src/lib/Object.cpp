#include <lib/Object.h>

bool Object::referenceEquals(Object& x, Object& y) {
    return (&x) == (&y);
}

bool Object::equals(Object& x) {
    return referenceEquals(*this, x);
}

int Object::getHashCode() {
    return (int)(long long)this;
}

bool Object::operator==(Object& x) {
    return equals(x);
}
