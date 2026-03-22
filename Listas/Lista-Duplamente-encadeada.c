#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int V;
    struct Node* Back;
    struct Node* Next;
} Node;

typedef struct {
    Node* End;
    Node* Start;
    int N;
} ListaDe;

ListaDe* CriarLista() {
    ListaDe* Li = malloc(sizeof(ListaDe));
    Li->End = NULL;
    Li->Start = NULL;
    Li->N = 0;
    return Li;
}

void LiberarListaDe(Node* No) {
    free(No);
}

Node* CriarNo(int V, Node* A, Node* B) {
    Node* No = malloc(sizeof(Node));
    No->Back = A;
    No->Next = B;
    No->V = V;
    return No;
}

void InsertStart(ListaDe* Li, int V) {
    Node* Aux = CriarNo(V, NULL, NULL);
    if(Li->Start) {
        Li->Start->Back = Aux;
        Aux->Next = Li->Start;
        Li->Start = Aux;
    } else {
        Li->Start = Li->End = Aux;
    }
    Li->N++;
}

void InsertEnd(ListaDe* Li, int V) {
    Node* Aux = CriarNo(V, NULL, NULL);
    if(Li->End) {
        Li->End->Next = Aux;
        Aux->Back = Li->End;
        Li->End = Aux;
    } else {
        Li->Start = Li->End = Aux;
    }
    Li->N++;
}

void InsertInMeio(ListaDe* Li, int V, int i) {
    if(i < 0 || i > Li->N) return;
    if(i == 0) {
        InsertStart(Li, V);
    } else if(i == Li->N) {
        InsertEnd(Li, V);
    } else {
        Node* Novo = CriarNo(V, NULL, NULL);
        Node* Atual;
        int metade = Li->N / 2;
        if(i <= metade) {
            Atual = Li->Start;
            for(int j = 0; j < i; j++)
                Atual = Atual->Next;
        } else {
            Atual = Li->End;
            for(int j = Li->N-1; j > i; j--)
                Atual = Atual->Back;
        }
        Node* Ant = Atual->Back;
        Ant->Next = Novo;
        Novo->Back = Ant;
        Novo->Next = Atual;
        Atual->Back = Novo;
        Li->N++;
    }
}

int RemoverPri(ListaDe* Li) {
    if(Li->Start == NULL) return -1;
    Node* Atual = Li->Start;
    int V = Atual->V;
    Li->Start = Li->Start->Next;
    if(Li->Start) Li->Start->Back = NULL;
    else Li->End = NULL;
    LiberarListaDe(Atual);
    Li->N--;
    return V;
}

int RemoverUlti(ListaDe* Li) {
    if(Li->End == NULL) return -1;
    Node* Atual = Li->End;
    int V = Atual->V;
    Li->End = Li->End->Back;
    if(Li->End) Li->End->Next = NULL;
    else Li->Start = NULL;
    LiberarListaDe(Atual);
    Li->N--;
    return V;
}

void RemoverIn(ListaDe* Li, int i) {
    if(i < 0 || i >= Li->N) return;
    if(i == 0) {
        RemoverPri(Li);
    } else if(i == Li->N-1) {
        RemoverUlti(Li);
    } else {
        Node* Atual = Li->Start;
        for(int j = 0; j < i; j++)
            Atual = Atual->Next;
        Node* Ant = Atual->Back;
        Node* Prox = Atual->Next;
        Ant->Next = Prox;
        Prox->Back = Ant;
        LiberarListaDe(Atual);
        Li->N--;
    }
}

int ObterEm(ListaDe* Li, int i) {
    if(i < 0 || i >= Li->N) return -1;
    Node* Atual = Li->Start;
    for(int j = 0; j < i; j++)
        Atual = Atual->Next;
    return Atual->V;
}

void Imprimir(ListaDe* Li) {
    Node* Atual = Li->Start;
    int pos = 0;
    while(Atual) {
        printf("Pos %d: %d\n", pos, Atual->V);
        Atual = Atual->Next;
        pos++;
    }
}

void ImprimirDes(ListaDe* Li) {
    Node* Atual = Li->End;
    int pos = Li->N - 1;
    while(Atual) {
        printf("Pos %d: %d\n", pos, Atual->V);
        Atual = Atual->Back;
        pos--;
    }
}


