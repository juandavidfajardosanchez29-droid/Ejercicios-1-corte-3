// Ejercicio 5: Fecha de una reunión (meetup)
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#include <map>
using namespace std;

bool esBisiesto(int y) { return (y % 4 == 0 && y % 100 != 0) || (y % 400 == 0); }

int diasDelMes(int y, int m) {
    static const int d[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    return (m == 2 && esBisiesto(y)) ? 29 : d[m - 1];
}

// Algoritmo de Sakamoto: 0 = domingo, 1 = lunes, ..., 6 = sábado
int diaSemana(int y, int m, int d) {
    static const int t[] = {0, 3, 2, 5, 0, 3, 5, 1, 4, 6, 2, 4};
    if (m < 3) y -= 1;
    return (y + y / 4 - y / 100 + y / 400 + t[m - 1] + d) % 7;
}

string meetup(int year, int month, const string& weekday, const string& week) {
    static const map<string, int> dias = {
        {"Sunday", 0}, {"Monday", 1}, {"Tuesday", 2}, {"Wednesday", 3},
        {"Thursday", 4}, {"Friday", 5}, {"Saturday", 6}};
    int objetivo = dias.at(weekday);
    int dia;

    if (week == "last") {
        // Se parte del último día del mes y se retrocede hasta el día buscado
        dia = diasDelMes(year, month);
        while (diaSemana(year, month, dia) != objetivo) dia--;
    } else {
        // Primer día posible de cada semana; se avanza hasta el día buscado
        static const map<string, int> inicio = {
            {"first", 1}, {"second", 8}, {"third", 15}, {"fourth", 22}, {"teenth", 13}};
        dia = inicio.at(week);
        while (diaSemana(year, month, dia) != objetivo) dia++;
    }

    ostringstream s;
    s << setfill('0') << setw(4) << year << "-" << setw(2) << month << "-" << setw(2) << dia;
    return s.str();
}

int main() {
    cout << meetup(2018, 1, "Monday", "first")      << "  (esperado 2018-01-01)\n";
    cout << meetup(2019, 8, "Tuesday", "third")     << "  (esperado 2019-08-20)\n";
    cout << meetup(2020, 5, "Wednesday", "teenth")  << "  (esperado 2020-05-13)\n";
    cout << meetup(2021, 7, "Sunday", "fourth")     << "  (esperado 2021-07-25)\n";
    cout << meetup(2022, 11, "Thursday", "last")    << "  (esperado 2022-11-24)\n";
    cout << meetup(1953, 8, "Saturday", "teenth")   << "  (esperado 1953-08-15)\n";
    return 0;
}
