#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

struct WordInfo {
    string word;
    string lines; // Список номеров строк, в которых встречается слово
};

int main() {
    const char* input_filename = "input.txt";
    const char* output_filename = "output.txt";

    ifstream infile(input_filename);
    if (!infile) {
        cerr << "Failed to open file for reading." << endl;
        exit(1);
    }

    WordInfo shortest_word, longest_word;
    shortest_word.word = longest_word.word = "";

    string line;
    int line_number = 0;
    while (getline(infile, line)) {
        line_number++;

        // Разбиваем строку на слова
        istringstream ss(line);
        string word;
        while (ss >> word) {
            // Если это первое слово, то сразу записываем его как самое длинное и самое короткое
            if (shortest_word.word == "" && longest_word.word == "") {
                shortest_word.word = longest_word.word = word;
                shortest_word.lines = longest_word.lines = to_string(line_number);
            }
            else {
                // Сравниваем длину слова с длиной самого короткого и самого длинного слов
                if (word.length() < shortest_word.word.length()) {
                    shortest_word.word = word;
                    shortest_word.lines = to_string(line_number);
                }
                else if (word.length() == shortest_word.word.length()) {
                    shortest_word.lines += ", " + to_string(line_number);
                }
                if (word.length() > longest_word.word.length()) {
                    longest_word.word = word;
                    longest_word.lines = to_string(line_number);
                }
                else if (word.length() == longest_word.word.length()) {
                    longest_word.lines += ", " + to_string(line_number);
                }
            }
        }
    }

    infile.close();

    // Открываем файл для записи
    ofstream outfile(output_filename);
    if (!outfile) {
        cerr << "Failed to open file for writing." << endl;
        exit(1);
    }

    // Записываем результаты в файл
    outfile << "Shortest word(s): \"" << shortest_word.word << "\" (in lines " << shortest_word.lines << ")" << endl;
    outfile << "Longest word: \"" << longest_word.word << "\" (in lines " << longest_word.lines << ")" << endl;

    outfile.close();

    return 0;
}