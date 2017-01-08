//
// Created by Alexandra Nyitraiova on 27/12/16.
//
#include <string>

#ifndef BVS_BVS_H
#define BVS_BVS_H

class Node {
    int data;
    Node *left;
    Node *right;
    int height = 0;
public:
    Node( int const number , Node *leftChild = nullptr, Node *rightChild = nullptr );
    Node() {}
    int getValue() const;
    Node *getLeft() const;
    Node *getRight() const;
    void setLeft(Node &newNode);
    void setRight(Node &newNode);
    void setValue(const int newData);
    int getHeight() const {return height;} //testy
    void setHeight(int newHeight) {height = newHeight;} //testy
    int left_height(); //testy
    int right_height(); //testy
};

class BVS {
    std::string getInorder(Node &root) const;
    std::string getPreorder(Node &root) const;
    std::string getPostorder(Node &root) const;
    Node *delNode(Node &rootNode, int data);//testy
    std::pair<Node *,Node *> minNodeInSubtree(Node *rootNode) const; //testy
protected:
    Node *root;
public:
    BVS() {}
    BVS( Node *node ) {root = node;}
    BVS( const int *array );
    Node *getRoot() {return root;}
    bool insertNode(int data, Node *rootParam);
    std::string inorder() const;
    std::string preorder() const;
    std::string postorder() const;
    bool isNode(int data) const;
    int getMax() const;
    int getMin() const;
    void deleteNode(int data);
};

class AVL: public BVS {
    bool isBalanced(Node &node) const;
    void recomputeHeight(Node &node);
    void rebalance(Node &node);
    Node tallChild(Node *node, bool favorleft = false);
    Node tall_grandchild(Node &node);
public:
    AVL() {}
    AVL( const int *array );
    AVL( Node *node ) {root = node;}
    bool insertNode(int data, Node *rootParam);

    bool deleteNode(int data);


};

#endif //BVS_BVS_H

//pomocne triedy: Node + implementovat templates pre rozne values (string, int)

//constructor: kopirovaci
//destructor

//AVL