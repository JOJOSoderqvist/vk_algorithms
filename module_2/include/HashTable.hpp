#pragma once
#include <vector>

constexpr int INITIAL_SIZE = 8;

template<typename T>
struct HashTableElement {
    enum class ElementState {
        KEY,
        NIL,
        DEL
    };

    T _data;
    ElementState _element_state;

    HashTableElement() {
        _element_state = ElementState::NIL;
    }

    explicit HashTableElement(const T& data) : _data(data) {
        _element_state = ElementState::KEY;
    }

    explicit HashTableElement(const T& data, const ElementState state) : _data(data),
                                                                         _element_state(state) {
    }
};


template<typename T, typename Hasher>
class HashTable {
private:
    void rehash();

    std::vector<HashTableElement<T>> _table_data;
    Hasher _hasher;

public:
    explicit HashTable(size_t initial_size = INITIAL_SIZE): _table_data(initial_size) {}

    ~HashTable() = default;

    bool add(const T& key) {
        if (_table_data.empty()) {
            auto elem = HashTableElement<T>(key, HashTableElement<T>::ElementState::KEY);
            _table_data.push_back(elem);
            return true;
        }

        const size_t hash = _hasher(key) % _table_data.size();
        int counter = 0;
        int del_pos = -1;
        for (size_t i = hash; counter < _table_data.size(); ++i, ++counter) {
            if (i == _table_data.size())
                i = 0;
            auto current_table_elem = _table_data[i];

            if (current_table_elem._data == key)
                return false;
            if (current_table_elem._element_state == HashTableElement<T>::ElementState::DEL)
                del_pos = static_cast<int>(i);

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL) {
                if (del_pos != -1)
                    _table_data[del_pos] = key;
                else
                    _table_data[i] = key;
                return true;
            }
        }
    }

    bool has(const T& key) {
        const size_t hash = _hasher(key) % _table_data.size();
        int counter = 0;
        for (size_t i = hash; counter < _table_data.size(); ++i, ++counter) {
            if (i == _table_data.size())
                i = 0;
            auto current_table_elem = _table_data[i];
            if (current_table_elem._data == key)
                return true;

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL)
                return false;
        }
    }
    bool remove(const T& key) {
        const size_t hash = _hasher(key) % _table_data.size();
        int counter = 0;
        for (size_t i = hash; counter < _table_data.size(); ++i, ++counter) {
            if (i == _table_data.size())
                i = 0;
            auto current_table_elem = _table_data[i];
            if (current_table_elem._data == key) {
                _table_data[i]._element_state = HashTableElement<T>::ElementState::DEL;
                delete _table_data[i]._data;
                return true;
            }

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL)
                return false;
        }
    }
};
