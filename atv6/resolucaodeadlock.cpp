#include <iostream>
#include <vector>

using namespace std;

const int P = 5;  // Número de processos
const int R = 3;  // Número de recursos

// Função para verificar se o sistema está em estado seguro
bool isSafe(vector<int> &available, vector<vector<int>> &max, vector<vector<int>> &allocation, vector<vector<int>> &need) {
    vector<int> work = available;
    vector<bool> finish(P, false);
    vector<int> safeSequence;

    for (int count = 0; count < P; ++count) {
        bool found = false;
        for (int p = 0; p < P; ++p) {
            if (!finish[p]) {
                bool canProceed = true;
                for (int r = 0; r < R; ++r) {
                    if (need[p][r] > work[r]) {
                        canProceed = false;
                        break;
                    }
                }

                if (canProceed) {
                    for (int r = 0; r < R; ++r)
                        work[r] += allocation[p][r];
                    safeSequence.push_back(p);
                    finish[p] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            cout << "O sistema está em um estado inseguro!\n";
            return false;
        }
    }

    cout << "O sistema está em estado seguro.\nSequência segura: ";
    for (int i : safeSequence)
        cout << i << " ";
    cout << endl;

    return true;
}

// Função para alocar recursos e verificar se a operação é segura
bool requestResources(int p, vector<int> &available, vector<vector<int>> &max, vector<vector<int>> &allocation, vector<vector<int>> &need, vector<int> request) {
    // Verificando se o pedido é válido
    for (int r = 0; r < R; ++r) {
        if (request[r] > need[p][r]) {
            cout << "Erro: O processo " << p << " pediu mais recursos do que o necessário.\n";
            return false;
        }
        if (request[r] > available[r]) {
            cout << "Recursos não disponíveis para o processo " << p << ".\n";
            return false;
        }
    }

    // Testar alocação provisória
    for (int r = 0; r < R; ++r) {
        available[r] -= request[r];
        allocation[p][r] += request[r];
        need[p][r] -= request[r];
    }

    if (isSafe(available, max, allocation, need)) {
        cout << "Recursos alocados ao processo " << p << ".\n";
        return true;
    } else {
        // Desfazer a alocação provisória
        for (int r = 0; r < R; ++r) {
            available[r] += request[r];
            allocation[p][r] -= request[r];
            need[p][r] += request[r];
        }
        cout << "Recursos não podem ser alocados. Processo " << p << " deve esperar.\n";
        return false;
    }
}

int main() {
    vector<int> available = {3, 3, 2}; // Recursos disponíveis

    vector<vector<int>> max = {
        {7, 5, 3},
        {3, 2, 2},
        {9, 0, 2},
        {2, 2, 2},
        {4, 3, 3}
    };

    vector<vector<int>> allocation = {
        {0, 1, 0},
        {2, 0, 0},
        {3, 0, 2},
        {2, 1, 1},
        {0, 0, 2}
    };

    vector<vector<int>> need(P, vector<int>(R)); // Necessidade restante de cada processo
    for (int i = 0; i < P; ++i) {
        for (int j = 0; j < R; ++j) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }

    // Verificando se o sistema está inicialmente em estado seguro
    isSafe(available, max, allocation, need);

    // Processo 1 solicitando recursos (exemplo)
    vector<int> request = {1, 0, 2}; // Exemplo de pedido
    requestResources(1, available, max, allocation, need, request);

    return 0;
}
