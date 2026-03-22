#include <stdio.h>
#include <stdlib.h>


#define V int

typedef struct {
    int N;
    int C;
    V* Vet;
}Pilha;

Pilha* CriarPilha() {
    Pilha* Pi = malloc(sizeof(Pilha));
    Pi->C = 5;
    Pi->N = 0;
    Pi->Vet = (int*) malloc(sizeof(int)*Pi->C);
    return Pi;
}

void LiberarPilha(Pilha* Pi) {
    free(Pi->Vet);
}


void AumePi(Pilha* Li) {

    int NC = Li->C * 1.5;  
    int *Vi = malloc(NC * sizeof(int));

    if(Vi == NULL) {
        printf("Erro de alocação!\n");
    }
    for (int i = 0; i < Li->N; i++) {
        Vi[i] = Li->Vet[i];
    }

    free(Li->Vet);     // libera o antigo
    Li->Vet = Vi;     // aponta pro novo
    Li->C = NC;
} 

void Push(Pilha* Pi, V Va){
    if(Pi->C == Pi->N) {
        AumePi(Pi);    
    }
    Pi->Vet[Pi->N] = Va;
     Pi->N++;
}

V ObterTopo(Pilha* Pi) {
    return Pi->Vet[Pi->N-1];
}

V Pop(Pilha* Pi) {
    if(Pi->N == 0) {
        printf("A LISTA ESTÁ VAZIA!");
    }else {
        int Aux = Pi->Vet[Pi->N-1];
        Pi->Vet[Pi->N-1] = NULL;
        Pi->N--;
        return Aux;
    }
}

int TamanhoPi(Pilha* Pi) {
    return Pi->N;
}

int VazioPi(Pilha* Pi) {
    if(Pi->N == 0) {
       return 1;
    }else {
        return 0;
    }
}

void LimparPi(Pilha* Pi) {
    int *V2 = malloc(sizeof(int)*Pi->C);
    LiberarPilha(Pi);
    Pi->Vet = V2;
    Pi->N = 0;
}

void ImpriPilha(Pilha *Pi) {
    printf("Pilha:\n");
    printf("^\n");
    for(int i = Pi->N-1; i>=0; i--){
        printf(" | %d\n", Pi->Vet[i]);
    }
}

int PiIgual(Pilha* Pi, Pilha* Fih) {
    if(Pi->N == Fih->N) {
        for(int i = 0; i<Pi->N;i++) {
            if (Pi->Vet[i] != Fih->Vet[i]) {
                printf("TESTE!");
                return 0;
            }
        }
        printf("TESTE2");
        return 1;
    }else {
        printf("A pilha não contém o mesmo numeros de elementos\n");
    }
}

void DecimalBinario(int X, char* Sb) {
    if(X < 0) {
        printf("ERRO! O número tem que ser maior ou igual a 0");
    }else {
        Pilha *Binario = CriarPilha();

        while(X>0) {
            Push(Binario, X%2);
            X = X/2;
        }
 
        int i = 0;
        while (!VazioPi(Binario)) {
            Sb[i++] = Pop(Binario) + '0';
        }
         Sb[i] = '\0';
        LiberarPilha(Binario); 
    }

}

int VeriParenteses(char * Expressao) {
    Pilha* VP = CriarPilha();

     for (int i = 0; Expressao[i] != '\0'; i++) {
        if (Expressao[i] == '(') {
            Push(VP, '('); 
        }
        else {
           if (Expressao[i] == ')') {
                if (VazioPi(VP)) {
                    LiberarPilha(VP);
                    return 0; 
                }
                Pop(VP); 
            }
        }
    }

    int valido = VazioPi(VP); 
    LiberarPilha(VP);
    return valido;
}

int verificar_delimitadores(char* expressao) {
    Pilha *P = CriarPilha();

    for (int i = 0; expressao[i] != '\0'; i++) {
        char c = expressao[i];

       
        if (c == '(' || c == '[' || c == '{') {
            Push(P, c);                  
        }
       
        else {
            if (c == ')' || c == ']' || c == '}') {
                if (VazioPi(P)) {             
                    LiberarPilha(P);
                    return 0;
                }
                char topo = (char) Pop(P);    
                if (!((topo == '(' && c == ')') ||
                    (topo == '[' && c == ']') ||
                    (topo == '{' && c == '}'))) {
                    LiberarPilha(P);          
                    return 0;
                }
            }
        }
            
    }
  
    int valido = VazioPi(P); 
    LiberarPilha(P);
    return valido;
}    

void inverter(Pilha* p) {
    Pilha* aux = CriarPilha();

    while (!VazioPi(p)) {
        Push(aux, Pop(p));
    }

    while (!VazioPi(aux)) {
        Push(p, Pop(aux));
    }

    LiberarPilha(aux);
}

Pilha* clonar_pilha(Pilha* p) {
    Pilha* aux = CriarPilha();
    Pilha* clone = CriarPilha();

    while (!VazioPi(p)) {
        Push(aux, Pop(p));
    }

    while (!VazioPi(aux)) {
        int v = Pop(aux);
        Push(p, v);     
        Push(clone, v);  
    }

    LiberarPilha(aux);
    return clone;
}

int infixa_para_posfixa(char* In, char* Out) {
    Pilha* P = CriarPilha();
    int i = 0, j = 0;

    while (In[i] != '\0') {
        char c = In[i];

        if (c >= '0' && c <= '9') {
            Out[j++] = c;
        }
        else if (c == '(') {
            Push(P, c);
        }
        else if (c == ')') {
            while (!VazioPi(P) && ObterTopo(P) != '(') {
                Out[j++] = Pop(P);
            }
            if (VazioPi(P)) return 0;
            Pop(P);
        }
        else if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^') {
            int Pc = 0;
            if (c == '+' || c == '-') Pc = 1;
            if (c == '*' || c == '/') Pc = 2;
            if (c == '^') Pc = 3;

            while (!VazioPi(P)) {
                char t = ObterTopo(P);
                int Pt = 0;
                if (t == '+' || t == '-') Pt = 1;
                if (t == '*' || t == '/') Pt = 2;
                if (t == '^') Pt = 3;

                if (Pt >= Pc && t != '(') Out[j++] = Pop(P);
                else break;
            }
            Push(P, c);
        }
        else return 0;

        i++;
    }

    while (!VazioPi(P)) {
        char t = Pop(P);
        if (t == '(') return 0;
        Out[j++] = t;
    }

    Out[j] = '\0';
    return 1;
}

int main() {
    int N = 100;
    char D[50];
    DecimalBinario(N, D);
    printf("%s", D);


    
}