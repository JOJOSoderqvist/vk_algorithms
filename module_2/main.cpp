#include "src/task_2_1.cpp"
#include "src/task_1_2.cpp"
#include "include/AVLTree.hpp"
int main() {
    //task_1_2::IO(std::cin, std::cout);
    AvlTree<int> tree;
    tree.add(10);
    std::cout << tree.has(10) << '\n';
    tree.add(4);
    std::cout << tree.has(4) << '\n';
    tree.add(3);
    std::cout << tree.has(3) << '\n';
    tree.add(9);
    std::cout << tree.has(9) << '\n';
    tree.remove(10);
    std::cout << tree.has(10) << '\n';
    std::cout << tree.has(5) << '\n';
    std::cout << tree.has(4) << '\n';
    std::cout << tree.has(9) << '\n';
}
