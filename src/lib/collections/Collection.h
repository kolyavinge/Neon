#pragma once

#include <lib/Object.h>
#include <lib/collections/comparators.h>

template<class T>
class Collection;

template<class T>
class List;

template<class TKey, class TItem>
class Group : public Object {

    TKey _key = {};
    List<TItem> _items;

public:
    TKey getKey() {
        return _key;
    }

    void setKey(TKey key) {
        _key = key;
    }

    int getItemsCount() {
        return _items.getCount();
    }

    Collection<TItem>& getItems() {
        return _items;
    }

    TItem& operator[](int index) {
        return _items[index];
    }

    void addItem(TItem& item) {
        _items.add(item);
    }
};

template<class T>
class Collection : public Object {

public:
    virtual T& operator[](int index) = 0;

    virtual int getCount() const = 0;

    T& first() {
        return (*this)[0];
    }

    T& last() {
        return (*this)[getCount() - 1];
    }

    int getIndexOf(const T& item) {
        for (int i = 0; i < getCount(); i++) {
            if (item == (*this)[i]) {
                return i;
            }
        }

        return -1;
    }

    void initAll(T initValue) {
        for (int i = 0; i < getCount(); i++) {
            (*this)[i] = initValue;
        }
    }

    void initRange(int startIndex, int endIndex, T value) {
        for (int i = startIndex; i <= endIndex; i++) {
            (*this)[i] = value;
        }
    }

    void sort(IComparator<T>& comparator) {
        int count = getCount();
        if (count > 0) {
            sortRec(0, count - 1, comparator);
        }
    }

    template<class TGroupKey>
    void groupBy(TGroupKey(*getGroupKey)(T& item), List<Group<TGroupKey, T*>>& grouped) {
        int count = getCount();
        if (count == 0) return;

        class GroupKeyComparator : public Object, public IComparator<T*> {
            TGroupKey(*_getGroupKey)(T& item);
        public:
            GroupKeyComparator(TGroupKey(*getGroupKey)(T& item)) { _getGroupKey = getGroupKey; }
            int compare(T* a, T* b) override {
                TGroupKey x = _getGroupKey(*a);
                TGroupKey y = _getGroupKey(*b);

                return x < y ? -1 : (x > y ? 1 : 0);
            }
        };

        List<T*> sortedItemsByGroupKey;
        for (int i = 0; i < count; i++) {
            sortedItemsByGroupKey.add(&(*this)[i]);
        }
        GroupKeyComparator comparator(getGroupKey);
        sortedItemsByGroupKey.sort(comparator);

        TGroupKey lastKey = getGroupKey(*sortedItemsByGroupKey[0]);
        Group<TGroupKey, T*>& firstGroup = grouped.addNew();
        firstGroup.setKey(lastKey);
        firstGroup.addItem(sortedItemsByGroupKey[0]);
        for (int i = 1; i < sortedItemsByGroupKey.getCount(); i++) {
            T* item = sortedItemsByGroupKey[i];
            TGroupKey currentKey = getGroupKey(*item);
            if (lastKey == currentKey) {
                grouped.last().addItem(item);
            } else {
                lastKey = currentKey;
                Group<TGroupKey, T*>& newGroup = grouped.addNew();
                newGroup.setKey(lastKey);
                newGroup.addItem(item);
            }
        }
    }

    int getSizeInBytes() {
        return getCount() * (int)sizeof(T);
    }

private:
    void sortRec(int startIndex, int endIndex, IComparator<T>& comparator) {
        int i = startIndex;
        int j = endIndex;
        T& middle = (*this)[(i + j) / 2];
        while (i <= j) {
            while (comparator.compare((*this)[i], middle) < 0) i++;
            while (comparator.compare((*this)[j], middle) > 0) j--;
            if (i <= j) {
                T temp = (*this)[i];
                (*this)[i] = (*this)[j];
                (*this)[j] = temp;
                i++;
                j--;
            }
        }
        if (j > startIndex) sortRec(startIndex, j, comparator);
        if (i < endIndex) sortRec(i, endIndex, comparator);
    }
};
