#include <stdio.h>
#include <stdlib.h>


typedef int V;

typedef struct {
    int *Vet;
    int N;
    int C;
} Lista;

Lista* CriarLista();
void LiberarLista(Lista *Li);
void AumeVetor(Lista *Li);
void InserirFim(Lista *Li, V Va);
void InserirInicio(Lista *Li, V Va);
void InserirEm(Lista *Li, V Va, int i);
void Alterar(Lista *Li, V Va, int i);
V obter_primeiro(Lista *Li);
V obter_ultimo(Lista *Li);
V obter_em(Lista *Li, int i);
V RemoverPrime(Lista *Li);
V RemoverUlti(Lista *Li);
V RemoverEm(Lista *Li, int i);
int TamanhoLi(Lista* Li);
int ListaVazia(Lista *Li);
void LimparLista(Lista* Li);
void Imprimir(Lista* Li);
void ImprimirDes(Lista* Li);
void InserirOdernado(Lista* Li, V Va);
Lista UniaoLi(Lista* Li, Lista* Fi);
int VerifiLiOrde(Lista* Li);
int VeriLiFibo(Lista* Li);
int BuscaPosi(Lista *Li, V Va);
Lista UniaoLi(Lista* Li, Lista* Fi);
int contem_todos(Lista* l, Lista* a);
int listas_iguais(Lista* l, Lista* a);
Lista interseccao(Lista* Li, Lista* Fi);
Lista diferenca(Lista* Li, Lista* Fi);





int main() {


}


Lista* CriarLista() {
    Lista* Li;
    Li->N = 0;
    Li->C = 5;
    Li->Vet = (int*) malloc(Li->C*sizeof(int));
    return Li;
}
 

void LiberarLista(Lista *Li) {
     free(Li);
}

void AumeVetor(Lista * Li) {

    int NC = Li->C * 1.5;  
    int *V = malloc(NC * sizeof(int));

    for (int i = 0; i < Li->N; i++) {
        V[i] = Li->Vet[i];
    }

    free(Li->Vet);     // libera o antigo
    Li->Vet = V;     // aponta pro novo
    Li->C = NC;
} 

void InserirFim(Lista* Li, V Va) {
     if ( Li->C == Li->N) {
          AumeVetor(Li);
     } 

    Li->Vet[Li->N] = Va;
    Li->N++;
}

void InserirInicio(Lista *Li, V Va) {
     if (Li->N == Li->C) {
         AumeVetor(Li);        
     }
     int i = 0;

     for (int K = Li->N-1; K>= i; K--) {

         Li->Vet[K+1] = Li->Vet[K];
     }

     Li->Vet[i] = Va;
     Li->N++;
} 

void InserirEm(Lista *Li, V Va, int i) {
    if (i < 0 || i > Li->C) {
        printf("\n ERRO! Valor de i não pode ser menor do que 0 ou maior do que a capacidade da lista!");
    } else {
        if (Li->N == Li->C) {
            AumeVetor(Li);        
        }

        for (int K = Li->N-1; K>= i; K--) {

            Li->Vet[K+1] = Li->Vet[K];
        }

        Li->Vet[i] = Va;
        Li->N++;
    } 
        
} 


void Alterar(Lista* Li, V Va, int i) {
    if (i < 0 || i > Li->C) {
        printf("\n ERRO! Valor de i nao pode ser menor do que 0 ou maior do que a capacidade da lista!");
    } else {
        Li->Vet[i] = Va;
    }

}

V obter_primeiro(Lista *Li) {
    if (Li->N == 0) {
        printf("A lista está vazia!\n");
        return -1;
    } else {
        return Li->Vet[0];
    }
}

V obter_ultimo(Lista *Li) {
    if (Li->N == 0) {
        printf("A lista está vazia!\n");
        return -1;
    } else {
        return Li->Vet[Li->N-1];
    }
}

V obter_em(Lista *Li, int i) {
    if (i < 0 || i >= Li->N) {
        printf("\nERRO! Índice inválido!\n");
        return -1;
    } else {
        return Li->Vet[i];
    }
}

V RemoverPrime(Lista *Li) {
    if (Li->N == 0) {
        printf("\nA lista está vazia!\n");
        return -1;
    } else {
        V valor = Li->Vet[0];
        for (int K = 1; K < Li->N; K++) {
            Li->Vet[K-1] = Li->Vet[K];
        }
        Li->N--;
        return valor;
    }
}

V RemoverUlti(Lista *Li) {
    if (Li->N == 0) {
        printf("\nA lista está vazia!\n");
        return -1;
    } else {
        Li->N--;
        return Li->Vet[Li->N];
    }
}

V RemoverEm(Lista *Li, int i) {
    if (i < 0 || i >= Li->N) {
        printf("\nERRO! Índice inválido!\n");
        return -1;
    } else {
        V valor = Li->Vet[i];
        for (int K = i+1; K < Li->N; K++) {
            Li->Vet[K-1] = Li->Vet[K];
        }
        Li->N--;
        return valor;
    }
}


