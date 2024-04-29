#pragma once
#include <vector>
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
public:
    explicit StringHasher(const size_t prime = 211, const size_t secondary_prime = 101) : _main_prime(prime), _secondary_prime(secondary_prime) {
    }

    size_t operator()(const std::string& str) const {
        size_t hash = 0;
        for (const char i: str) {
            hash = hash * _main_prime + i;
        }
        return hash ? hash : 1;
    }


    [[nodiscard]] size_t secondary_hash(const std::string& str) const {
        size_t hash = 0;
        for (const char i: str) {
            hash = hash * _secondary_prime + i;
        }
        return hash ? 2 * hash + 1 : 1;
    }
private:
    size_t _main_prime;
    size_t _secondary_prime;
};

template<typename T, typename Hasher = StringHasher>
class HashTable {
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

        size_t main_hash = _hasher(key) % _table_data.size();
        const size_t secondary_hash = _hasher.secondary_hash(key) % _table_data.size();
        int counter = 0;
        int del_pos = -1;
        for (; counter < _table_data.size(); ++counter) {
            if (main_hash >= _table_data.size())
                main_hash = 0;
            auto current_table_elem = _table_data[main_hash];

            if (current_table_elem._data == key && current_table_elem._element_state == HashTableElement<T>::ElementState::KEY)
                return false;

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::DEL)
                del_pos = static_cast<int>(main_hash);

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL) {
                if (del_pos != -1)
                    _table_data[del_pos] = HashTableElement<T>(key);
                else
                    _table_data[main_hash] = HashTableElement<T>(key);
                ++_number_of_filled;
                return true;
            }

            main_hash = (main_hash + secondary_hash) % _table_data.size();
        }
    }

    bool has(const T& key) {
        size_t main_hash = _hasher(key) % _table_data.size();
        const size_t secondary_hash = _hasher.secondary_hash(key) % _table_data.size();
        int counter = 0;
        for (; counter < _table_data.size(); ++counter) {
            if (main_hash == _table_data.size())
                main_hash = 0;
            auto current_table_elem = _table_data[main_hash];
            if (current_table_elem._data == key &&
                current_table_elem._element_state != HashTableElement<T>::ElementState::DEL)
                return true;

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL)
                return false;
            main_hash = (main_hash + secondary_hash) % _table_data.size();

        }
    }

    bool remove(const T& key) {
        size_t main_hash = _hasher(key) % _table_data.size();
        const size_t secondary_hash = _hasher.secondary_hash(key) % _table_data.size();
        int counter = 0;
        for (; counter < _table_data.size(); ++counter) {
            if (main_hash >= _table_data.size())
                main_hash = 0;
            auto current_table_elem = _table_data[main_hash];
            if (current_table_elem._data == key && current_table_elem._element_state != HashTableElement<
                    T>::ElementState::DEL) {
                _table_data[main_hash]._element_state = HashTableElement<T>::ElementState::DEL;
                return true;
            }

            if (current_table_elem._element_state == HashTableElement<T>::ElementState::NIL)
                return false;
            main_hash = (main_hash + secondary_hash) % _table_data.size();
        }
    }

private:
    void rehash() {
        std::vector<HashTableElement<T>> new_table_data(_table_data.size() * 2);
        for (int i = 0; i < _table_data.size(); ++i) {
            auto elem = _table_data[i];
            size_t new_main_hash = _hasher(elem._data) % new_table_data.size();
            const size_t secondary_hash = _hasher.secondary_hash(elem._data) % new_table_data.size();

            if (new_table_data[new_main_hash]._element_state == HashTableElement<T>::ElementState::KEY) {
                int counter = 0;
                for (; counter < new_table_data.size(); ++counter) {
                    if (new_main_hash >= new_table_data.size())
                        new_main_hash = 0;
                    if (new_table_data[new_main_hash]._element_state == HashTableElement<T>::ElementState::NIL) {
                        new_table_data[new_main_hash] = elem;
                        break;
                    }
                    new_main_hash = (new_main_hash + secondary_hash) % new_table_data.size();
                }
            } else
                new_table_data[new_main_hash] = elem;
        }
        _table_data = new_table_data;
    }

    std::vector<HashTableElement<T>> _table_data;
    Hasher _hasher;
    float _number_of_filled;
};
