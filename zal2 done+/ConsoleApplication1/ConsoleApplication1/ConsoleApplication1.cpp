#include <iostream>
#include <fstream>

using namespace std;

double horner_recursive(double x, double* coefficients, int n) {
    if (n == 0) {
        return coefficients[0];
    }
    else {
        return x * horner_recursive(x, coefficients, n - 1) + coefficients[n];
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    double x, result;
    int n;

    cout << "Введите степень многочлена: ";
    cin >> n;

    cout << "Введите значение x: ";
    cin >> x;

    double* coefficients = new double[n + 1];

    ifstream infile("coefficients.txt");

    for (int i = 0; i <= n; i++) {
        infile >> coefficients[i];
    }

    infile.close();

    result = horner_recursive(x, coefficients, n);

    cout << "Значение многочлена в точке " << x << " равно " << result << endl;

    delete[] coefficients;

    return 0;
}