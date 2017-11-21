#include "lib.h"

/**
Uma função para verificar a estrutura da árvore e as cores dos nodos.
Imprime o nodo que você informa, e os filhos mais suas cores.
*/
void printChildren(){
	node* aux;
	int data;
	printf("Informe os dados do nodo: ");
	scanf("%d",&data);
	while(getchar()!='\n');

	aux=treeSearch(rbt->root,data);


	if(aux==NULL)	{
		printf("Nodo nao encontrado!!!\n");
	}else{
		printf("Nodo (%d,%c) possui: ",aux->data,aux->color);
		if(aux->left == NULL)
			printf(" Filho esquerda nulo ");
		else
			printf(" Filho esquerda (%d,%c) ",aux->left->data,aux->left->color);
		if(aux->right == NULL)
			printf(" Filho direita nulo \n");
		else
			printf(" Filho direita (%d,%c) \n",aux->right->data,aux->right->color);
	}
}


/**
Uma função que encontra o avô de um nodo.
*/
node* grandparent(node* n){
	if((n !=NULL) && (n->parent!=NULL))
	return n->parent->parent;
	/*if the grandparent is NULL it doesnt matter, the function will return a NULL pointer, but if the parent is NULL we will get a segmentation fault*/

	else
		return NULL;
}


/**
Função que encontra o tio de um nodo.
*/
node* uncle(node* n){
	node* g = grandparent(n);
	if (g==NULL)
	return NULL;//no grandparent no uncle!!!
	else if(n->parent == g->left)
	return g->right;
	else return g->left;
}


void leftRotate(node* x){
	node* y;

	y=x->right;

	x->right=y->left;

	if(y->left!=NULL)
	{
		y->left->parent=x;
	}

	y->parent=x->parent;
	if(x->parent==NULL){//if we are rotating the top
		rbt->root = y;
	}


	else if(x == x->parent->left){
		x->parent->left = y;
	}else
        x->parent->right = y;

	y->left = x;
	x->parent = y;
}

/**
Com a rotação, temos que mudar seis conexões para a
árvore levando em consideração a conexão principal.
*/
void rightRotate(node* x){
	node* y;
	y = x->left;

	x->left = y->right; /** Primeira */

	if(y->right != NULL){
		y->right->parent = x; /** Segunda */
	}

	y->parent = x->parent;   /** Terceira */

	if(x->parent == NULL){
		rbt->root = y;
	}

	else if(x == x->parent->left){
		x->parent->left = y;  /** Quarta */
	}

	else x->parent->right = y;  /** Quarta - Outro caso*/

	y->right = x;   /** Quinta */
	x->parent = y;  /** Sexta */
}

/**
Inserção
*/
void insert(){
	node* y = NULL;
	node* x = rbt->root;
	node* n = (node*)malloc(sizeof(node));

	printf("Informe os dados do nodo: ");
	scanf("%d",&n->data);
	while(getchar()!='\n');


   /**
   y é o pai de x e será o pai de z
   */
	while (x != NULL){
		y = x;

		if(n->data < x->data)
			x = x->left;
		else
            x = x->right;
	}

	n->parent = y;

	if (y == NULL){
		rbt->root = n;
	}

	else if (n->data < y->data){
		y->left = n;
	}
	else y->right = n;

	n->left = NULL;
	n->right = NULL;
	n->color = 'r';


	insert_case1(n);

}

void insert_case1(node* n)
{
	//no other elements n goes to the root
	if(n->parent == NULL){
        n->color = 'b';
	}else
        insert_case2(n);
}


void insert_case2(node* n){
	if(n->parent->color =='b')
		return;
	else
		insert_case3(n);
}

void insert_case3(node* n){
	node* u = uncle(n);
	node* g;

	if((u!=NULL) && (u->color=='r')){
		n->parent->color = 'b';
		u->color = 'b';
		g = grandparent(n);
		g->color = 'r';
		insert_case1(g);
	}else{
		insert_case4(n);
	}
}


