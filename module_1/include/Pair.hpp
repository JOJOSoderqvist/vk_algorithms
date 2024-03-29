#pragma once

template <typename T1, typename T2>
struct Pair {
    T1 _first;
    T2 _second;

    Pair() = default;

    Pair(T1 first, T2 second) {
        this->makePair(first, second);
    }

    void makePair(T1 first, T2 second) {
        _first = first;
        _second = second;
    }
};