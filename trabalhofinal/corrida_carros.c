#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define NUM_CARROS 3        // Número de carros na corrida
#define NUM_SEGMENTOS 5     // Número de segmentos da pista

// Semáforos para cada segmento da pista
sem_t pista[NUM_SEGMENTOS];

// Função para a thread de cada carro
void* carro(void* arg) {
    int id_carro = *(int*)arg;
    free(arg);  // Libera a memória alocada para o identificador do carro

    // Adiciona um atraso aleatório antes de começar a corrida
    usleep(rand() % 1000000);  // Atraso entre 0 e 1 segundo

    for (int i = 0; i < NUM_SEGMENTOS; i++) {
        sem_wait(&pista[i]);  // Tenta entrar no segmento

        printf("Carro %d está no segmento %d\n", id_carro, i + 1);
        sleep(1);  // Simula o tempo que o carro leva para percorrer o segmento

        sem_post(&pista[i]);  // Libera o segmento
    }

    printf("Carro %d terminou a corrida!\n", id_carro);
    pthread_exit(NULL);
}

int main() {
    pthread_t carros[NUM_CARROS];
    srand(time(NULL));  // Inicializa o gerador de números aleatórios

    // Inicializa os semáforos para cada segmento da pista (1 carro por vez)
    for (int i = 0; i < NUM_SEGMENTOS; i++) {
        sem_init(&pista[i], 0, 1);
    }

    // Cria as threads dos carros
    for (int i = 0; i < NUM_CARROS; i++) {
        int* id_carro = malloc(sizeof(int));
        *id_carro = i + 1;
        pthread_create(&carros[i], NULL, carro, id_carro);
    }

    // Espera o fim das threads dos carros
    for (int i = 0; i < NUM_CARROS; i++) {
        pthread_join(carros[i], NULL);
    }

    // Destroi os semáforos
    for (int i = 0; i < NUM_SEGMENTOS; i++) {
        sem_destroy(&pista[i]);
    }

    printf("Corrida finalizada!\n");
    return 0;
}
