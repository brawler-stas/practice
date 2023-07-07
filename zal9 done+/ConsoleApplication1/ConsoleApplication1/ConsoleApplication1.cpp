#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Settlement {
    string name;
    int population;
    string date_founded;
    string type;
};

// Функция для записи данных в двоичный файл
void write_settlements_to_binary_file(const char* filename, const Settlement* settlements, int num_settlements) {
    ofstream outfile(filename, ios::binary);
    if (!outfile) {
        cerr << "Не удалось открыть файл для записи." << endl;
        exit(1);
    }
    for (int i = 0; i < num_settlements; i++) {
        const Settlement& s = settlements[i];
        int name_length = s.name.length();
        int date_length = s.date_founded.length();
        int type_length = s.type.length();
        outfile.write(reinterpret_cast<const char*>(&name_length), sizeof(name_length));
        outfile.write(s.name.c_str(), name_length);
        outfile.write(reinterpret_cast<const char*>(&s.population), sizeof(s.population));
        outfile.write(reinterpret_cast<const char*>(&date_length), sizeof(date_length));
        outfile.write(s.date_founded.c_str(), date_length);
        outfile.write(reinterpret_cast<const char*>(&type_length), sizeof(type_length));
        outfile.write(s.type.c_str(), type_length);
    }
    outfile.close();
}

// Функция для чтения данных из двоичного файла
Settlement* read_settlements_from_binary_file(const char* filename, int& num_settlements) {
    ifstream infile(filename, ios::binary);
    if (!infile) {
        cerr << "Не удалось открыть файл для чтения." << endl;
        exit(1);
    }
    infile.seekg(0, ios::end);
    int length = infile.tellg();
    num_settlements = length / (sizeof(int) + sizeof(int) + sizeof(int));
    Settlement* settlements = new Settlement[num_settlements];
    infile.seekg(0, ios::beg);
    for (int i = 0; i < num_settlements; i++) {
        int name_length, date_length, type_length;
        infile.read(reinterpret_cast<char*>(&name_length), sizeof(name_length));
        settlements[i].name.resize(name_length);
        infile.read(&settlements[i].name[0], name_length);
        infile.read(reinterpret_cast<char*>(&settlements[i].population), sizeof(settlements[i].population));
        infile.read(reinterpret_cast<char*>(&date_length), sizeof(date_length));
        settlements[i].date_founded.resize(date_length);
        infile.read(&settlements[i].date_founded[0], date_length);
        infile.read(reinterpret_cast<char*>(&type_length), sizeof(type_length));
        settlements[i].type.resize(type_length);
        infile.read(&settlements[i].type[0], type_length);
    }
    infile.close();
    return settlements;
}

// Функция для вычисления средней численности населения по городам
double average_population_of_cities(const Settlement* settlements, int num_settlements) {
    int total_population = 0;
    int num_cities = 0;
    for (int i = 0; i < num_settlements; i++) {
        if (settlements[i].type == "city") {
            total_population += settlements[i].population;
            num_cities++;
        }
    }
    if (num_cities == 0) {
        return 0.0;
    }
    else {
        return static_cast<double>(total_population) / num_cities;
    }
}

int main() {
    setlocale(LC_ALL, "RUS");
    const char* filename = "settlements.bin";

    // Создаем массив населенных пунктов
    Settlement settlements[] = {
        {"Москва", 1265500, "1147", "city"},
        {"Санкт-Петербург", 53980, "1703", "city"},
        {"Краснодар", 9287, "1793", "city"},
        {"Красноярск", 10951, "1628", "city"},
        {"Екатеринбург", 14937, "1723", "city"},
        {"Сочи", 4435, "1838", "city"},
        {"Красная Поляна", 4253, "1864", "village"},
        {"Липецк", 5088, "1703", "city"},
        {"Щучье", 13825, "1948", "town"},
        {"Севастополь", 3424, "1783", "city"}
    };
    int num_settlements = sizeof(settlements) / sizeof(settlements[0]);

    // Записываем данные в двоичный файл
    write_settlements_to_binary_file(filename, settlements, num_settlements);

    // Читаем данные из двоичного файла
    Settlement* settlements_from_file = read_settlements_from_binary_file(filename, num_settlements);

    // Вычисляем среднюю численность населения по городам
    double avg_population_of_cities = average_population_of_cities(settlements_from_file, num_settlements);

    // Выводим результат на экран
    cout << "Средняя численность населения по городам: " << avg_population_of_cities << endl;

    // Освобождаем выделенную память
    delete[] settlements_from_file;

    return 0;
}