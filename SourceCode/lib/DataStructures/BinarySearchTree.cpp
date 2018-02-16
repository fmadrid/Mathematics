#include "BinarySearchTree.h"

int main() {

    BinarySearchTree<int> b;
    b.insert(1);
    b.insert(2);
    b.insert(3);
    printInOrder(b.root);
    return 0;

}
