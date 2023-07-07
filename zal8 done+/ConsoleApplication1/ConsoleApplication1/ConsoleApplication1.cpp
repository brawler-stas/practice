#include <iostream>
#include <fstream>

using namespace std;

int main() {
    ifstream coeffFile("coefficients.txt");
    ifstream matrixFile("matrix.txt");

    const int MAX_SIZE = 100;
    double matrix[MAX_SIZE][MAX_SIZE];
    double b[MAX_SIZE];

    // Считываем коэффициенты из файла
    int n = 0;
    double value;
    while (coeffFile >> value) {
        b[n] = value;
        n++;
    }

    // Считываем матрицу из файла
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrixFile >> matrix[i][j];
        }
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; i++) {
        int maxRow = i;
        for (int j = i + 1; j < n; j++) {
            if (abs(matrix[j][i]) > abs(matrix[maxRow][i])) {
                maxRow = j;
            }
        }
        for (int j = i; j < n; j++) {
            swap(matrix[i][j], matrix[maxRow][j]);
        }
        swap(b[i], b[maxRow]);

        double pivot = matrix[i][i];
        for (int j = i; j < n; j++) {
            matrix[i][j] /= pivot;
        }
        b[i] /= pivot;

        for (int j = i + 1; j < n; j++) {
            double factor = matrix[j][i];
            for (int k = i; k < n; k++) {
                matrix[j][k] -= factor * matrix[i][k];
            }
            b[j] -= factor * b[i];
        }
    }

    // Обратный ход метода Гаусса
    double x[MAX_SIZE];
    for (int i = n - 1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i + 1; j < n; j++) {
            x[i] -= matrix[i][j] * x[j];
        }
    }

    // Записываем решение в файл
    ofstream outputFile("solution.txt");
    for (int i = 0; i < n; i++) {
        outputFile << "x" << i + 1 << " = " << x[i] << endl;
    }
    outputFile.close();

    return 0;
}