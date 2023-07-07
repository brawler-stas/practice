#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;

int main()
{
    setlocale(LC_ALL, "RUS");
    int target;

    cout << "Введите искомое значение: ";
    cin >> target;

    // Генерация массива из миллиона случайных чисел
    const int size = 1000000;
    int* arr = new int[size];

    for (int i = 0; i < size; i++) {
        arr[i] = rand() % 1000000;
    }

    // Сортировка массива
    sort(arr, arr + size);

    // Выполнение двоичного поиска
    int count = 0;
    int left = 0;
    int right = size - 1;

    while (left <= right) {
        int mid = (left + right) / 2;
        count++;

        if (arr[mid] == target) {
            cout << "Значение " << target << " найдено в позиции " << mid << endl;
            break;
        }
        else if (arr[mid] < target) {
            left = mid + 1;
        }
        else {
            right = mid - 1;
        }
    }

    if (left > right) {
        cout << "Значение " << target << " не найдено\n";
    }

    // Запись количества итераций в файл
    ofstream fout("binary_search_iterations.txt");
    if (!fout) {
        cerr << "Не удалось открыть файл для записи количества итераций!\n";
        return 1;
    }

    fout << "Количество итерраций: " << count << endl;
    fout.close();

    delete[] arr; // Освобождение памяти, занятой массивом
    return 0;
}