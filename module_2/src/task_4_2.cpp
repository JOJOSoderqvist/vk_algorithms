#include "../include/AVLTree.hpp"
#include <vector>
namespace task_4_2 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        AvlTree<int> tree;
        int count, number, stat;
        std::vector<int> stat_vector;
        input_stream >> count;
        for (int i = 0; i < count; ++i) {
            input_stream >> number >> stat;
            if (number > 0)
                tree.add(number);
            else
                tree.remove(std::abs(number));
            stat_vector.push_back(tree.kthStatistic(stat));
        }
        for (const auto elem: stat_vector) {
            output_stream << elem << '\n';
        }
    }
}