//
// Created by Alexandra Nyitraiova on 27/12/16.
//

#include "bvs.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>

using namespace std;

Node::Node(int const number, Node *leftChild, Node *rightChild ) {
    data = number;
    left = leftChild;
    right = rightChild;
}

int Node::getValue() const {
    return data;
}

Node *Node::getLeft() const {
    return left;
}

Node *Node::getRight() const {
    return right;
}

void Node::setLeft( Node &newNode ) {//ano, este to opravim, resp, zamyslim sa nad tym
    left = new Node;
    if( &newNode != nullptr ) {
        *left = newNode;
        return;
    }
    left = nullptr;
    return;
}

void Node::setRight( Node &newNode ) { //ano, este to opravim, resp, zamyslim sa nad tym
    right = new Node;
    if( &newNode != nullptr ) {
        *right = newNode;
        return;
    }
    right = nullptr;
    return;
}

void Node::setParent( Node *newNode ) {//ano, este to opravim, resp, zamyslim sa nad tym
    parent = new Node;
    if( &newNode != nullptr ) {
        parent = newNode;
        return;
    }
    parent = nullptr;
    return;
}

void Node::setValue(const int newData) {
    data = newData;
}

int Node::left_height() {
    return (left != nullptr) ? left->getHeight() : 0;
}

int Node::right_height() {
    return (right != nullptr) ? right->getHeight() : 0;
}

//BVS
BVS::BVS(const int *array ) {
    root = new Node(array[0]);
    const int *pom = array;
    pom++;

    while( *pom != '\0' ) { // ano este to opravim
        insertNode( *pom, root);
        pom++;
    }
}

bool BVS::insertNode(int data, Node *rootParam ) {

    if( data > rootParam->getValue() ) {
//        cout << "I'm going right? like" << endl;
        if( rootParam->getRight() == nullptr ) {
//            cout << "vytvaram praveho syna" << endl;
            Node k(data);
            rootParam->setRight(k);
            return true;
        }
       return insertNode(data, rootParam->getRight() );
    }

    if( data < rootParam->getValue() ) {
//        cout << "I'm going left" << endl;
        if( rootParam->getLeft() == nullptr ) {
//            cout << "vytvaram laveho syna" << endl;
            Node k(data);
            rootParam->setLeft(k);
            return true;
        }
        return insertNode(data, rootParam->getLeft());
    }

    return false;
}

string BVS::getInorder(Node &node) const {
   if( &node == nullptr ) {
       return "";
   }
    return getInorder(*node.getLeft()) + "," + to_string(node.getValue()) + getInorder(*node.getRight());
}

string BVS::inorder() const {
    string result = getInorder(*root);
    return result.substr(1,result.length());
}

string BVS::getPreorder(Node &root) const {
    if( &root == nullptr ) {
        return "";
    }
    return "," + to_string(root.getValue()) + getPreorder(*root.getLeft()) + getPreorder(*root.getRight());
}

string BVS::preorder() const {
    string result = getPreorder(*root);
    return result.substr(1,result.length());
}

string BVS::getPostorder(Node &node) const {
    if( &node == nullptr ) {
        return "";
    }
    return getPostorder(*node.getLeft()) + getPostorder(*node.getRight()) + "," + to_string(node.getValue());
}

string BVS::postorder() const {
    string result = getPostorder(*root);
    return result.substr(1,result.length());
}

bool BVS::isNode(int data) const {
    Node *startRoot = root;
    while( startRoot != nullptr ) {
        if( startRoot->getValue() == data ) {
            return true;
        }

        if ( data < startRoot->getValue() ) {
            startRoot = startRoot->getLeft();
        }

        if( data > startRoot-> getValue() ) {
            startRoot = startRoot->getRight();
        }
    }
    return false;
}

int BVS::getMax() const {
    Node *startRoot = root;
    while( startRoot->getRight() != nullptr ) {
        startRoot = startRoot->getRight();
    }
    return startRoot->getValue();
}

int BVS::getMin() const {
    Node *startRoot = root;
    while( startRoot->getLeft() != nullptr ) {
        startRoot = startRoot->getLeft();
    }
    return startRoot->getValue();
}

pair<Node *,Node *> BVS::minNodeInSubtree( Node *rootNode ) const { //ci sa neprepise parent po prepisani rootNode
    Node *parent = nullptr;
    while( rootNode->getLeft() != nullptr ) {
        parent = rootNode;
        rootNode = rootNode->getLeft();
    }
    return make_pair( parent, rootNode);
}

Node *BVS::delNode(Node &rootNode, int data) { //komenty budem este potrebovat, zmazem neskor
    if( data > rootNode.getValue() ) {
        Node *k = delNode( *rootNode.getRight(), data );
        rootNode.setRight( *k );
    }

    if( data < rootNode.getValue() ) {
//        cout << "deleting lower node " << endl;
//        cout << "left node value: " << rootNode.getLeft()->getValue() << endl;
        Node *n = delNode( *rootNode.getLeft(), data );
//        cout << "created new node: "  << n << endl;
        rootNode.setLeft( *n );
//        cout << "left node value" << rootNode.getLeft() << endl;
    }

    if( data == rootNode.getValue() ) {
        if( rootNode.getLeft() == nullptr && rootNode.getRight() == nullptr ) {
//            cout << "no children: "  << rootNode.getValue() << endl;
            Node *p = nullptr;
            return p;
        } else if ( rootNode.getLeft() != nullptr && rootNode.getRight() == nullptr ) {
//            cout << "left son: " << endl;
            return rootNode.getLeft();
        } else if( rootNode.getLeft() == nullptr && rootNode.getRight() != nullptr ) {
            return rootNode.getRight();
        } else {
//            cout << "2 children: " << rootNode.getValue() << endl;
            //looking for the leftest son in right subtree -> it's value should be near to the root's
            pair<Node *, Node *> parentAndNode = minNodeInSubtree( rootNode.getRight() );

            if( parentAndNode.first == nullptr ) {
                Node *p = nullptr;
                rootNode.setRight( *p );
            } else {
                Node *k = delNode( *parentAndNode.second , parentAndNode.second->getValue() );
                parentAndNode.first->setLeft( *k );
            }

            rootNode.setValue(parentAndNode.second->getValue());
        }
    }
    return &rootNode;
}

