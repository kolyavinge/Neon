#pragma once

class Object {

public:
    static bool referenceEquals(Object& x, Object& y);

    Object() = default;
    Object(const Object&) = default;
    Object(Object&&) noexcept = default;

    // копирование по умолчанию запрещено
    Object& operator=(const Object&) = delete;
    Object& operator=(Object&&) noexcept = delete;

    virtual ~Object() = default;

    virtual bool equals(Object& x);
    virtual int getHashCode();

    // не виртуальный, вызывает внутри себя equals
    bool operator==(Object& x);
};