void insert_case4(node* n){
	node* g = grandparent(n);

	if((n == n->parent->right) && (n->parent == g->left))	{
		leftRotate(n->parent);
		n = n->left; /*the pointer now points to the former parent*/
	}else if((n == n->parent->left) && (n->parent == g->right)){
		rightRotate(n->parent);
		n = n->right; // for case5 to work on the parent
	}

	insert_case5(n);
}


void insert_case5(node* n){
	node* g = grandparent(n);

	n->parent->color = 'b';
	g->color = 'r';

	if(n == n->parent->left)
		rightRotate(g);
	else
		leftRotate(g);
}



//recursive walk on the tree

void print(node* n){
	if(n != NULL){
		print(n->left);
		printf(" (%d,%c) ",n->data, n->color);
		print(n->right);
	}

}





node* treeMin(node* x){
	while(x->left!=NULL){
		x=x->left;
	}
	return x;
}


void transplant(node* u, node* n){
	if(u->parent == NULL)
		rbt->root = n;
	else if(u == u->parent->left)
		u->parent->left = n;
	else u->parent->right = n;


	if( n!= NULL)
	n->parent = u->parent;
}




void rbDelete(node* z){
	node* x;
	node* y = z;

	char y_original_color = y->color;

	if(z->left == NULL){
		x = z->right;
		transplant(z,z->right);
	}

	else if(z->right == NULL){
		x = z->left;
		transplant(z,z->left);
	}else{
        y= treeMin(z->right);
		y_original_color = y->color;
		x = y->right;

		if(y->parent == z && x!=NULL){
			x->parent = y;
		}else{
			transplant(y,y->right);
			y->right = z->right;
			if(y->right!=NULL)
			y->right->parent = y;

			transplant(z,y);
			y->left = z->left;
			y->left->parent = y;
			y->color = z->color;
		}
	}

	if(y_original_color == 'b' && x!=NULL){
		deleteFixup(x);
	}

}

void deleteFixup(node* x){

	node* w;

	while(x!=rbt->root && x->color == 'b'){
		if (x == x->parent->left){
			w = x->parent->right;

			if(w->color == 'r'){
				w->color = 'b';
				x->parent->color = 'r';
				leftRotate(x->parent);
				w = x->parent->right;
			}
			if(w->left->color == 'b' && w->right->color =='b'){
                w->color = 'r';
				x = x->parent;
			}else if(w->right->color == 'b'){
				w->left->color = 'b';
				w->color = 'b';
				rightRotate(w);
				w = x->parent->right;
				w->color = x->parent->color;
				x->parent->color ='b';
				w->right->color = 'b';
				leftRotate(x->parent);
				x = rbt->root;
			}
		}else{
			w = x->parent->left;

			if( w->color == 'r'){
				w->color = 'b';
				x->parent->color = 'r';
				rightRotate(x->parent);
				w = x->parent->left;
			}

			if(w->right->color == 'b' && w->left->color == 'b'){
				w->color ='r';
				x = x->parent;
			}else if(w->left->color == 'b'){
				w->right->color = 'b';
				w->color = 'b';
				leftRotate(w);
				w = x->parent->left;
				w->color = x->parent->color;
				x->parent->color ='b';
				w->left->color = 'b';
				rightRotate(x->parent);
				x = rbt->root;
			}
		}

	}
	if(x!=NULL)
	x->color = 'b';
}

void delete(){
	int data;
	node* aux;

	printf("Informe o valor a ser deletado: ");
	scanf("%d",&data);
	while(getchar()!='\n');

	aux=treeSearch(rbt->root,data);

	if(aux!=NULL){
		rbDelete(aux);
	}else
		printf("Nodo nao encontrado\n");

}



node* treeSearch(node* x,int key){

	while(x!=NULL && x->data!=key){
		if(x->data<key){
			x=x->right;
		}else{
			x=x->left;
		}
	}
	return x;
}

void print_tree(node *r, int l){
	int i;
	if(!r)
		return;
	print_tree(r->right, l + 1);
	for(i = 0; i < l; ++i)
		printf(" ");
	printf("(%d,%c)\n", r->data, r->color);
	print_tree(r->left, l + 1);
}
