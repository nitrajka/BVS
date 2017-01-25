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

void Node::setLeft( Node &newNode ) {//ano, este to opravim, resp, zamyslim sa nad tym
//    if( &newNode != nullptr ) {
//        left = new Node;
//        *left = newNode;
//    }
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

void Node::setLeft(Node *node) {
    left = node;
}

void Node::setRight( Node *node ) {
    right = node;
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
BVS::BVS(const int array[], const int size) {
    if( size <= 0 ) {
        throw underflow_error("Can't create empty bvs.");
    }

    root = new Node(array[0]);

    for ( int i = 0; i < size; i++ ) {
        insertNode( array[i], root);
    }
}

void BVS::insert( int data ) {
    if( root == nullptr ) {
        Node *n = new Node(data);
        root = n;
        return;
    }

    insertNode(data, getRoot());
}

bool BVS::insertNode(int data, Node *rootParam ) {
    if( data > rootParam->getValue() ) {
        if( rootParam->getRight() == nullptr ) {
            Node k(data);
            rootParam->setRight(k);
            return true;
        }
       return insertNode(data, rootParam->getRight() );
    }

    if( data < rootParam->getValue() ) {
        if( rootParam->getLeft() == nullptr ) {
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
    if( root == nullptr ) {
        return "";
    }
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
    if( root == nullptr ) {
        return "";
    }
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
    if( root == nullptr ) {
        return "";
    }
    string result = getPostorder(*root);
    return result.substr(1,result.length());
}

bool BVS::isNode(int data) const {
    if( root == nullptr ) {
        throw underflow_error("Binary search tree instance is empty.");
    }
    Node *startRoot = root;
    while( startRoot != nullptr ) {

        if ( data < startRoot->getValue() ) {
            startRoot = startRoot->getLeft();
        } else if( data > startRoot-> getValue() ) {
            startRoot = startRoot->getRight();
        } else {
            return true;
        }
    }
    return false;
}

int BVS::getMax() const {
    if( root == nullptr ) {
        throw underflow_error("Binary search tree instance is empty.");
    }

    Node *startRoot = root;
    while( startRoot->getRight() != nullptr ) {
        startRoot = startRoot->getRight();
    }
    return startRoot->getValue();
}

int BVS::getMin() const {
    if( root == nullptr ) {
        throw underflow_error("Binary search tree instance is empty.");
    }

    Node *startRoot = root;
    while( startRoot->getLeft() != nullptr ) {
        startRoot = startRoot->getLeft();
    }
    return startRoot->getValue();
}

pair<Node *,Node *> BVS::minNodeInSubtree( Node *currentNode ) const {
    Node *parent = nullptr;
    while( currentNode->getLeft() != nullptr ) {
        parent = currentNode;
        currentNode = currentNode->getLeft();
    }
    return { parent, currentNode };
}

Node *BVS::delNode(Node &currentNode, int data) {
    if( data > currentNode.getValue() ) {
        Node *k = delNode( *currentNode.getRight(), data );
        currentNode.setRight( *k );
    }

    if( data < currentNode.getValue() ) {
        Node *n = delNode( *currentNode.getLeft(), data );
        currentNode.setLeft( *n );
    }

    if( data == currentNode.getValue() ) {
        if( currentNode.getLeft() == nullptr && currentNode.getRight() == nullptr ) {
            return nullptr;
        } else if ( currentNode.getLeft() != nullptr && currentNode.getRight() == nullptr ) {
            return currentNode.getLeft();
        } else if( currentNode.getLeft() == nullptr && currentNode.getRight() != nullptr ) {
            return currentNode.getRight();
        } else {
            //looking for the leftest son in right subtree -> it's value should be near to the root's
            pair<Node *, Node *> parentAndNode = minNodeInSubtree( currentNode.getRight() );

            if( parentAndNode.first == nullptr ) {
                Node *p = nullptr;
                currentNode.setRight( *p );
            } else {
                Node *k = delNode( *parentAndNode.second , parentAndNode.second->getValue() );
                parentAndNode.first->setLeft( *k );
            }

            currentNode.setValue(parentAndNode.second->getValue());
        }
    }
    return &currentNode;
}

void BVS::deleteNode( int data ) {
    if( root == nullptr ) {
        throw underflow_error("Binary search tree instance is empty.");
    }
    root = delNode(*root, data);
}

//AVL
AVL::AVL( const int array[], const int size ) {
    if( size <= 0 ) {
        throw underflow_error("Can't create empty bvs.");
    }

    root = new Node(array[0]);
    Node *v = nullptr;
    root->setParent(v);

    for ( int i = 1; i < size; i++ ) {
        insertNode( array[i], root);
    }
};

void AVL::insert(int data) {
    if( root == nullptr ) {
        Node *n = new Node(data);
        root = n;
        return;
    }
    insertNode(data, getRoot());
}


bool AVL::insertNode(int data, Node *rootParam) {

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

void AVL::deleteNode(int data) {
    if( root == nullptr ) {
        throw underflow_error("Binary search tree instance is empty.");
    }
    root = delNode(*root, data);
}

Node *AVL::delNode(Node &currentNode, int data) {
    if( data > currentNode.getValue() ) {

        Node *n = delNode( *currentNode.getRight(), data );
        currentNode.setRight( *n );
        rebalance(currentNode.getRight());
    }

    if( data < currentNode.getValue() ) {
        Node *n = delNode( *currentNode.getLeft(), data );
        currentNode.setLeft( *n );
        rebalance(currentNode.getLeft());
    }

    if( data == currentNode.getValue() ) {
        if( currentNode.getLeft() == nullptr && currentNode.getRight() == nullptr ) {
            return nullptr;
        } else if ( currentNode.getLeft() != nullptr && currentNode.getRight() == nullptr ) {
            return currentNode.getLeft();
        } else if( currentNode.getLeft() == nullptr && currentNode.getRight() != nullptr ) {
            return currentNode.getRight();
        } else {
            //looking for the leftest son in right subtree -> it's value should be near to the root's
            pair<Node *, Node *> parentAndNode = minNodeInSubtree( currentNode.getRight() );

            if( parentAndNode.first == nullptr ) {
                Node *p = nullptr;
                currentNode.setRight( *p );
            } else {
                Node *k = delNode( *parentAndNode.second , parentAndNode.second->getValue() );
                parentAndNode.first->setLeft( *k );
            }

            currentNode.setValue(parentAndNode.second->getValue());
        }
    }
    return &currentNode;
}

void AVL::rebalance(Node *node) {
    int oldHeight = 0;
    Node *k = new Node(0); //because later I'm asking (k != nullptr) -> like switch

    while( node != nullptr && k != nullptr ) {
        oldHeight = node->getHeight();
        if( !isBalanced(*node) ) {
            Node *ex_node = node;
            Node *pom = tall_grandchild(node);
            node = restructure( pom );
            if( node->getParent() != nullptr ) {
                if( node->getParent()->getLeft() == ex_node ) {
                    node->getParent()->setLeft(node);
                } else if( node->getParent()->getRight() == ex_node ) {
                    node->getParent()->setRight(node);
                } else {
//                    cout << "REALLY UNEXPECTED" << endl;
                }
            }

            recomputeHeight( node->getLeft() );
            recomputeHeight( node->getRight() );
        }
        recomputeHeight(node);
        if( node->getHeight() == oldHeight && node->getHeight() != 1 ) {
            k = nullptr;
        } else {
            if( node->getParent() == nullptr ) {
                k = nullptr;
            } else {
                node = node->getParent();
                if( node->getLeft() != nullptr) {
                }
            }
        }
    }
};

bool AVL::isBalanced( Node &node ) const {
    return abs(node.left_height() - node.right_height()) <= 1;
}

void AVL::recomputeHeight(Node *node) {
    node->setHeight(1 + max(node->left_height(), node->right_height()) );
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
    Node *parent = node->getParent();
    Node *grandParent = parent->getParent();

    if( ( node == parent->getRight() ) ==  ( parent == grandParent->getRight()) ) {
        rotate( parent );
        return parent;
    } else {
        rotate(node);
        rotate(node);
        return node;
    }
}

void AVL::rotate(Node *node) {
    Node *x = node;
    Node *parent = x->getParent();
    Node *grandParent = parent->getParent();

    if( grandParent == nullptr ) {
        setRoot( x );
        x->setParent( nullptr );
    } else {
        relink( grandParent, x, (parent == grandParent->getLeft()) );
    }

    if( x == parent->getLeft() ) {
        relink( parent, x->getRight(), true );
        relink( x, parent, false);
    } else {
        relink( parent, x->getLeft(), false );
        relink( x, parent, true );
    }
}

void AVL::relink(Node *parent, Node *child, bool make_left_child) {
    if( make_left_child ) {
        parent->setLeft(child);
    } else {
        parent->setRight(child);
    }

    if( child != nullptr ) {
        child->setParent(parent);
    }
}
