#ifndef SEARCH_TREE_H
#define SEARCH_TREE_H

template<class T>
class SearchTree<T> {
    Node<T> root*;

    Node<T>* findNode(T) const;
    T getMinimumValue() const;
    T getMaximumValue() const;
    Node<T> getPredecessor(Node<T>*) const;
    Node<T> getSuccessor(Node<T>*) const;
    void insertNode(Node<T>*);
    void deleteNode(Node<T>*);




};

#endif
