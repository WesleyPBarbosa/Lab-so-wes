#include <iostream>
#include <thread>
#include <mutex>

using namespace std;

// Mutexes (recursos compartilhados)
mutex recurso_1;
mutex recurso_2;

void processo_1() {
    cout << "Processo 1: Tentando adquirir Recurso 1\n";
    recurso_1.lock(); // Bloqueia o recurso 1
    cout << "Processo 1: Adquiriu Recurso 1\n";

    this_thread::sleep_for(chrono::milliseconds(100)); // Simula um atraso para aumentar a chance de impasse

    cout << "Processo 1: Tentando adquirir Recurso 2\n";
    recurso_2.lock(); // Bloqueia o recurso 2
    cout << "Processo 1: Adquiriu Recurso 2\n";

    // Libera os recursos
    recurso_2.unlock();
    recurso_1.unlock();
}

void processo_2() {
    cout << "Processo 2: Tentando adquirir Recurso 2\n";
    recurso_2.lock(); // Bloqueia o recurso 2
    cout << "Processo 2: Adquiriu Recurso 2\n";

    this_thread::sleep_for(chrono::milliseconds(100)); // Simula um atraso para aumentar a chance de impasse

    cout << "Processo 2: Tentando adquirir Recurso 1\n";
    recurso_1.lock(); // Bloqueia o recurso 1
    cout << "Processo 2: Adquiriu Recurso 1\n";

    // Libera os recursos
    recurso_1.unlock();
    recurso_2.unlock();
}

int main() {
    // Cria duas threads que representam os processos tentando adquirir os recursos
    thread t1(processo_1);
    thread t2(processo_2);

    // Espera que ambas as threads terminem (o que pode nunca acontecer devido ao impasse)
    t1.join();
    t2.join();

    return 0;
}
