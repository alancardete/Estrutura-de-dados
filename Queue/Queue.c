#include <stdio.h>
#include <stdlib.h>

#define V int

typedef struct {
    V* Vet;
    int N;
    int C;
    int Head;
    int Tail;
}Fila;

Fila* CriarFila() {
    Fila* Fi = malloc(sizeof(Fila));
    Fi->C = 5;
    Fi->N = 0;
    Fi->Vet = malloc(sizeof(int)*Fi->C);
    Fi->Head = 0;
    Fi->Tail = 0;
    return Fi;
}

void LiberarFila(Fila* Fi) {
    free(Fi->Vet);
    free(Fi);
}

void InserirFila(Fila* Fi, V Va) {
    if(Fi->N == Fi->C) {
        printf("A fila está cheia\n");
        return;
    }
    Fi->Vet[Fi->Tail] = Va;
    Fi->Tail = (Fi->Tail + 1) % Fi->C;
    Fi->N++;
}

V ObterInicio(Fila* Fi) {
    if(Fi->N == 0) {
        printf("A fila está vazia\n");
        return 0;
    }else {
        return Fi->Vet[Fi->Head];
    }
}

V RemoverFila(Fila* Fi) {
    if(Fi->N == 0) {
        printf("A fila está vazia\n");
        return 0;
    }else {
        V X = Fi->Vet[Fi->Head];
        Fi->Head = (Fi->Head + 1) % Fi->C;
        Fi->N--;
        return X;
    }
}

int TamanhoFila(Fila* Fi) {
    return Fi->N;
}

int FilaVazia(Fila* Fi) {
    if(Fi->N == 0) {
        return 1;
    }else {
        return 0;
    }
}

void LimparFila(Fila* Fi) {
    Fi->Head = 0;
    Fi->Tail = 0;
    Fi->N = 0;
}

void ImprimirFila(Fila* F) {
    Fila* A = CriarFila();
    while(!FilaVazia(F)) {
        V x = RemoverFila(F);
        printf("%d\n", x);
        InserirFila(A, x);
    }
    while(!FilaVazia(A)) InserirFila(F, RemoverFila(A));
    LiberarFila(A);
}
int FilasIguais(Fila* A, Fila* B) {
    Fila* T1 = CriarFila();
    Fila* T2 = CriarFila();
    int ok = 1;

    while(!FilaVazia(A) && !FilaVazia(B)) {
        V x = RemoverFila(A);
        V y = RemoverFila(B);
        if(x != y) ok = 0;
        InserirFila(T1, x);
        InserirFila(T2, y);
    }

    if(!FilaVazia(A) || !FilaVazia(B)) ok = 0;

    while(!FilaVazia(T1)) InserirFila(A, RemoverFila(T1));
    while(!FilaVazia(T2)) InserirFila(B, RemoverFila(T2));

    LiberarFila(T1);
    LiberarFila(T2);
    return ok;
}


void InverterFila(Fila* F) {
    Fila* A = CriarFila();
    Fila* B = CriarFila();
    while(!FilaVazia(F)) InserirFila(A, RemoverFila(F));
    while(!FilaVazia(A)) {
        V x = RemoverFila(A);
        Fila* T = CriarFila();
        while(!FilaVazia(B)) InserirFila(T, RemoverFila(B));
        InserirFila(B, x);
        while(!FilaVazia(T)) InserirFila(B, RemoverFila(T));
        LiberarFila(T);
    }
    while(!FilaVazia(B)) InserirFila(F, RemoverFila(B));
    LiberarFila(A);
    LiberarFila(B);
}


Fila* ClonarFila(Fila* F) {
    Fila* Nova = CriarFila();
    Fila* A = CriarFila();
    while(!FilaVazia(F)) {
        V x = RemoverFila(F);
        InserirFila(Nova, x);
        InserirFila(A, x);
    }
    while(!FilaVazia(A)) InserirFila(F, RemoverFila(A));
    LiberarFila(A);
    return Nova;
}

