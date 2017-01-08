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
    int *array = new int[5];
    array[0] = 4;
    array[1] = 6;
    array[2] = 3;
    array[3] = 2;
    array[4] = '\0';
    BVS n(array);
    ASSERT_EQ( n.getRoot()->getValue(), 4 );
    ASSERT_EQ( n.getRoot()->getRight()->getValue(), 6 );
    ASSERT_EQ( n.getRoot()->getLeft()->getValue(), 3 );
    ASSERT_EQ( n.getRoot()->getLeft()->getLeft()->getValue(), 2 );
}

TEST_F(Test, inorder ) {
    Node n(5);
    BVS bvs(&n);
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
TEST_F( Test, initializesWithArray ) { //viac testov
    int *array = new int[6];
    array[0] = 4;
    array[1] = 6;
    array[2] = 3;
    array[3] = 2;
    array[4] = 1;
    array[5] = '\0';
    BVS bvs(array);
    ASSERT_EQ( bvs.getRoot()->getValue(), 4 );
    ASSERT_EQ( bvs.getRoot()->getLeft()->getValue(), 2 );
    ASSERT_EQ( bvs.getRoot()->getLeft()->getRight()->getValue(), 3 );
}


//TEST_F( Test, insertAVLNode ) { //viac testov
//    Node n(7);
//    AVL avl(&n);
//    avl.insertNode(8, avl.getRoot());
//    avl.insertNode(9, avl.getRoot());
//    ASSERT_EQ( avl.getRoot()->getValue(), 8);
//    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 7 );
//    ASSERT_EQ( avl.getRoot()->getRight()->getValue(), 9 );
//    avl.insertNode(10, avl.getRoot());
//    avl.insertNode(6, avl.getRoot());
//    avl.insertNode(5, avl.getRoot());
//    ASSERT_EQ( avl.getRoot()->getLeft()->getValue(), 6);
//    ASSERT_EQ( avl.getRoot()->getLeft()->getRight()->getValue(), 7 );
//    ASSERT_EQ( avl.getRoot()->getRight()->getLeft()->getValue(), 5 );
//    //koniec skontrolovat inorderom
//}

//delete AVL Node tests