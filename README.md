# Implementation of Binary Search Tree and AVL Tree in C++
With help of this project you can create BST or AVL, insert and delete nodes.
Firstly, to create BST or AVL we need to know how to create Node. So let's start with this.
Then I'll explain how to create BVS/AVL and how to insert and delete nodes in particular tree.

## Node

### without children

```
Node n(5);
n.getValue() == 5;
n.setValue(6);
n.getValue() == 6;
n.getLeft() == nullptr;
n.getRight() == nullptr;
```

### with children
```
Node n(5);
Node m(6);
Node k( 8, &m, &n );
n.getLeft()->getValue() == 6;
```

or

```
Node n(5);
Node m(6);
Node k(8);
n.setLeft(m);
n.setRight(k);
n.getLeft()->getValue() == 6;
n.getRight()->getValue() == 8;
```

## How to Work with BST?

### Create BST

##### with single node:

```
Node n(5);
BVS s(&n);
s.getRoot()->getValue() == 5;
```

##### with data in array

```
int array[4] = {4,6,3,2};
BVS bvs(array, 4);
bvs.getRoot()->getValue() == 4;
bvs.getRoot()->getRight()->getValue() == 6;
bvs.getRoot()->getLeft()->getValue() == 3;
bvs.getRoot()->getLeft()->getLeft()->getValue() == 2;
```

### Insert node:
```
int array[4] = {4,6,3,2};
BVS bvs(array, 4);
bvs.insert(7);
bvs.getRoot()->getRight()->getRight()->getValue() == 7;
```


### inorder, preorder, postorder
```
int array[] = {5, 7, 3, 8, 6, 4, 2};
BVS bvs(array, 7);
bvs.inorder() == "2,3,4,5,6,7,8";
bvs.preorder() == "5,3,2,4,7,6,8";
bvs.postorder() == "2,4,3,6,8,7,5";
```

### BST contains Node
```
int array[] = {5, 7, 3, 8, 6, 4, 2};
BVS bvs(array, 7);
bvs.isNode(2) == true;
```


### Delete node:
```
Node n(5);
BVS bvs(&n);
bvs.deleteNode(5);
bvs.getRoot() == nullptr;
```

if BST is empty, all of the functions (except insert) throw error.

```bvs.isNode(5); // error: "Binary search tree instance is empty."```

### getMin, getMax (gets Node with minimal/maximal value)
```
int array[] = {5, 7, 3, 8, 6, 4, 2};
BVS bvs(array, 7);
bvs.getMax() == 8;
bvs.getMin() == 2;
```

## How to Work with AVL?
### Create AVL

##### The only way how to create AVL is using array:
```
int array[3] = {4,6,7};
AVL avl(array, 3);
avl.getRoot()->getValue() == 6;
```
You can manipulate with your instance of AVL using the same methods as in BVS. Names of those methods are similar. The only differrence is in rebalancing subtrees in AVL instance, which is done automatically without your assistance.

You can use `insert(int data)` method for inserting node and `deleteNode(int data)` method
for deleting Node with given value. If you try to delete 'empty' AVL or use some other from the functions (except insert) when instance ist empty, an error will be thrown.
