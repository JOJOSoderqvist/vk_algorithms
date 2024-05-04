#pragma once

#include <iostream>
#include <vector>

template<typename T>
class BTree {
public:
    struct Node {
        explicit Node(const bool leaf): is_leaf(leaf) {
        }

        ~Node() {
            for (Node* child: children)
                delete child;
        }

        bool is_leaf;
        std::vector<T> keys;
        std::vector<Node *> children;
    };

    explicit BTree(const size_t min_degree): t(min_degree), root(nullptr) {
    }

    ~BTree() = default;

    void Insert(const T& key) {
        if (!root)
            root = new Node(true);

        if (isNodeFull(root)) {
            Node* newRoot = new Node(false);
            newRoot->children.push_back(root);
            root = newRoot;
            splitChild(root, 0);
        }

        insertNonFull(root, key);
    }

    [[nodiscard]] Node* getRoot() const { return root; }

private:

    bool isNodeFull(Node* node) {
        return node->keys.size() == 2 * t - 1;
    }

    void splitChild(Node* node, size_t index) {
        Node* child_to_split = node->children[index];
        Node* new_child = new Node(false);
        if (child_to_split->is_leaf)
            new_child->is_leaf = true;
        for (int i = 0; i < t - 1; ++i)
            new_child->keys.push_back(child_to_split->keys[i + t]);
        if (!child_to_split->is_leaf)
            for (int i = 0; i < t; ++i)
                new_child->children.push_back(child_to_split->children[i + t]);

        node->keys.insert(node->keys.begin() + index, child_to_split->keys[t - 1]);
        node->children.insert(node->children.begin() + index + 1, new_child);
        child_to_split->keys.erase(child_to_split->keys.begin() + t - 1, child_to_split->keys.end());
        if (!child_to_split->children.empty())
            child_to_split->children.erase(child_to_split->children.begin() + t, child_to_split->children.end());
    }

    void insertNonFull(Node* node, const T& key) {
        int pos = node->keys.size() - 1;

        if (node->is_leaf) {
            node->keys.resize(node->keys.size() + 1);
            while (pos >= 0 && key < node->keys[pos]) {
                node->keys[pos + 1] = node->keys[pos];
                --pos;
            }
            node->keys[pos + 1] = key;
        }
        else {
            while (pos >= 0 && key < node->keys[pos]) {
                --pos;
            }

            if (isNodeFull(node->children[pos + 1])) {
                splitChild(node, pos + 1);
                if (key > node->keys[pos + 1])
                    ++pos;
            }
            insertNonFull(node->children[pos + 1], key);
        }
    }

    size_t t;
    Node* root;
};
