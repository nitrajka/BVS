// Copyright 2005, Google Inc.
// All rights reserved.
#include "gtest/gtest.h"
#include "../src/bvs.h"

using namespace ::testing;

//Node tests
TEST_F(Test, createNodeWithData ) {
    Node n(5);
    ASSERT_EQ( n.getValue(), 5);
}

TEST_F(Test, getLeftNode ) {
    Node n(5);
    Node m(6);
    Node k( 8, &m, &n );
    ASSERT_EQ( k.getLeft()->getValue(), m.getValue() );
}

TEST_F(Test, getRightNode ) {
    Node n(5);
    Node m(6);
    Node k( 8, &m, &n );
    ASSERT_EQ( k.getRight()->getValue(), n.getValue() );
}

TEST_F(Test, setLeftNode ) { //pridat testy na nullptr
    Node n(5);
    Node m(6);
    n.setLeft(m);
    ASSERT_EQ( n.getLeft()->getValue(), m.getValue() );
}

TEST_F(Test, setRightNode ) { //pridat testy na nullptr
    Node n(5);
    Node m(6);
    n.setRight(m);
    ASSERT_EQ( n.getRight()->getValue(), m.getValue() );
}

TEST_F(Test, setValue) {
    Node k(5);
    ASSERT_EQ(k.getValue(), 5);
    k.setValue(6);
    ASSERT_EQ(k.getValue(), 6);
}

//BVS tests
TEST_F(Test, HasRootTest) {
    Node n(5);
    BVS s(&n);
    ASSERT_EQ( s.getRoot()->getValue(), 5);
}

TEST_F(Test, dontCreateWithEmptyArray ) {
    int *a = new int [0];
    a[0] = '\0';
//    std::cout << "som tu" << std::endl;

    try {
        BVS bvs(a, 0);
    } catch(std::underflow_error const &err) {
        EXPECT_EQ( err.what(), std::string("Can't create empty bvs."));
    }

    int *b = new int [1];
    b[0] = '\0';
    BVS bvs(b, 1);
    ASSERT_EQ( bvs.getRoot()->getValue(), 0);
}


TEST_F(Test, InsertsNodes ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    ASSERT_EQ( bvs.getRoot()->getRight()->getValue(), 7 );
    ASSERT_EQ( bvs.getRoot()->getRight()->getRight()->getValue(), 8 );
    ASSERT_EQ( bvs.getRoot()->getRight()->getLeft()->getValue(), 6 );
    ASSERT_EQ( bvs.getRoot()->getLeft()->getValue(), 3 );
    ASSERT_EQ( bvs.getRoot()->getLeft()->getRight()->getValue(), 4 );
    ASSERT_EQ( bvs.getRoot()->getLeft()->getLeft()->getValue(), 2 );
}

TEST_F(Test, InitializesWithArray ) {
    int array[4] = {4,6,3,2};
    BVS bvs(array, 4);
    ASSERT_EQ( bvs.getRoot()->getValue(), 4 );
    ASSERT_EQ( bvs.getRoot()->getRight()->getValue(), 6 );
    ASSERT_EQ( bvs.getRoot()->getLeft()->getValue(), 3 );
    ASSERT_EQ( bvs.getRoot()->getLeft()->getLeft()->getValue(), 2 );
}

TEST_F(Test, inorder ) {
    int array[1] = {5};
    BVS bvs(array, 1);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    ASSERT_EQ( bvs.inorder(), "2,3,4,5,6,7,8");
}

TEST_F(Test, preorder ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    ASSERT_EQ( bvs.preorder(), "5,3,2,4,7,6,8" );
}

TEST_F(Test, postorder ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    ASSERT_EQ( bvs.postorder(), "2,4,3,6,8,7,5" );
}

TEST_F(Test, emptyInorderPreorderPostorder ) {
    Node n(5);
    BVS bvs(&n);
    bvs.deleteNode(5);
    ASSERT_EQ( bvs.inorder(), "" );
    ASSERT_EQ( bvs.preorder(), "" );
    ASSERT_EQ( bvs.postorder(), "" );
}

TEST_F(Test, isNode ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    ASSERT_EQ( bvs.isNode(2), true );
    ASSERT_EQ( bvs.isNode(20), false );
}

TEST_F(Test, isNodeInEmptyTree) {
    Node n(5);
    BVS bvs(&n);
    bvs.deleteNode(5);
    try {
        bvs.isNode(5);
    } catch(std::underflow_error const &err) {
        EXPECT_EQ( err.what(), std::string("Binary search tree instance is empty."));
    }
}