int TamanhoLi(Lista* Li) {
       return Li->N;
}

int ListaVazia(Lista* Li) {
    if (Li->N == 0) {
        return 1;
    } else {
        return 0;
    }
}

void LimparLista(Lista* Li) {
    V* A = (int*) malloc(Li->C*sizeof(int));
    Li->N = 0;
    Li->Vet = A;
}

//Questão 2


void ImprimirDes(Lista* Li) {
    for(int i =Li->N-1; i >= 0; i--) {
        printf("\nPosicao %d:%d", i, Li->Vet[i]);
    }
}

void Imprimir(Lista * Li) {
    for(int i =0; i<Li->N; i++) {
        printf("\nPosicao %d:%d", i, Li->Vet[i]);
    }
}

void InserirOdernado(Lista* Li, V Va) {
   
    if(Li->C == Li->N) {
        AumeVetor(Li);           
    }
    int pos = Li->N;

    for (int i = 0; i < Li->N; i++) {       
        if(Va < Li->Vet[i]) {
            pos = i;
            break;
        };
    }
    InserirEm(Li, Va, pos);
}

int VerifiLiOrde(Lista* Li) {
    if (Li->N == 0) {
        return 1;
    }

    for (int i = 0; i < Li->N - 1; i++) {
        if (Li->Vet[i] > Li->Vet[i + 1]) {
            return 0; 
        }
    }

    return 1; 
}

int VeriLiFibo(Lista* Li) {
    if (Li->N < 3) {
        return 1;
    }

    for (int i = 0; i < Li->N - 2; i++) {
        if (Li->Vet[i] + Li->Vet[i+1] != Li->Vet[i+2]) {
            return 0;
        }
    }

    return 1;
}


int BuscaPosi(Lista *Li, V Va) {
    for (int i = 0; i< Li->N-1; i++)  {
         if (Va == Li->Vet[i]) {
            return i;
         }
    }
}

Lista UniaoLi(Lista* Li, Lista* Fi) {
    int R;
    Lista* Uni;
    Uni->C = Li->N + Fi->N;
    Uni->Vet = (int) malloc(Li->C * sizeof(int));
    for (int i = 0; i <Li->N; i++) {
            Uni->Vet[i] = Li->Vet[i];
            Uni->N++;
    }
    
    for (int i = 0; i < Fi->N; i++) {
        R = 0;
        for (int j = 0; j < Uni->N; j++) {
            if (Uni->Vet[j] == Fi->Vet[i]) {
                R = 1;
                break;
            }
        }
        if (R == 0) { 
            Uni->Vet[Uni->N] = Fi->Vet[i];
            Uni->N++;
        }
    }
}

int contem_todos(Lista* l, Lista* a) {
    for (int i = 0; i < a->N; i++) {
        int encontrou = 0;
        for (int j = 0; j < l->N; j++) {
            if (a->Vet[i] == l->Vet[j]) {
                encontrou = 1;
                break;
            }
        }
        if (!encontrou) {
            return 0;
        }
    }
    return 1;
}

int listas_iguais(Lista* l, Lista* a) {
    if (l->N != a->N) {
        return 0;
    }
    
    for (int i = 0; i < a->N; i++) {
        int encontrou = 0;
        for (int j = 0; j < l->N; j++) {
            if (a->Vet[i] == l->Vet[j]) {
                encontrou = 1;
                break;
            }
        }
        if (!encontrou) {
            return 0;
        }
    }
    return 1;
}

Lista interseccao(Lista* Li, Lista* Fi) {
    Lista Inter;
    Inter.N = 0;
    
    if (Li->N < Fi->N) {
        Inter.C = Li->N;
    } else {
        Inter.C = Fi->N;
    }
    
    Inter.Vet = (int*)malloc(Inter.C * sizeof(int));
    
    for (int i = 0; i < Li->N; i++) {
        int encontrou = 0;
        for (int j = 0; j < Fi->N; j++) {
            if (Li->Vet[i] == Fi->Vet[j]) {
                encontrou = 1;
                break;
            }
        }
        if (encontrou) {
            Inter.Vet[Inter.N] = Li->Vet[i];
            Inter.N++;
        }
    }
    
    return Inter;
}

Lista diferenca(Lista* Li, Lista* Fi) {
    Lista Diff;
    Diff.N = 0;
    Diff.C = Li->N;
    Diff.Vet = (int*)malloc(Diff.C * sizeof(int));
    
    for (int i = 0; i < Li->N; i++) {
        int encontrou = 0;
        for (int j = 0; j < Fi->N; j++) {
            if (Li->Vet[i] == Fi->Vet[j]) {
                encontrou = 1;
                break;
            }
        }
        if (!encontrou) {
            Diff.Vet[Diff.N] = Li->Vet[i];
            Diff.N++;
        }
    }
    
    return Diff;
}