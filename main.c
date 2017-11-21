#include "function.c"

int main(){

	rbt = malloc(sizeof(tree));

	char choice;
	do{

		printf(" MENU \n Árvore red-black\n pressione: \n i(inserir) \n d(deletar) \n r(mostrar toda estrutura)[bugado] \n p(mostrar) \n c(Imprimir os filhos de um nó) \n q(Sair)  ");
		scanf("%c",& choice);
		while(getchar() != '\n');
            switch(choice){
                case 'i':  /* Inserção */
                    insert();
                    break;
                case 'd':  /* Remoção */
                    delete();
                    break;
                case 'r':  /* Mostra toda estrutura */
                    if(!rbt->root)
                        printf("\nA arvore esta vazia\n");
                    else{
                        print_tree(rbt->root, (int)NULL);
                        printf("\n");
                    }
                case 'p':  /* Mostrar árvore */
                    printf("\n");
                    if(rbt->root != NULL)
                        printf("Raiz: (%d,%c)\n",rbt->root->data, rbt->root->color);
                    print(rbt->root);
                    printf("\n");
                    break;
                case 'c':  /* Mostrar filhos de um nodo*/
                    printChildren();
                    break;
                case 'q':  /* Sair */
                    printf("Finalizando!!!!\n");
                    break;
                default :
                    printf("Opcao incorreta");
            }

	}while(choice != 'q');
	return 0;
}