TEST_F(Test, getMax ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    ASSERT_EQ( bvs.getMax(), 8 );
}

TEST_F(Test, getMin ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    ASSERT_EQ( bvs.getMin(), 2 );
}

TEST_F(Test, getMaxANDgetMinInEmptyTree) {
    Node n(5);
    BVS bvs(&n);
    bvs.deleteNode(5);
    try {
        bvs.getMax();
    } catch(std::underflow_error const &err) {
        EXPECT_EQ( err.what(), std::string("Binary search tree instance is empty."));
    }

    try {
        bvs.getMin();
    } catch(std::underflow_error const &err) {
        EXPECT_EQ( err.what(), std::string("Binary search tree instance is empty."));
    }
}

//delete node + pridat testy na mazanie nullptr (osetrit v kode ci tam taky vrchol je)
TEST_F(Test, delLeafs ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.deleteNode(3);
    ASSERT_EQ( bvs.getRoot()->getLeft(), nullptr );
    bvs.deleteNode(7);
    ASSERT_EQ( bvs.getRoot()->getRight(), nullptr );
}

TEST_F(Test, deleteEmptyBVS ) {
    Node n(5);
    BVS bvs(&n);
    bvs.deleteNode(5);

    try {
        bvs.deleteNode(5);
    } catch(std::underflow_error const &err) {
        EXPECT_EQ( err.what(), std::string("Binary search tree instance is empty."));
    }

    bvs.insertNode(5, bvs.getRoot());
    ASSERT_EQ(bvs.getRoot()->getValue(), 5);
}

TEST_F(Test, delNodeWithLeftSon ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(3, bvs.getRoot());
    bvs.deleteNode(5);
    ASSERT_EQ( bvs.getRoot()->getLeft(), nullptr );
    ASSERT_EQ( bvs.getRoot()->getValue(), 3);

}

TEST_F(Test, delNodeWithRightSon ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.deleteNode(5);
    ASSERT_EQ( bvs.getRoot()->getRight(), nullptr );
    ASSERT_EQ( bvs.getRoot()->getValue(), 7);
}

TEST_F(Test, delNodeWithBothSonsInSimpleTree ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.deleteNode(5);
    ASSERT_EQ( bvs.getRoot()->getRight(), nullptr );
    ASSERT_EQ( bvs.getRoot()->getValue(), 7);
    ASSERT_EQ(bvs.getRoot()->getLeft()->getValue(), 3);
}

TEST_F(Test, delNodeWithBothSonsInComplexTree ) {
    Node n(5);
    BVS bvs(&n);
    bvs.insertNode(7, bvs.getRoot());
    bvs.insertNode(3, bvs.getRoot());
    bvs.insertNode(8, bvs.getRoot());
    bvs.insertNode(6, bvs.getRoot());
    bvs.insertNode(4, bvs.getRoot());
    bvs.insertNode(2, bvs.getRoot());
    bvs.deleteNode(5);
    ASSERT_EQ( bvs.getRoot()->getValue(), 6);
    ASSERT_EQ( bvs.getRoot()->getRight()->getValue(), 7 );
    ASSERT_EQ(bvs.getRoot()->getRight()->getLeft(), nullptr);
}

//AVL
TEST_F(Test, simpleLeftRotation) {
    int array[3] = {4,6,7};
    AVL avl(array, 3);
    ASSERT_EQ( avl.getRoot()->getValue(), 6 );
    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 7);
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 4);
    ASSERT_EQ( avl.getRoot()->getHeight(), 2);
    ASSERT_EQ( avl.getRoot()->getRight()->getHeight(), 1);
    ASSERT_EQ( avl.getRoot()->getLeft()->getHeight(), 1);
    ASSERT_EQ( avl.getRoot(), avl.getRoot()->getRight()->getParent());
    ASSERT_EQ( avl.getRoot(), avl.getRoot()->getLeft()->getParent());
}

TEST_F(Test, simpleRightRotation) {
    int array[3] = {4,3,2};
    AVL avl(array, 3);
    ASSERT_EQ( avl.getRoot()->getValue(), 3 );
    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 4);
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 2);
    ASSERT_EQ( avl.getRoot()->getHeight(), 2);
    ASSERT_EQ( avl.getRoot()->getRight()->getHeight(), 1);
    ASSERT_EQ( avl.getRoot()->getLeft()->getHeight(), 1);
    ASSERT_EQ( avl.getRoot(), avl.getRoot()->getRight()->getParent());
    ASSERT_EQ( avl.getRoot(), avl.getRoot()->getLeft()->getParent());
}

