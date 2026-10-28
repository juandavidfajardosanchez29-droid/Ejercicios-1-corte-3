// Ejercicio 1: Sistema de subasta
#include <iostream>
#include <map>
#include <set>
#include <unordered_map>
#include <utility>
using namespace std;

class AuctionSystem {
private:
    // monto[item][usuario] = oferta actual del usuario en ese artículo
    unordered_map<int, unordered_map<int, int>> monto;
    // ranking[item] = conjunto ordenado de pares (monto, usuario).
    // El último elemento es el mayor monto y, en empate, el mayor userId.
    unordered_map<int, set<pair<int, int>>> ranking;

public:
    AuctionSystem() {}

    void addBid(int userId, int itemId, int bidAmount) {
        // Si ya tenía oferta, se reemplaza: primero se quita la anterior
        auto it = monto[itemId].find(userId);
        if (it != monto[itemId].end()) {
            ranking[itemId].erase({it->second, userId});
        }
        monto[itemId][userId] = bidAmount;
        ranking[itemId].insert({bidAmount, userId});
    }

    void updateBid(int userId, int itemId, int newAmount) {
        // Se garantiza que existe, por eso es lo mismo que reemplazar
        addBid(userId, itemId, newAmount);
    }

    void removeBid(int userId, int itemId) {
        int actual = monto[itemId][userId];
        ranking[itemId].erase({actual, userId});
        monto[itemId].erase(userId);
    }

    int getHighestBidder(int itemId) {
        auto it = ranking.find(itemId);
        if (it == ranking.end() || it->second.empty()) return -1;
        return it->second.rbegin()->second;   // mayor monto; empate -> mayor userId
    }
};

int main() {
    AuctionSystem a;
    a.addBid(1, 100, 50);
    a.addBid(2, 100, 70);
    cout << "Mayor postor item 100: " << a.getHighestBidder(100) << "  (esperado 2)\n";
    a.addBid(3, 100, 70);   // empate en 70 -> gana el userId mayor
    cout << "Empate en 70:          " << a.getHighestBidder(100) << "  (esperado 3)\n";
    a.updateBid(1, 100, 90);
    cout << "Usuario 1 sube a 90:   " << a.getHighestBidder(100) << "  (esperado 1)\n";
    a.removeBid(1, 100);
    cout << "Se retira el 1:        " << a.getHighestBidder(100) << "  (esperado 3)\n";
    cout << "Item sin ofertas:      " << a.getHighestBidder(999) << "  (esperado -1)\n";
    return 0;
}
