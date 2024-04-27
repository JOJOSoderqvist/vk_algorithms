#include "../include/HashTable.hpp"
#include <iostream>
#include <string>

namespace task_1_2 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        HashTable<std::string> table;
        char op;
        std::string key;
        while (input_stream >> op >> key) {
            switch (op) {
                case '?':
                    output_stream << (table.has(key) ? "OK" : "FAIL") << std::endl;
                    break;
                case '+':
                    output_stream << (table.add(key) ? "OK" : "FAIL") << std::endl;
                    break;
                case '-':
                    output_stream << (table.remove(key) ? "OK" : "FAIL") << std::endl;
                    break;
                default:
                    return;
            }
        }
    }
}