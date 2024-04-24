#include "../include/BinaryTree.hpp"
#include <stack>
#include <iostream>
#include <cassert>

void InOrder(const BinaryTree* tree, std::ostream& output_stream) {
    assert(tree->root != nullptr);
    std::stack<BinaryTree::Node*> stack;
    auto* current = tree->root;
    while (current != nullptr || !stack.empty()) {
        while (current != nullptr) {
            stack.push(current);
            current = current->left;
        }


        current = stack.top();
        stack.pop();
        output_stream << current->value << ' ';
        current = current->right;
    }
}


namespace task_2_1 {
    void IO(std::istream& input_stream, std::ostream& output_stream) {
        int num, elem;
        BinaryTree tree{};
        input_stream >> num;
        for (int i = 0; i < num; ++i) {
            input_stream >> elem;
            tree.insertNode(elem, defaultCompFunc);
        }
        InOrder(&tree, output_stream);
    }
}