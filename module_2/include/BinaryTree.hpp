#pragma once
#include <iostream>
#include <stack>


class BinaryTree {
public:
    struct Node {
        Node* parent;
        Node* left;
        Node* right;
        int value;

        explicit Node() : parent(nullptr), left(nullptr), right(nullptr), value(0) {
        }

        explicit Node(const int value) : parent(nullptr), left(nullptr), right(nullptr), value(value) {
        }

        Node(Node* left, Node* right, const int value) : parent(nullptr), left(left), right(right), value(value) {
        }
    };

    Node* root;
    BinaryTree() {
        root = new Node();
    }

    explicit BinaryTree(const int value) {
        root = new Node(value);
    }

    ~BinaryTree() {
        std::stack<Node*> s1, s2;
        s1.push(root);
        while (!s1.empty()) {
            auto elem = s1.top();
            s1.pop();
            s2.push(elem);
            if (elem->left != nullptr)
                s1.push(elem->left);
            if (elem->right != nullptr)
                s1.push(elem->right);
        }
        while (!s2.empty()) {
            const auto to_remove = s2.top();
            std::cout << to_remove->value;
            s2.pop();
            delete to_remove;
        }
    }

    void insertNode(const int value) {
        auto* temp = root;
        if (root == nullptr) {
            root = new Node(value);
            return;
        }
        while (temp != nullptr) {
            if (value < temp->value) {
                if (temp->left != nullptr) {
                    temp = temp->left;
                } else {
                    auto* child = new Node(value);
                    child->parent = temp;
                    temp->left = child;
                    break;
                }
            } else {
                if (temp->right != nullptr) {
                    temp = temp->right;
                } else {
                    auto* child = new Node(value);
                    child->parent = temp;
                    temp->right = child;
                    break;
                }
            }
        }
    }
};
