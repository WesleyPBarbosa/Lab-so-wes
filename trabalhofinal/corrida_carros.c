#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

sem_t* pista;           // Ponteiro para um array dinâmico de semáforos
int vencedor = -1;      // -1 indica que não há vencedor
int num_carros;         // Variável para armazenar o número de carros
int num_segmentos;      // Variável para armazenar o número de segmentos
void* carro(void* arg) {
    int id_carro = *(int*)arg;
    free(arg);

    usleep(rand() % 1000000);  // Atraso aleatório

    for (int i = 0; i < num_segmentos; i++) {
        sem_wait(&pista[i]);

        printf("Carro %d está no segmento %d\n", id_carro, i + 1);
        sleep(1);  // Simula o tempo no segmento

        sem_post(&pista[i]);
    }

    // Atualiza o vencedor, caso ainda não tenha sido determinado
    if (vencedor == -1) {
        vencedor = id_carro;
    }

    printf("Carro %d terminou a corrida!\n", id_carro);
    pthread_exit(NULL);
}

int main() {
    pthread_t* carros;
    srand(time(NULL));

    // Recebe as configurações da corrida
    printf("Informe o número de carros: ");
    scanf("%d", &num_carros);
    printf("Informe o número de segmentos na pista: ");
    scanf("%d", &num_segmentos);

    // Recebe a escolha do usuário para aposta
    int carro_escolhido;
    printf("Escolha um carro para apostar (1 a %d): ", num_carros);
    scanf("%d", &carro_escolhido);

    // Aloca memória para os semáforos e as threads de carros
    pista = malloc(num_segmentos * sizeof(sem_t));
    carros = malloc(num_carros * sizeof(pthread_t));

    // Inicializa os semáforos para cada segmento da pista (1 carro por vez)
    for (int i = 0; i < num_segmentos; i++) {
        sem_init(&pista[i], 0, 1);
    }

    // Cria as threads dos carros
    for (int i = 0; i < num_carros; i++) {
        int* id_carro = malloc(sizeof(int));
        *id_carro = i + 1;
        pthread_create(&carros[i], NULL, carro, id_carro);
    }

    // Espera o fim das threads dos carros
    for (int i = 0; i < num_carros; i++) {
        pthread_join(carros[i], NULL);
    }

    // Destroi os semáforos
    for (int i = 0; i < num_segmentos; i++) {
        sem_destroy(&pista[i]);
    }

    // Libera a memória alocada
    free(pista);
    free(carros);

    // Exibe o resultado da aposta do usuário
    printf("Carro %d venceu a corrida!\n", vencedor);
    if (carro_escolhido == vencedor) {
        printf("Parabéns! Você acertou o vencedor!\n");
    } else {
        printf("Que pena! Você errou. Tente novamente.\n");
    
    printf("Corrida finalizada!\n");
    return 0;
}}