TEST_F(Test, rightLeftRotation ) {
    int array[3] = {4,6,5};
    AVL avl(array, 3);
    ASSERT_EQ( avl.getRoot()->getValue(), 5 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 4 );
    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 6 );
}

TEST_F(Test, leftRightRotation ) {
    int array[3] = {4,2,3};
    AVL avl(array, 3);
    ASSERT_EQ( avl.getRoot()->getValue(), 3 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 2 );
    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 4 );
}

TEST_F( Test, insertAVLNodesAndRebalance1 ) {
    int array[1] = { 7 };
    AVL avl( array, 1 );
    avl.insertNode( 8, avl.getRoot());
    avl.insertNode( 9, avl.getRoot());
    ASSERT_EQ( avl.getRoot()->getValue(), 8 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 7 );
    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 9 );
    avl.insertNode( 10, avl.getRoot());
    avl.insertNode( 6, avl.getRoot());
    avl.insertNode( 5, avl.getRoot());
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 6 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getValue(), 7 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getValue(), 5 );
    ASSERT_EQ( avl.inorder(), "5,6,7,8,9,10" );
}

TEST_F( Test, insertAVLNodesAndRebalance2 ) {
    int array[8] = {13,15,10,16,11,5,4,6};
    AVL avl(array, 8);
    ASSERT_EQ( avl.getRoot()->getValue(), 13 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 10 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getValue(), 11 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getValue(), 5 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getLeft()->getValue(), 4 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getRight()->getValue(), 6 );
    ASSERT_EQ( avl.inorder(), "4,5,6,10,11,13,15,16" );
    avl.insertNode( 7, avl.getRoot() );
    ASSERT_EQ( avl.getRoot()->getValue(), 13 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 6 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getValue(), 10 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getLeft()->getValue(), 7 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getRight()->getValue(), 11 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getValue(), 5 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getLeft()->getValue(), 4 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getRight(), nullptr );
    ASSERT_EQ( avl.inorder(), "4,5,6,7,10,11,13,15,16" );
}

//delete AVL Node tests
TEST_F( Test, deleteLeafsAVL ) {
    int array[6] = {7,8,9,10,6,5};
    AVL avl(array, 6);
    ASSERT_EQ( avl.inorder(), "5,6,7,8,9,10");
    avl.deleteNode(5);
    ASSERT_EQ( avl.inorder(), "6,7,8,9,10");
}

TEST_F(Test, deleteEmptyAVL ) {
    int array[1] = {5};
    AVL avl(array, 1);
    avl.deleteNode(5);

    try {
        avl.deleteNode(5);
    } catch(std::underflow_error const &err) {
        EXPECT_EQ( err.what(), std::string("Binary search tree instance is empty."));
    }

    avl.insertNode(5, avl.getRoot());
    ASSERT_EQ( avl.getRoot()->getValue(), 5);
}

TEST_F(Test, delNodeWithLeftSonInAVL ) {
    int array[8] = {5,7,3,8,6,4,2,1};
    AVL avl(array, 8);
    avl.deleteNode(2);
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 3 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getValue(), 1);
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getValue(), 4);
}

TEST_F(Test, delNodeWithRightSonInAVL ) {
    int array[8] = {5,7,3,8,6,4,2,9};
    AVL avl(array, 8);
    avl.deleteNode(8);
    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 7 );
    ASSERT_EQ( avl.getRoot()->getRight()->getLeft()->getValue(), 6);
    ASSERT_EQ( avl.getRoot()->getRight()->getRight()->getValue(), 9);
}

TEST_F(Test, delNodeWithBothSonsInSimpleTreeInAVLAndRebalance ) {
    int array[8] = {5,7,3,8,6,4,2,1};
    AVL avl(array, 8);
    avl.deleteNodeAVL(3);
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 2 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getValue(), 1);
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getValue(), 4);
}

TEST_F(Test, delLeafAndRebalance ) {
    int array[8] = {5,7,3,8,6,4,2,1};
    AVL avl(array, 8);
    avl.deleteNodeAVL(4);
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 2 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getValue(), 1);
    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getValue(), 3);
}

TEST_F(Test, delRootWithBothSonsInComplexTreeInAVLAndRebalance ) {
    int array[7] = {5,7,3,8,6,4,2};
    AVL avl(array, 7);
    avl.deleteNode(5);
    ASSERT_EQ( avl.getRoot()->getValue(), 6);
    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 7 );
    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 3);
    ASSERT_EQ( avl.getRoot()->getLeft()->getLeft()->getValue(), 2);
    ASSERT_EQ( avl.getRoot()->getRight()->getLeft(), nullptr);
}

