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

void Node::setLeft( Node &newNode ) {
//    cout << "new node: " << &newNode << endl;
    left = new Node;
//    cout << "created new node " << endl;
    if( &newNode != nullptr ) {
        *left = newNode;
        return;
    }
    left = nullptr;
    //    cout << "set new node: " << left << endl;
    return;

}

void Node::setRight( Node &newNode ) {
    right = new Node;
    if( &newNode != nullptr ) {
        *right = newNode;
        return;
    }
    right = nullptr;
    return;
}

void Node::setValue(const int newData) {
    data = newData;
}

//BVS
BVS::BVS(const int *array ) {
    root = new Node(array[0]);
    const int *pom = array;
    pom++;

    while( *pom != '\0' ) { //ako zistit dlzku pola? array.size() ? nie. neviem
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

string BVS::getInorder(Node &root) const {
   if( &root == nullptr ) {
       return "";
   }
    return getInorder(*root.getLeft()) + "," + to_string(root.getValue()) + getInorder(*root.getRight());
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

string BVS::getPostorder(Node &root) const {
    if( &root == nullptr ) {
        return "";
    }
    return getPostorder(*root.getLeft()) + getPostorder(*root.getRight()) + "," + to_string(root.getValue());
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

Node *BVS::delNode(Node &rootNode, int data) {
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
    const int *pom = array;
    pom++;

    while( *pom != '\0' ) { //ako zistit dlzku pola? array.size() ? nie. neviem
        insertNode( *pom, root);
        pom++;
    }
};

bool AVL::insertNode(int data, Node *rootParam) {
    if( data > rootParam->getValue() ) {
//        cout << "I'm going right? like" << endl;
        if( rootParam->getRight() == nullptr ) {
//            cout << "vytvaram praveho syna" << endl;
            Node k(data);
            rootParam->setRight(k);
            rebalance( *rootParam->getRight() );
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
            rebalance( *rootParam->getLeft() );
            return true;
        }
        return insertNode(data, rootParam->getLeft());
    }

    return false;
};

//TODO
bool AVL::deleteNode(int data) {

};

//TODO
void AVL::rebalance(Node &node) {
    int oldHeight = 0;
    while( &node != nullptr) {
        oldHeight = node.getHeight();
        if( !isBalanced(node)) {
            node = restructure( tall_grandchild(node) );
            recomputeHeight( *node.getLeft() );
            recomputeHeight( *node.getRight() );
        }
        recomputeHeight(node);
        if( node.getHeight() == oldHeight ) {
            node = nullptr;
        } else {
            node = node.getParent(); //TODO
        }
    }
};

bool AVL::isBalanced( Node &node ) const {
    //abs(node.left_height() - node.right_height()) <= 1
    return abs(node.left_height() - node.right_height()) <= 1;
}

void AVL::recomputeHeight(Node &node) {
    //node._height = 1 + max(node.left_height(), node.right_height())
    node.setHeight(1 + max(node.left_height(), node.right_height()) );
}

Node AVL::tallChild(Node *node, bool favorleft = false) {
    int pom = ( (favorleft == true) ? 1 : 0 );
    if( node->left_height() + pom > node->right_height() ) {
        return *node->getLeft();
    }
    return *node->getRight();
};

Node AVL::tall_grandchild(Node &node) {
    Node child = tallChild( &node );
    bool alignment = ( child == node.getLeft());
    return tallChild( &child, alignment);
};



