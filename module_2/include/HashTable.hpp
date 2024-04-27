#pragma once
#include <vector>
#include <functional>
#include <string>
#include <iostream>


constexpr int INITIAL_SIZE = 8;
constexpr float MAX_FILLED_RATIO = 3.f / 4;

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

    ~HashTableElement() {
        _element_state = ElementState::NIL;
    }
};

class StringHasher {
private:
    size_t _prime;

public:
    explicit StringHasher(const size_t prime = 211) : _prime(prime) {
    }

    size_t operator()(const std::string& str) const {
        size_t hash = 0;
        for (const char i: str) {
            hash = hash * _prime + i;
        }
        return hash;
    }
};

template<typename T, typename Hasher = std::hash<T>>
class HashTable {
private:
    void rehash() {
        std::cout << _number_of_filled << '\n';
        std::vector<HashTableElement<T>> new_table_data(_table_data.size() * 2);
        for (int i = 0; i < _table_data.size(); ++i) {
            auto elem = _table_data[i];
            auto new_hash = _hasher(elem._data) % new_table_data.size();
            if (new_table_data[new_hash]._element_state == HashTableElement<T>::ElementState::KEY) {
                int counter = 0;
                for (size_t j = new_hash + 1; counter < new_table_data.size(); ++j, ++counter) {
                    if (j >= _table_data.size())
                        j = 0;
                    if (_table_data[j]._element_state == HashTableElement<T>::ElementState::NIL) {
                        new_table_data[j] = elem;
                    }
                }
            } else
                new_table_data[new_hash] = elem;
        }
        _table_data = new_table_data;
    }

    std::vector<HashTableElement<T>> _table_data;
    Hasher _hasher;
    double _number_of_filled;

public:
    explicit HashTable(size_t initial_size = INITIAL_SIZE): _table_data(initial_size), _number_of_filled(0) {
    }

    ~HashTable() {
        _table_data.clear();
        _number_of_filled = 0;
    }

    bool add(const T& key) {
        if (_number_of_filled / _table_data.size() > MAX_FILLED_RATIO)
            rehash();

        if (_table_data.empty()) {
            auto elem = HashTableElement<T>(key);
            _table_data.push_back(elem);
            ++_number_of_filled;
            return true;
        }

        const size_t hash = _hasher(key) % _table_data.size();
        int counter = 0;
        int del_pos = -1;
        for (size_t i = hash; counter < _table_data.size(); ++i, ++counter) {
            if (i >= _table_data.size())
                i = 0;
            auto current_table_elem = _table_data[i];

            if (current_table_elem._data == key && current_table_elem._element_state != HashTableElement<
                    T>::ElementState::DEL)
                return false;

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::DEL)
                del_pos = static_cast<int>(i);

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL) {
                if (del_pos != -1)
                    _table_data[del_pos] = HashTableElement<T>(key);
                else
                    _table_data[i] = HashTableElement<T>(key);
                ++_number_of_filled;
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
            if (current_table_elem._data == key &&
                current_table_elem._element_state != HashTableElement<T>::ElementState::DEL)
                return true;

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL)
                return false;
        }
        return false;
    }

    bool remove(const T& key) {
        const size_t hash = _hasher(key) % _table_data.size();
        int counter = 0;
        for (size_t i = hash; counter < _table_data.size(); ++i, ++counter) {
            if (i >= _table_data.size())
                i = 0;
            auto current_table_elem = _table_data[i];
            if (current_table_elem._data == key && current_table_elem._element_state != HashTableElement<
                    T>::ElementState::DEL) {
                _table_data[i]._element_state = HashTableElement<T>::ElementState::DEL;
                return true;
            }

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL)
                return false;
        }
    }
};
