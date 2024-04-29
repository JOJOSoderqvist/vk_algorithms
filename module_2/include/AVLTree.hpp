#pragma once

#include <iostream>

// дописать компаратор
template<typename T>
class AvlTree {
    struct Node {
        explicit Node(const T& data)
            : data(data), left(nullptr), right(nullptr), height(1), count(1) {
        }

        T data;
        Node* left;
        Node* right;
        size_t height;
        size_t count;
    };

public:
    AvlTree() : root(nullptr) {
    }

    ~AvlTree() {
        destroyTree(root);
    }

    void add(const T& data) {
        root = addInternal(root, data);
    }

    bool has(const T& data) {
        Node* tmp = root;
        while (tmp) {
            if (tmp->data == data)
                return true;
            if (tmp->data < data)
                tmp = tmp->right;
            else
                tmp = tmp->left;
        }
        return false;
    }

    void remove(const T& data) {
        root = removeInternal(root, data);
    }
private:
    void destroyTree(Node* node) {
        if (node) {
            destroyTree(node->left);
            destroyTree(node->right);
            delete node;
        }
    }

    Node* removeInternal(Node* node, const T& data) {
        if (!node)
            return nullptr;
        if (node->data < data)
            node->right = removeInternal(node->right, data);
        else if (node->data > data)
            node->left = removeInternal(node->left, data);
        else {
            Node* left = node->left;
            Node* right = node->right;

            delete node;

            if (!right)
                return left;

            std::pair<Node*, Node*> pair = findAndRemoveMin(right);
            Node* min = pair.second;
            min->right = pair.first;
            min->left = left;

            return doBalance(min);
        }

        return doBalance(node);
    }

    std::pair<Node*, Node*> findAndRemoveMin(Node* node) {
        if (!node->left) {
            return std::make_pair(node->right, node);
        }

        std::pair<Node*, Node*> res = findAndRemoveMin(node->left);
        node->left = res.first;
        Node* min_node = res.second;
        return std::make_pair(doBalance(node), min_node);
    }


    Node* addInternal(Node* node, const T& data) {
        if (!node)
            return new Node(data);
        if (node->data <= data)
            node->right = addInternal(node->right, data);
        else
            node->left = addInternal(node->left, data);

        return doBalance(node);
    }

    size_t getHeight(Node* node) {
        return node ? node->height : 0;
    }

    void fixHeight(Node* node) {
        node->height = std::max(getHeight(node->left), getHeight(node->right)) + 1;
    }

    void fixCount(Node* node) {
        if (node == nullptr)
            return;
        node->count = fixCount(node->left) + fixCount(node->right) + 1;
    }

    int getBalance(Node* node) {
        return getHeight(node->right) - getHeight(node->left);
    }

    Node* rotateLeft(Node* node) {
        Node* tmp = node->right;
        node->right = tmp->left;
        tmp->left = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    Node* rotateRight(Node* node) {
        Node* tmp = node->left;
        node->left = tmp->right;
        tmp->right = node;
        fixHeight(node);
        fixHeight(tmp);
        return tmp;
    }

    Node* doBalance(Node* node) {
        fixHeight(node);
        switch (getBalance(node)) {
            case 2: {
                if (getBalance(node->right) < 0)
                    node->right = rotateRight(node->right);
                return rotateLeft(node);
            }
            case -2: {
                if (getBalance(node->left) > 0)
                    node->left = rotateLeft(node->left);
                return rotateRight(node);
            }
            default:
                return node;
        }
    }
    Node* root;
};