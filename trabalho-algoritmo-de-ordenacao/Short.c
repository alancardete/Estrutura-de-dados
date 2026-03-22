/**
 * Trabalho de Ordenação - Algoritmos de Ordenação
 * 
 * Este programa implementa e compara diversos algoritmos de ordenação:
 * - Selection Sort
 * - Bubble Sort
 * - Insertion Sort
 * - Merge Sort
 * - Quick Sort
 * - Heap Sort
 * 
 * Funcionalidades:
 * - Geração de vetores aleatórios, crescentes e decrescentes
 * - Medição de tempo médio de execução
 * - Contagem de comparações e trocas
 * - Interface interativa com o usuário
 * 
 * Autor: [Seu Nome]
 * Data: [Data Atual]
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Variáveis globais para contagem de operações
long long comparacoes, trocas;

/**
 * Gera um vetor com diferentes tipos de ordenação
 * @param vetor Array a ser preenchido
 * @param n Tamanho do vetor
 * @param tipo 1=aleatório, 2=crescente, 3=decrescente
 */
void gerarVetor(int vetor[], int n, int tipo) {
    for (int i = 0; i < n; i++) {
        if (tipo == 1) 
            vetor[i] = rand() % 1000;
        else if (tipo == 2) 
            vetor[i] = i;
        else if (tipo == 3) 
            vetor[i] = n - i;
    }
}

/**
 * Cria um backup do vetor original
 * @param vetor Array original
 * @param n Tamanho do vetor
 * @return Ponteiro para o backup
 */
int* criarBackup(int vetor[], int n) {
    int *backup = malloc(n * sizeof(int));
    if (backup == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        backup[i] = vetor[i];
    }
    return backup;
}

/**
 * Selection Sort - Ordenação por seleção
 * Complexidade: O(n²) em todos os casos
 */
void selectionSort(int vetor[], int n) {
    comparacoes = 0;
    trocas = 0;
    
    for (int i = 0; i < n - 1; i++) {
        int min = i;
        for (int j = i + 1; j < n; j++) {
            comparacoes++;
            if (vetor[j] < vetor[min]) {
                min = j;
            }
        }
        if (min != i) {
            trocas++;
            int temp = vetor[i];
            vetor[i] = vetor[min];
            vetor[min] = temp;
        }
    }
}

/**
 * Bubble Sort - Ordenação por bolha
 * Complexidade: O(n²) no pior caso, O(n) no melhor caso
 */
void bubbleSort(int vetor[], int n) {
    comparacoes = 0;
    trocas = 0;
    
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            comparacoes++;
            if (vetor[j] > vetor[j + 1]) {
                trocas++;
                int temp = vetor[j];
                vetor[j] = vetor[j + 1];
                vetor[j + 1] = temp;
            }
        }
    }
}

/**
 * Insertion Sort - Ordenação por inserção
 * Complexidade: O(n²) no pior caso, O(n) no melhor caso
 */
void insertionSort(int vetor[], int n) {
    comparacoes = 0;
    trocas = 0;
    
    for (int i = 1; i < n; i++) {
        int key = vetor[i];
        int j = i - 1;
        
        while (j >= 0) {
            comparacoes++;
            if (vetor[j] > key) {
                trocas++;
                vetor[j + 1] = vetor[j];
                j--;
            } else {
                break;
            }
        }
        vetor[j + 1] = key;
    }
}

/**
 * Merge - Função auxiliar para intercalar subvetores
 */
