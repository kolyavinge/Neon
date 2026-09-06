#pragma once

class Object {

public:
    static bool referenceEquals(Object& x, Object& y);

    Object() = default;

    virtual ~Object() = default;

    virtual bool equals(Object& x);
    virtual int getHashCode();

    // не виртуальный, вызывает внутри себя equals
    bool operator==(Object& x);

protected:
    // копирование разрешено только наследникам
    Object(const Object&) = default;
    Object& operator=(const Object&) = default;
};
