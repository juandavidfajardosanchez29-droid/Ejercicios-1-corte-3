// Ejercicio 2: ATM
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class ATM {
private:
    const int denom[5] = {20, 50, 100, 200, 500};
    long long cantidad[5] = {0, 0, 0, 0, 0};   // billetes disponibles por denominación

public:
    ATM() {}

    void deposit(vector<int> banknotesCount) {
        for (int i = 0; i < 5; i++) cantidad[i] += banknotesCount[i];
    }

    vector<int> withdraw(int amount) {
        vector<int> usados(5, 0);
        long long restante = amount;

        // Voraz: de la denominación más grande a la más pequeña
        for (int i = 4; i >= 0; i--) {
            long long necesarios = restante / denom[i];
            long long tomar = min(necesarios, cantidad[i]);
            usados[i] = (int)tomar;
            restante -= tomar * denom[i];
        }

        if (restante != 0) return {-1};   // no se pudo: NO se modifica el cajero

        for (int i = 0; i < 5; i++) cantidad[i] -= usados[i];
        return usados;
    }
};

void imprimir(const vector<int>& v) {
    cout << "[";
    for (size_t i = 0; i < v.size(); i++) cout << v[i] << (i + 1 < v.size() ? ", " : "");
    cout << "]\n";
}

int main() {
    ATM atm;
    atm.deposit({0, 0, 1, 2, 1});          // 1x100, 2x200, 1x500
    cout << "retirar 600 -> "; imprimir(atm.withdraw(600));  // [0,0,1,0,1]
    atm.deposit({0, 1, 0, 1, 1});          // 1x50, 1x200, 1x500
    cout << "retirar 600 -> "; imprimir(atm.withdraw(600));  // [-1] (500 + 100 no alcanza)
    cout << "retirar 550 -> "; imprimir(atm.withdraw(550));  // [0,1,0,0,1]
    return 0;
}
