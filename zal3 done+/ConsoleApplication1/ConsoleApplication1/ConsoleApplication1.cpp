#include <iostream>
#include <cmath>

using namespace std;

double A(double a, double h, double m, double z) {
    return exp(a * z) * pow(1 + (h - 1) * z, a) / pow(1 + h * z, a + 1);
}

int main() {
    double a, h, z, x;

    cout << "Enter a: ";
    cin >> a;

    cout << "Enter h: ";
    cin >> h;

    cout << "Enter z: ";
    cin >> z;

    cout << "The polynomial is: ";
    for (int m = 1; m <= 10; m++) {
        cout << A(a, h, m, z) << "x^" << m;
        if (m < 10) {
            cout << " + ";
        }
    }
    /*
    cout << endl;

    cout << "Enter x: ";
    cin >> x;

    double result = 0.0;
    for (int m = 1; m <= 10; m++) {
        result += A(a, h, m, z) * pow(x, m);
    }

    cout << "The value of the polynomial for x = " << x << " is: " << result << endl;
    */
    return 0;
}