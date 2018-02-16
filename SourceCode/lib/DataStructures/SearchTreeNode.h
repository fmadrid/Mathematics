#ifndef SEARCH_TREE_NODE_H
#define SEARCH_TREE_NODE_H

template<class T>
class SearchTreeNode<T> {
    T value;
    std::vector<Node*> children;

public:
    SearchTreeNode(T val) : value(val) {}

    T getValue() { return value; }
    std::vector<Node<T>*> getChildren() { return children; }

#endif