void merge(int vetor[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    int *L = malloc(n1 * sizeof(int));
    int *R = malloc(n2 * sizeof(int));
    
    if (L == NULL || R == NULL) {
        printf("Erro: Falha na alocação de memória!\n");
        exit(1);
    }
    
    for (int i = 0; i < n1; i++) L[i] = vetor[left + i];
    for (int j = 0; j < n2; j++) R[j] = vetor[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    
    while (i < n1 && j < n2) {
        comparacoes++;
        if (L[i] <= R[j]) {
            vetor[k] = L[i];
            i++;
        } else {
            vetor[k] = R[j];
            j++;
        }
        k++;
        trocas++;
    }
    
    while (i < n1) {
        vetor[k] = L[i];
        i++;
        k++;
        trocas++;
    }
    
    while (j < n2) {
        vetor[k] = R[j];
        j++;
        k++;
        trocas++;
    }
    
    free(L);
    free(R);
}

/**
 * Merge Sort - Ordenação por intercalação
 * Complexidade: O(n log n) em todos os casos
 */
void mergeSort(int vetor[], int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(vetor, left, mid);
        mergeSort(vetor, mid + 1, right);
        merge(vetor, left, mid, right);
    }
}

/**
 * Partition - Função auxiliar para particionar o vetor no Quick Sort
 */
int partition(int vetor[], int low, int high) {
    int pivot = vetor[high];
    int i = (low - 1);
    
    for (int j = low; j <= high - 1; j++) {
        comparacoes++;
        if (vetor[j] < pivot) {
            i++;
            trocas++;
            int temp = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = temp;
        }
    }
    
    trocas++;
    int temp = vetor[i + 1];
    vetor[i + 1] = vetor[high];
    vetor[high] = temp;
    
    return (i + 1);
}

/**
 * Quick Sort - Ordenação rápida
 * Complexidade: O(n log n) no caso médio, O(n²) no pior caso
 */
void quickSort(int vetor[], int low, int high) {
    if (low < high) {
        int pi = partition(vetor, low, high);
        quickSort(vetor, low, pi - 1);
        quickSort(vetor, pi + 1, high);
    }
}

/**
 * Heapify - Função auxiliar para manter a propriedade de heap
 */
void heapify(int vetor[], int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;
    
    if (left < n) {
        comparacoes++;
        if (vetor[left] > vetor[largest]) 
            largest = left;
    }
    
    if (right < n) {
        comparacoes++;
        if (vetor[right] > vetor[largest]) 
            largest = right;
    }
    
    if (largest != i) {
        trocas++;
        int temp = vetor[i];
        vetor[i] = vetor[largest];
        vetor[largest] = temp;
        heapify(vetor, n, largest);
    }
}

/**
 * Heap Sort - Ordenação por heap
 * Complexidade: O(n log n) em todos os casos
 */
void heapSort(int vetor[], int n) {
    comparacoes = 0;
    trocas = 0;
    
    // Construir heap máximo
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(vetor, n, i);
    }
    
    // Extrair elementos do heap
    for (int i = n - 1; i >= 0; i--) {
        trocas++;
        int temp = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = temp;
        heapify(vetor, i, 0);
    }
}

/**
 * Imprime o vetor no formato legível
 */
void imprimirVetor(int vetor[], int n) {
    printf("[ ");
    for (int i = 0; i < n; i++) {
        printf("%d", vetor[i]);
        if (i < n - 1) printf(", ");
        if ((i + 1) % 10 == 0 && i < n - 1) {
            printf("\n  ");
        }
    }
    printf(" ]\n");
}

/**
 * Mede o tempo médio de execução para algoritmos simples
 */
double medirTempoMedio(void (*func)(int[], int), int vetor[], int backup[], int n) {
    int repeticoes = (n < 1000) ? 100 : 1;
    double totalTempo = 0;
    
    for (int r = 0; r < repeticoes; r++) {
        for (int i = 0; i < n; i++) 
            vetor[i] = backup[i];
            
        clock_t inicio = clock();
        func(vetor, n);
        clock_t fim = clock();
        
        totalTempo += ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
    }
    
    return totalTempo / repeticoes;
}

/**
 * Mede o tempo médio para o Merge Sort
 */
double medirTempoMerge(int vetor[], int backup[], int n) {
    int repeticoes = (n < 1000) ? 100 : 1;
    double total = 0;
    
    for (int i = 0; i < repeticoes; i++) {
        for (int j = 0; j < n; j++) 
            vetor[j] = backup[j];
            
        clock_t inicio = clock();
        mergeSort(vetor, 0, n - 1);
        clock_t fim = clock();
        
        total += ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
    }
    
    return total / repeticoes;
}

/**
 * Função principal do programa
 */
