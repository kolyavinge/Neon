#pragma once

#include <concepts>
#include <lib/Memory.h>
#include <lib/collections/Collection.h>
#include <lib/exceptions.h>

template<class T>
class List : public Collection<T> {

    static const int _initCapacity = 16;

    T* _items;
    int _count;
    int _capacity;

public:
    List() : List(_initCapacity) {}

    List(int capacity) {
        if (capacity < 0) throw ArgumentException();
        _count = 0;
        _capacity = capacity;
        if (_capacity > 0) {
            _items = new T[(size_t)_capacity];
            // _items нельзя инициализировать нулями, ибо в случае с обьектами мы перезапишем vptr
        } else {
            _items = nullptr;
        }
    }

    List(const List<T>& copy) {
        _items = nullptr;
        set(copy);
    }

    ~List() override {
        delete[] _items;
    }

    List<T>& operator=(const List<T>& other) {
        set(other);
        return *this;
    }

    T& operator[](int index) override {
        checkBounds(index, _count);
        return _items[index];
    }

    int getCount() const override {
        return _count;
    }

    void initAll(T initValue) {
        for (int i = 0; i < _count; i++) {
            _items[i] = initValue;
        }
    }

    // для простых типов - передача по значению
    void add(T value) requires std::is_scalar_v<T> {
        addInternal(value);
    }

    // для обьектов - передача по ссылке
    void add(T& value) requires !std::is_scalar_v<T> {
        addInternal(value);
    }

    T& addNew() {
        resizeIfNeeded(1);
        _count++;

        return _items[_count - 1];
    }

    void addRange(List<T>& range) {
        resizeIfNeeded(range.getCount());
        Memory::copy<T>(range._items, _items + _count, range.getCount());
        _count += range.getCount();
    }

    void addRange(T* range, int count) {
        resizeIfNeeded(count);
        Memory::copy<T>(range, _items + _count, count);
        _count += count;
    }

    void insert(int index, T value) {
        checkBounds(index, _count + 1);
        resizeIfNeeded(1);
        for (int i = _count; i > index; i--) {
            _items[i] = _items[i - 1];
        }
        _items[index] = value;
        _count++;
    }

    void removeAt(int index) {
        checkBounds(index, _count);
        for (int i = index; i < _count - 1; i++) {
            _items[i] = _items[i + 1];
        }
        _count--;
    }

    void remove(T value) {
        for (int i = 0; i < _count; ) {
            if (_items[i] == value) {
                removeAt(i);
            } else {
                i++;
            }
        }
    }

    void removeAll(Collection<T>& range) {
        for (int i = 0; i < range.getCount(); i++) {
            remove(range[i]);
        }
    }

    int findIndex(T value) {
        for (int i = 0; i < _count; i++) {
            if (_items[i] == value) return i;
        }

        return -1;
    }

    void clear() {
        _count = 0;
    }

    void prepareEnoughCapacity(int enoughCapacity) {
        if (enoughCapacity <= 0) throw ArgumentException(L"enoughCapacity must be greater than zero.");
        if (_capacity > enoughCapacity) return;
        _capacity = enoughCapacity;
        resizeItems();
    }

    T* getItemsPointer() {
        return _items;
    }

private:
    void addInternal(T& value) {
        resizeIfNeeded(1);
        _items[_count] = value;
        _count++;
    }

    void set(const List<T>& copy) {
        _count = copy._count;
        _capacity = copy._capacity;
        if (_items != nullptr) {
            delete[] _items;
        }
        if (_capacity > 0) {
            _items = new T[(size_t)_capacity];
            Memory::copy<T>(copy._items, _items, _capacity);
        }
    }

    void resizeIfNeeded(int addedCount) {
        bool resize = false;
        while (_count + addedCount > _capacity) {
            _capacity *= 2;
            resize = true;
        }
        if (resize) {
            resizeItems();
        }
    }

    void checkBounds(int index, int count) {
        bool inBounds = 0 <= index && index < count;
        if (!inBounds) throw IndexOutOfBoundsException();
    }

    void resizeItems() {
        Memory::resize<T>(_items, _count, _capacity);
    }
};
