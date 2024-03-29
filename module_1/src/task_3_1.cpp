#include <iostream>
#include "../include/Queue.hpp"


void IO(std::istream& input_stream, std::ostream& output_stream){
    int number, command_id, value, expected_value;
    bool isAllExpected = true;
    input_stream >> number;
    Queue queue(number);
    for (int i = 0; i < number; ++i){
        input_stream >> command_id >> value;
        switch (command_id) {
            case 2:
                expected_value = queue.Dequeue();
                if (expected_value != value){
                    isAllExpected = false;
                }
                break;
            case 3:
                queue.Enqueue(value);
                break;

            default:
                return;
        }
    }

    if (isAllExpected){
        output_stream << "YES";
    } else {
        output_stream << "NO";
    }
}
