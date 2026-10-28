// Ejercicio 3: Sistema subterráneo (metro)
#include <iostream>
#include <string>
#include <unordered_map>
#include <map>
#include <utility>
using namespace std;

class UndergroundSystem {
private:
    // id -> (estación de entrada, tiempo de entrada) de quienes están viajando
    unordered_map<int, pair<string, int>> enViaje;
    // (inicio, fin) -> (suma de tiempos, cantidad de viajes)
    map<pair<string, string>, pair<long long, int>> historial;

public:
    UndergroundSystem() {}

    void checkIn(int id, string stationName, int t) {
        enViaje[id] = {stationName, t};
    }

    void checkOut(int id, string stationName, int t) {
        auto entrada = enViaje[id];
        enViaje.erase(id);                       // el cliente ya no está viajando
        auto& dato = historial[{entrada.first, stationName}];
        dato.first += t - entrada.second;        // acumula duración
        dato.second += 1;                        // cuenta el viaje
    }

    double getAverageTime(string startStation, string endStation) {
        auto& dato = historial[{startStation, endStation}];
        return (double)dato.first / dato.second;
    }
};

int main() {
    UndergroundSystem u;
    u.checkIn(45, "Leyton", 3);
    u.checkIn(32, "Paradise", 8);
    u.checkIn(27, "Leyton", 10);
    u.checkOut(45, "Waterloo", 15);   // 12
    u.checkOut(27, "Waterloo", 20);   // 10
    u.checkOut(32, "Cambridge", 22);  // 14
    cout << "Paradise->Cambridge: " << u.getAverageTime("Paradise", "Cambridge") << "  (esperado 14)\n";
    cout << "Leyton->Waterloo:    " << u.getAverageTime("Leyton", "Waterloo") << "  (esperado 11)\n";
    u.checkIn(10, "Leyton", 24);
    u.checkOut(10, "Waterloo", 38);   // 14
    cout << "Leyton->Waterloo:    " << u.getAverageTime("Leyton", "Waterloo") << "  (esperado 12)\n";
    return 0;
}
