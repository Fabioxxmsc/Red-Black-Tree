#include<stdio.h>
#include<stdlib.h>

typedef struct node node;
typedef struct tree tree;

struct node{
	char color; /** r -> vermelho, b -> preto */
	int data;
	node* parent;
	node* right;
	node* left;
};

struct tree{
    node* root;
};


//function declaration

node* treeMin(node* x);
void transplant(node* u, node* n);
void rbDelete(node* z);
void deleteFixup(node* x);
void delete();
node* treeSearch(node* x,int key);
node* grandparent(node* n);
node* uncle(node* n);
void print(node* n);
void insert();
void rightRotate(node* x);
void leftRotate(node* x);
void insert_case1(node* n);
void insert_case2(node* n);
void insert_case3(node* n);
void insert_case4(node* n);
void insert_case5(node* n);
void printChildren();
void print_tree(node *r, int l);


//functions

tree* rbt;
