#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double h = 0.05; // шаг
    double eps = 1e-3; // точность
    double x = 0; // начальное значение x

    while (x <= 1) {
        // вычисление значения выражения x / (1 + x * x)
        double expr = x / (1 + x * x);

        // инициализация переменных для вычисления значения функции
        int n = 0;
        double sum = 0;
        double term = 1;

        // вычисление суммы ряда
        while (abs(term) > eps) {
            double denominator = pow(1 + x * x, n);
            double numerator = pow(x, 2 * n);
            double numerator_fact = 1;
            double denominator_fact = 1;

            // вычисление двойного факториала числителя
            if (n > 0) {
                for (int i = 1; i <= n; i++) {
                    numerator_fact *= 2 * i;
                }
            }

            // вычисление двойного факториала знаменателя
            if (n > 0) {
                for (int i = 1; i <= n; i++) {
                    denominator_fact *= 2 * i + 1;
                }
            }

            term = numerator_fact * numerator / (denominator_fact * denominator);
            sum += term;
            n++;
        }

        double y = expr * sum;

        // вывод значений x и y
        cout << "x = " << x << ", y = " << y << endl;

        // увеличение значения x на шаг h
        x += h;
    }

    return 0;
}