int main() {
    srand(time(NULL));
    int continuar = 1;
    
    printf("========================================\n");
    printf("   TRABALHO DE ALGORITMOS DE ORDENAÇÃO  \n");
    printf("========================================\n");
    printf("Desenvolvido por: [Seu Nome]\n");
    printf("Algoritmos implementados: Selection, Bubble,\n");
    printf("Insertion, Merge, Quick e Heap Sort\n");
    printf("========================================\n");
    
    while (continuar) {
        int n, tipo, opcao;
        
        printf("\n=== CONFIGURAÇÃO DO VETOR ===\n");
        printf("1 - Aleatório\n");
        printf("2 - Crescente\n");
        printf("3 - Decrescente\n");
        printf("Escolha o tipo de vetor: ");
        scanf("%d", &tipo);
        
        printf("Informe o tamanho do vetor: ");
        scanf("%d", &n);
        
        if (n <= 0) {
            printf("Erro: Tamanho de vetor inválido!\n");
            continue;
        }
        
        int *vetor = malloc(n * sizeof(int));
        if (vetor == NULL) {
            printf("Erro: Falha na alocação de memória!\n");
            return 1;
        }
        
        gerarVetor(vetor, n, tipo);
        int *backup = criarBackup(vetor, n);
        
        printf("\n=== OPÇÕES ===\n");
        printf("1 - Imprimir vetor original\n");
        printf("2 - Ordenar vetor\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        if (opcao == 1) {
            printf("\nVetor original:\n");
            imprimirVetor(vetor, n);
        } 
        else if (opcao == 2) {
            printf("\n=== ALGORITMOS DISPONÍVEIS ===\n");
            printf("1 - Selection Sort (O(n²))\n");
            printf("2 - Bubble Sort (O(n²))\n");
            printf("3 - Insertion Sort (O(n²))\n");
            printf("4 - Merge Sort (O(n log n))\n");
            printf("5 - Quick Sort (O(n log n))\n");
            printf("6 - Heap Sort (O(n log n))\n");
            
            int escolha;
            printf("\nOpcao: ");
            scanf("%d", &escolha);
            
            double tempo = 0;
            
            switch (escolha) {
                case 1:
                    tempo = medirTempoMedio(selectionSort, vetor, backup, n);
                    printf("\n✓ Selection Sort executado com sucesso!\n");
                    break;
                case 2:
                    tempo = medirTempoMedio(bubbleSort, vetor, backup, n);
                    printf("\n✓ Bubble Sort executado com sucesso!\n");
                    break;
                case 3:
                    tempo = medirTempoMedio(insertionSort, vetor, backup, n);
                    printf("\n✓ Insertion Sort executado com sucesso!\n");
                    break;
                case 4:
                    tempo = medirTempoMerge(vetor, backup, n);
                    printf("\n✓ Merge Sort executado com sucesso!\n");
                    break;
                case 5:
                    int repeticoes = (n < 1000) ? 100 : 1;
                    double total = 0;
                    
                    for (int r = 0; r < repeticoes; r++) {
                        for (int i = 0; i < n; i++) 
                            vetor[i] = backup[i];
                            
                        clock_t inicio = clock();
                        quickSort(vetor, 0, n - 1);
                        clock_t fim = clock();
                        
                        total += ((double)(fim - inicio)) / CLOCKS_PER_SEC * 1000.0;
                    }
                    
                    tempo = total / repeticoes;
                    printf("\n✓ Quick Sort executado com sucesso!\n");
                    break;
                case 6:
                    tempo = medirTempoMedio(heapSort, vetor, backup, n);
                    printf("\n✓ Heap Sort executado com sucesso!\n");
                    break;
                default:
                    printf("\n✗ Opção inválida!\n");
                    break;
            }
            
            if (escolha >= 1 && escolha <= 6) {
                printf("\n=== RESULTADOS ===\n");
                printf("Tempo médio: %.6f ms\n", tempo);
                printf("Comparações: %lld\n", comparacoes);
                printf("Trocas: %lld\n", trocas);
                
                int imprimir;
                printf("\nDeseja imprimir o vetor ordenado? (1 - Sim / 0 - Não): ");
                scanf("%d", &imprimir);
                
                if (imprimir == 1) {
                    printf("\nVetor ordenado:\n");
                    imprimirVetor(vetor, n);
                }
            }
        } else {
            printf("\n✗ Opção inválida!\n");
        }
        
        free(vetor);
        free(backup);
        
        printf("\n=== CONTINUAR ===\n");
        printf("Deseja realizar outra operação? (1 - Sim / 0 - Sair): ");
        scanf("%d", &continuar);
    }
    
    printf("\n========================================\n");
    printf("   PROGRAMA FINALIZADO COM SUCESSO!    \n");
    printf("========================================\n");
    
    return 0;
}