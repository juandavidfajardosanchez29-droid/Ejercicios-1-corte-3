
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
using namespace std;

class Clock {
private:
    int minutos;  
    static const int MIN_POR_DIA = 24 * 60;

    static int normalizar(int total) {
        
        return ((total % MIN_POR_DIA) + MIN_POR_DIA) % MIN_POR_DIA;
    }

public:
    Clock(int hora, int minuto = 0) : minutos(normalizar(hora * 60 + minuto)) {}

    Clock plus(int m) const  { return Clock(0, minutos + m); }
    Clock minus(int m) const { return Clock(0, minutos - m); }

    bool operator==(const Clock& otro) const { return minutos == otro.minutos; }
    bool operator!=(const Clock& otro) const { return !(*this == otro); }

    string toString() const {
        ostringstream s;
        s << setfill('0') << setw(2) << minutos / 60 << ":" << setw(2) << minutos % 60;
        return s.str();
    }
};

int main() {
    cout << Clock(8, 0).toString()        << "  (esperado 08:00)\n";
    cout << Clock(25, 0).toString()       << "  (esperado 01:00)\n";
    cout << Clock(-1, 15).toString()      << "  (esperado 23:15)\n";
    cout << Clock(10, 3).plus(61).toString()  << "  (esperado 11:04)\n";
    cout << Clock(0, 30).minus(60).toString() << "  (esperado 23:30)\n";
    cout << Clock(0, 0).minus(3000).toString() << "  (esperado 22:00)\n";
    cout << boolalpha << (Clock(15, 37) == Clock(39, 37)) << "  (esperado true)\n";
    cout << boolalpha << (Clock(15, 37) == Clock(15, 38)) << "  (esperado false)\n";
    return 0;
}
