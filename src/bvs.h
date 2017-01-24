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
    Node *parent;
    int height = 1;
public:
    Node( int const number, Node *leftChild = nullptr, Node *rightChild = nullptr );
    Node() {}
    int getValue() const;
    Node *getLeft() const {return left;}
    Node *getRight() const {return right;}
    void setLeft(Node &newNode);
    void setRight(Node &newNode);
    void setValue(const int newData);
    int getHeight() const {return height;} //testy
    void setHeight(int newHeight) {height = newHeight;} //testy
    int left_height(); //testy
    int right_height(); //testy
    void setParent(Node *newData); //testy
    Node *getParent() const {return parent;}
    void setLeft(Node *node); //testy
    void setRight(Node *node); //testy
};

class BVS {
    std::string getInorder(Node &root) const;
    std::string getPreorder(Node &root) const;
    std::string getPostorder(Node &root) const;
    virtual Node *delNode(Node &currentNode, int data);//testy
protected:
    Node *root;
    std::pair<Node *,Node *> minNodeInSubtree(Node *currentNode) const; //testy
public:
    BVS() {}
    BVS( Node *node ) {root = node;}
    BVS( const int array[], const int size );
    Node *getRoot() {return root;}
    virtual bool insertNode(int data, Node *rootParam); //prerobit rootparam
    std::string inorder() const;
    std::string preorder() const;
    std::string postorder() const;
    bool isNode(int data) const;
    int getMax() const;
    int getMin() const;
    virtual void deleteNode(int data);
};

class AVL: public BVS {
    bool isBalanced(Node &node) const;
    void recomputeHeight(Node *node);
    void rebalance(Node *node);
    Node *tallChild(Node *node, bool favorleft = false);
    Node *tall_grandchild(Node *node);
    Node *restructure(Node *node);
    void rotate(Node *node);
    void relink(Node *parent, Node *child, bool make_left_child);
    void setRoot(Node *node) {root = node;}
    Node *delNode1(Node &currentNode, int data);//testy
public:
    AVL() {}
    AVL( const int array[], const int size ); //posielat dlzku array ako parameter
    bool insertNode(int data, Node *rootParam);
    void deleteNodeAVL(int data);
};

#endif //BVS_BVS_H

//AVL ->delete node
