#include "../include/BinaryTree.hpp"
#include <stack>
#include <iostream>


void InOrder(const BinaryTree* tree, std::ostream& output_stream) {
    std::stack<BinaryTree::Node*> stack;
    auto* current = tree->root;
    while (current != nullptr) {
        stack.push(current);
        current = current->left;

    }

    while (!stack.empty()) {
        current = stack.top();
        stack.pop();
        output_stream << current->value;
        current = current->right;
    }

}