void BVS::deleteNode( int data ) {
    root = delNode(*root, data);
}

//AVL
AVL::AVL( const int *array ) {
    root = new Node(array[0]);
    Node *v = nullptr;
    root->setParent(v);
    const int *pom = array;
    pom++;

    while( *pom != '\0' ) { // ano, neskor, viem.
        insertNode( *pom, root);
        pom++;
    }
};

bool AVL::insertNode(int data, Node *rootParam) {
    cout << endl;
    if( data > rootParam->getValue() ) {
        if( rootParam->getRight() == nullptr ) {
            Node k(data);
            rootParam->setRight(k);
            rootParam->getRight()->setParent( rootParam );
            rebalance( rootParam->getRight() );
            return true;
        }
        return insertNode(data, rootParam->getRight() );
    }

    if( data < rootParam->getValue() ) {
        if( rootParam->getLeft() == nullptr ) {
            Node k(data);
            rootParam->setLeft(k);
            rootParam->getLeft()->setParent( rootParam );
            rebalance( rootParam->getLeft() );
            return true;
        }
        return insertNode(data, rootParam->getLeft());
    }

    return false;
};

bool AVL::deleteNode(int data) {
    return true;
};

void AVL::rebalance(Node *node) {
//    cout << "rebalancing: " << node->getValue() << endl;
    int oldHeight = 0;
    Node *k = new Node(5);

    while( node != nullptr && k != nullptr ) { // pozor na toto lebo prepises nejaky node
        cout << endl << endl;
//        cout << "rebalancing: " << node->getValue() << endl;
        oldHeight = node->getHeight();
        if( !isBalanced(*node) ) {
            cout << "HURRRAAAAAAAAAAAAA" << endl;
            cout << node->getValue() << " is not balanced" << endl;
            Node *pom = tall_grandchild(node);
            node = restructure( pom );
            recomputeHeight( node->getLeft() );
            recomputeHeight( node->getRight() );
        }
        recomputeHeight(node);
//        cout << "node height after recomputing: " << node->getHeight() << endl;
//        cout << "right height after recomputing: " << node->right_height() << endl;
        if( node->getHeight() == oldHeight && node->getHeight() != 1 ) { //som pridala ze vyska nie je 1
            k = nullptr; //aby po pridani noveho prvku recomputol vsetky pred nim
        } else {
            if( node->getParent() == nullptr ) { //pom_node = pom_node->getParent() ak parent je nullptr-> segmFault
//                cout << "parent nebude" << endl;
                k = nullptr;
            } else {
//                cout << "parent bude: " << node->getParent()->getValue() << endl;
                node = node->getParent();
//                cout << "height of right child after recomp: " << node->getRight()->getHeight() << endl;
            }
//            pom_node = *pom_node.getParent();
        }
    }
};

bool AVL::isBalanced( Node &node ) const {
    cout << node.left_height() << " - " << node.right_height() << endl;
    return abs(node.left_height() - node.right_height()) <= 1;
}

void AVL::recomputeHeight(Node *node) {
//    cout << "old height is: " << node->getHeight() << endl;
//    cout << "recomputing height left: " << node->left_height() << " right: " << node->right_height() << endl;
//    cout << "max of heights: " << max(node->left_height(), node->right_height()) << endl;
    node->setHeight(1 + max(node->left_height(), node->right_height()) );
//    cout << "height of " << node->getValue() << " was set to " << node->getHeight() << endl;
}

Node *AVL::tallChild(Node *node, bool favorleft) {
    if( node->left_height() + favorleft > node->right_height() ) {
        return node->getLeft();
    }
    return node->getRight();
};

Node *AVL::tall_grandchild(Node *node) {
    Node *child = tallChild( node );
    bool alignment = ( child == node->getLeft());
    return tallChild( child, alignment);
};

Node *AVL::restructure(Node *node) {
    Node *y = node->getParent();
    Node *z = y->getParent();

    if( ( node == y->getRight() ) ==  ( y == z->getRight()) ) {
        rotate( y );
        return y;
    } else {
        rotate(node);
        rotate(node);
        return node;
    }
}

void AVL::rotate(Node *node) {
    Node *x = node;
    Node *y = x->getParent();
    Node *z = y->getParent();

    if( z == nullptr ) {
        setRoot( *x );
        Node *k = nullptr;
        x->setParent( k );
    } else {
        relink(*z, *x, (y == z->getLeft()) );
    }

    if( x == y->getLeft() ) {
        relink( *y, *x->getRight(), true );
        relink( *x, *y, false);
    } else {
        relink( *y, *x->getLeft(), false );
        relink( *x, *y, true );
    }
}

void AVL::relink(Node &parent, Node &child, bool make_left_child) {
    if( make_left_child ) {
        parent.setLeft(child);
    } else {
        parent.setRight(child);
    }

    if( &child != nullptr ) {
        child.setParent(&parent);
    }
}