void InserirOrdenado(ListaDe* Li, int V) {
    int pos = Li->N;
    Node* Atual = Li->Start;

    for (int i = 0; i < Li->N; i++) {
        if (V < Atual->V) {
            pos = i;
            break;
        }
        Atual = Atual->Next;
    }
    InserirEm(Li, V, pos);
}

int VerifiOrde(ListaDe* Li) {
    if (Li->N <= 1) {
        return 1;
    } else {
        Node* Atual = Li->Start;
        for (int i = 0; i < Li->N - 1; i++) {
            if (Atual->V > Atual->Next->V)
                return 0;
            Atual = Atual->Next;
        }
        return 1;
    }
}

int VeriLiFibo(ListaDe* Li) {
    if (Li->N < 3) {
        return 1;
    }
    Node* Atual = Li->Start;
    while (Atual != NULL && Atual->Next != NULL && Atual->Next->Next != NULL) {
        if (Atual->V + Atual->Next->V != Atual->Next->Next->V) {
            return 0;
        }
        Atual = Atual->Next;
    }
    return 1;
}

int BuscaPosi(ListaDe* Li, int Va) {
    Node* Atual = Li->Start;
    for (int i = 0; i < Li->N; i++) {
        if (Va == Atual->V) {
            return i;
        }
        Atual = Atual->Next;
    }
    return -1;
}

ListaDe* UniListaDe(ListaDe* Li, ListaDe* Fi) {
    ListaDe* Uni = Li;
    Node* AtualFih = Fi->Start;

    while (AtualFih != NULL) {
        int R = 0;
        Node* AtualUni = Uni->Start;

        while (AtualUni != NULL) {
            if (AtualUni->V == AtualFih->V) {
                R = 1;
                break;
            }
            AtualUni = AtualUni->Next;
        }

        if (R == 0) {
            InsertEnd(Uni, AtualFih->V);
        }

        AtualFih = AtualFih->Next;
    }
    return Uni;
}

int BuscaPosiListDe(ListaDe* Li, int V) {
    if (Li->N == 0) {
        return -1;
    } else {
        Node* Atual = Li->Start;
        for (int i = 0; i < Li->N; i++) {
            if (Atual->V == V) {
                return i;
            }
            Atual = Atual->Next;
        }
        return -1;
    }
}

int ConteListDe(ListaDe* Li, ListaDe* Fi) {
    if (Fi->N == 0) {
        return 1;
    } else {
        Node* AtualFih = Fi->Start;
        for (int i = 0; i < Fi->N; i++) {
            if (BuscaPosiListDe(Li, AtualFih->V) == -1) {
                return 0;
            }
            AtualFih = AtualFih->Next;
        }
        return 1;
    }
}

int ListIguaDe(ListaDe* Li, ListaDe* Fi) {
    if (Li->N != Fi->N) {
        return 0;
    } else {
        Node* AtualFih = Fi->Start;
        for (int i = 0; i < Fi->N; i++) {
            if (buscar_posicao(Li, AtualFih->V) == -1) {
                return 0;
            }
            AtualFih = AtualFih->Next;
        }
        return 1;
    }
}

ListaDe* InterseListaDe(ListaDe* Li, ListaDe* Fi) {
    ListaDe* Nova = CriarLista();
    if (Li->N != 0 && Fi->N != 0) {
        Node* Atual = Li->Start;
        for (int i = 0; i < Li->N; i++) {
            if (buscar_posicao(Fi, Atual->V) != -1 &&
                buscar_posicao(Nova, Atual->V) == -1) {
                InsertEnd(Nova, Atual->V);
            }
            Atual = Atual->Next;
        }
    }
    return Nova;
}

ListaDe* DiferencaListDe(ListaDe* Li, ListaDe* Fi) {
    ListaDe* Nova = CriarLista();
    if (Li->N != 0) {
        Node* Atual = Li->Start;
        for (int i = 0; i < Li->N; i++) {
            if (buscar_posicao(Fi, Atual->V) == -1) {
                InsertEnd(Nova, Atual->V);
            }
            Atual = Atual->Next;
        }
    }
    return Nova;
}