typedef struct {
    int fluxo;
    int dado;
}Pacote;

typedef struct {
    Pacote* Vet;
    int N;
    int C;
    int Head;
    int Tail;
}FilaPacote;

FilaPacote* CriarFilaPacote() {
    FilaPacote* Fi = malloc(sizeof(FilaPacote));
    Fi->C = 10;
    Fi->N = 0;
    Fi->Vet = malloc(sizeof(Pacote)*Fi->C);
    Fi->Head = 0;
    Fi->Tail = 0;
    return Fi;
}

void InserirPacote(FilaPacote* Fi, int fluxo, int dado) {
    Pacote P;
    P.fluxo = fluxo;
    P.dado = dado;
    Fi->Vet[Fi->Tail] = P;
    Fi->Tail = (Fi->Tail + 1) % Fi->C;
    Fi->N++;
}

Pacote RemoverPacote(FilaPacote* Fi) {
    Pacote P = Fi->Vet[Fi->Head];
    Fi->Head = (Fi->Head + 1) % Fi->C;
    Fi->N--;
    return P;
}

void Multiplexar() {
    Fila* F1 = CriarFila();
    Fila* F2 = CriarFila();
    Fila* F3 = CriarFila();
    int x;

    printf("Fluxo 1: ");
    while(scanf("%d",&x) && x != -1) InserirFila(F1,x);
    printf("Fluxo 2: ");
    while(scanf("%d",&x) && x != -1) InserirFila(F2,x);
    printf("Fluxo 3: ");
    while(scanf("%d",&x) && x != -1) InserirFila(F3,x);

    printf("\nF1:\n"); ImprimirFila(F1);
    printf("\nF2:\n"); ImprimirFila(F2);
    printf("\nF3:\n"); ImprimirFila(F3);

    FilaPacote* Canal = CriarFilaPacote();

    while(!FilaVazia(F1) || !FilaVazia(F2) || !FilaVazia(F3)) {
        if(!FilaVazia(F1)) { int v = RemoverFila(F1); InserirPacote(Canal,1,v); }
        if(!FilaVazia(F2)) { int v = RemoverFila(F2); InserirPacote(Canal,2,v); }
        if(!FilaVazia(F3)) { int v = RemoverFila(F3); InserirPacote(Canal,3,v); }
    }

    printf("\nCanal multiplexado:\n");
    while(Canal->N > 0) {
        Pacote P = RemoverPacote(Canal);
        printf("(%d, %d) ",P.fluxo,P.dado);
    }
    printf("\n");
}



void Demultiplexar() {
    FilaPacote* Canal = CriarFilaPacote();
    int fluxo, dado;

    printf("Digite pares fluxo valor (-1 para parar):\n");
    scanf("%d",&fluxo);
    while(fluxo != -1) {
        scanf("%d",&dado);
        InserirPacote(Canal,fluxo,dado);
        scanf("%d",&fluxo);
    }

    printf("\nCanal:\n");
    for(int i = 0; i < Canal->N; i++) {
        int idx = (Canal->Head + i) % Canal->C;
        printf("(%d, %d) ", Canal->Vet[idx].fluxo, Canal->Vet[idx].dado);
    }
    printf("\n");

    Fila* F1 = CriarFila();
    Fila* F2 = CriarFila();
    Fila* F3 = CriarFila();

    while(Canal->N > 0) {
        Pacote P = RemoverPacote(Canal);
        if(P.fluxo == 1) InserirFila(F1, P.dado);
        if(P.fluxo == 2) InserirFila(F2, P.dado);
        if(P.fluxo == 3) InserirFila(F3, P.dado);
    }

    printf("\nFluxo 1:\n"); ImprimirFila(F1);
    printf("\nFluxo 2:\n"); ImprimirFila(F2);
    printf("\nFluxo 3:\n"); ImprimirFila(F3);
}


int main() {

}
