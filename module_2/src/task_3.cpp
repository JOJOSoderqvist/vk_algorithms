#include "../include/BTree.hpp"
#include <iostream>
#include <queue>

template<typename T>
void BFSTreePrint(BTree<T> tree, std::ostream& output_stream) {
    std::queue<std::pair<typename BTree<T>::Node *, int>> queue;
    auto temp = tree.getRoot();
    int level = 1;

    queue.push({temp, level});
    while (!queue.empty()) {
        auto elem = queue.front();
        queue.pop();
        if (elem.second != level) {
            output_stream << '\n';
            level = elem.second;
        }
        for (const auto key: elem.first->keys)
            output_stream << key << ' ';

        if (!elem.first->children.empty()) {
            for (const auto child: elem.first->children)
                queue.push({child, elem.second + 1});
        }
    }
}


namespace task_3 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        int t, elem;
        input_stream >> t;
        BTree<int> tree(t);
        while (input_stream >> elem) {
            tree.Insert(elem);
        }
        BFSTreePrint(tree, output_stream);
    }
}
