#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <limits.h>

typedef struct nodo_a {
	int dato;
	struct nodo_a *izq;
	struct nodo_a *der;
}ARBOL;

int cuentaNodos(ARBOL *);
int treeType(ARBOL *);
int depth(ARBOL *);
int leafs(ARBOL *);
void muestraArbol(int,ARBOL *);
void preOrden(ARBOL *);
void enOrden(ARBOL *);
void postOrden(ARBOL *);
int busca(ARBOL *,int);
int min(ARBOL *);
int max(ARBOL *);
ARBOL *inserta(int,ARBOL *);
ARBOL *ordena(ARBOL *,ARBOL *);
ARBOL *elimina(ARBOL *,int);

//Cuenta los nodos del árbol
int cuentaNodos(ARBOL *p) {
	if(p == NULL)
		return 0;
	else
		return (cuentaNodos(p->izq)+1+cuentaNodos(p->der));
}

//Tree Type
int treeType(ARBOL *p) {

	if (leafs(p) == pow(2,(depth(p)-1)) && cuentaNodos(p) == pow(2,depth(p))-1)
		return 0;

	else if(cuentaNodos(p) == (2*(leafs(p))-1))
		return 1;

	else
		return 2;



}

//Depth
int depth(ARBOL *p){
	if(p!=NULL){
		int nIzq = depth(p->izq);
		int nDer = depth(p->der);

		if(nIzq > nDer){
			return nIzq+1;
		}
		else
			return nDer+1;
	}
}

//Leafs
int leafs(ARBOL *p){

	if(p != NULL){
		if((p -> izq == NULL) && (p -> der == NULL)){
			return 1;
		}
			return (leafs(p->izq) + leafs(p->der));
	}
	else{
		return 0;
	}
	/*switch (type) {
	case 1:
		return pow(2, depth(type, p, n));
		break;
	case 2:
		return ((n + 1) / 2);
		break;
	default:
		return INT_MIN;
		break;
	}*/
}

//Breadth first order
void muestraArbol(int nivel,ARBOL *p) {
	int i;
	if(p != NULL) {
		muestraArbol(nivel + 1,p -> der);
		printf("\n");
		for(i = 0;i < nivel;i++)
			printf(" ");
		printf("%d",p -> dato);
		muestraArbol(nivel + 1,p -> izq);
	}
}

//Pre Orden
void preOrden(ARBOL *p){
	if(p != NULL) {
		printf("%d - ",p -> dato);
		preOrden(p -> izq);
		preOrden(p -> der);
	}
}

//En Orden
void enOrden(ARBOL *p) {
	if(p != NULL) {
		enOrden(p -> izq);
		printf("%d - ",p -> dato);
		enOrden(p -> der);
	}
}

//Post Orden
void postOrden(ARBOL *p) {
	if(p != NULL) {
		postOrden(p -> izq);
		postOrden(p -> der);
		printf("%d - ",p -> dato);
	}
}

//Busca un elemento en el árbol
int busca(ARBOL *p,int dato) {
	if(p == NULL)
		return(INT_MIN);
	if(dato == p -> dato)
		return(1);
	if(dato < p -> dato)
		return(busca(p -> izq,dato));
	else
		return(busca(p -> der,dato));
}

//Busca el elemento mínimo
int min(ARBOL *p) {
	if(p == NULL)
		return(INT_MIN);
	else if(p -> izq == NULL)
		return(p -> dato);
	else
		return(min(p -> izq));
}

//Busca el elemento máximo
int max(ARBOL *p) {
	if(p == NULL)
		return(INT_MIN);
	else if(p -> der == NULL)
		return(p -> dato);
	else
		return(max(p -> der));
}

//Inserta un nodo
ARBOL *inserta(int dato,ARBOL *p) {
	if(p == NULL) {
		ARBOL *p = (ARBOL *)malloc(sizeof(ARBOL));
		p -> dato = dato;
		p -> izq = NULL;
		p -> der = NULL;
		return(p);
	}
	if(dato < p -> dato)
		p->izq = inserta(dato,p->izq);
	else
		p->der = inserta(dato,p->der);
	return(p);
}

