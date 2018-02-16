#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H
#include <iostream>

template<class T>
struct Node {

    T value;
    Node<T>* parent;
    Node<T>* left;
    Node<T>* right;

    Node(T val) : Node(val, nullptr){}
    Node(T val, Node<T>* p) : value(val), parent(p), left(nullptr), right(nullptr) {}

};

template<class T>
struct BinarySearchTree {
    Node<T>* root = nullptr;

    void insert(T val) { insert(new Node<T>(val)); }
    void insert(Node<T>* node) {
        std::cout << "Inserting : " << node->value << "\n";
        Node<T>* currentNode = root;
        Node<T>* parentNode  = nullptr;
        std::cout <<"h\n";
        while(currentNode != nullptr) {
            std::cout <<"a\n";
            parentNode = currentNode;
            std::cout <<"b\n";
            currentNode = (node->value < currentNode->value) ? currentNode->left : currentNode->right;
            std::cout <<"c\n";

            std::cout << "h\n";
        }
        node->parent = parentNode;
        if(parentNode == nullptr) root = node;
        else if(node->value < parentNode->value) parentNode->left = node;
        else parentNode->right = node;

    }
};

template <class T>
void printInOrder(Node<T>* node) {

    if(node) {
        printInOrder(node->left);
        std::cout << node->value;
        printInOrder(node->right);
    }

}

#endif