//Ordena el árbol en el proceso de eliminación
ARBOL *ordena(ARBOL *p,ARBOL *s) {
	ARBOL *tmp;
	if(s -> der != NULL)
		s -> der = ordena(p,s -> der);
	else {
		tmp = s;
		p -> dato = s -> dato;
		s = s -> izq;
		free(tmp);
	}
	return(s);
}

// Busca y elimina un dato del árbol
ARBOL *elimina(ARBOL *p,int dato) {
	ARBOL *tmp;
	if(p == NULL)
		printf("\n\tÁrbol Vacío...");
	else if(dato < p -> dato)
		p -> izq = elimina(p -> izq,dato);
	else if(dato > p -> dato)
		p -> der = elimina(p -> der,dato);
	else {
		tmp = p;
		if(tmp -> der == NULL) {
			p = tmp -> izq;
			free(tmp);
		}
		else if(tmp -> izq == NULL) {
			p = tmp -> der;
			free(tmp);
		}
		else
			tmp -> izq = ordena(tmp,tmp -> izq);
	}
	return(p);
}

int main(void) {
	int n,i,dato,op;
	int type = 0;

	ARBOL *p = NULL;
	while(1){
		printf("\nOperaciones Básicas con un árbol Binario\n");
		printf("1. Llenar un árbol de forma aleatoria\n");
		printf("2. Llenar un árbol de forma manual\n");
		printf("3. Buscar un dato\n");
		printf("4. Suprimir un Dato\n");
		printf("5. Buscar Mínimo y Máximo\n");
		printf("6. Contar Nodos\n");
		printf("7. Ver Recorridos\n");
		printf("8. Ver árbol\n");
		printf("\nNuevas funciones:\n 9. Contar Hojas\n");
		printf("10. Profundidad\n");
		printf("11. Tipo de Arbol\n");
		printf("\n12. Salir\n");
		printf("\nElija una Opción: ");
		scanf("%d",&op);
		switch(op) {
			case 1:
				printf("Número de nodos del árbol: ");
				scanf("%d",&n);
				srand(time(NULL));
				for(i = 0;i < n;i++) {
					printf("\n\tElemento No. %d : ",i+1);
					dato = rand()/100000000;
					printf("Dato a insertar: %d\n",dato);
					p = inserta(dato,p);
				}
				break;
			case 2:
				printf("Número de nodos del árbol: ");
				scanf("%d",&n);
				for(i = 0;i < n;i++) {
					printf("\n\tElemento No. %d: ",i+1);
					scanf("%d",&dato);
					p = inserta(dato,p);
				}
				break;
      case 3:
        printf("\n\tDato a Buscar : ");
        scanf("%d",&dato);
        printf("\n\t");
        if(busca(p,dato) != INT_MIN)
        	printf("\n\tSe encontró el dato %d",dato);
        else
          printf("\n\t\aNo se encontró el dato %d",dato);
        break;
      case 4:
        printf("Dato a Suprimir: ");
    		scanf("%d",&dato);
    		elimina(p,dato);
    		break;
      case 5:
        printf("\n\n\tMínimo = %d",min(p));
        printf("\n\n\tMáximo = %d",max(p));
        break;
      case 6:
        printf("\n\n\tNodos: %d",cuentaNodos(p));
				break;
      case 7:
        printf("Recorrido en Pre-Orden:");
        preOrden(p);
        printf("Recorrido En Orden:");
        enOrden(p);
      	printf("Recorrido en Post-Orden:");
        postOrden(p);
      	break;
			case 8:
				printf("Árbol Binario");
				muestraArbol(0,p);
				break;
			case 9:
				printf("Numero de Hojas: %d\n", leafs(p));
				break;
			case 10:
				printf("Profundidad: %d\n", depth(p)-1);
				break;
			case 11:
				
				printf("Tipo de Arbol:\n");
				type = treeType(p);
				switch(type){
					case 0:
						printf("Arbol Binario Completo\n");
					break;
					case 1:
						printf("Arbol Estrictamente Binario\n");
					break;
					case 2:
						printf("Arbol Binario\n");
					break;
				}
				break;
			case 12:
     		break;
      }
    }
    
    return 0;
}
