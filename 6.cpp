#include <iostream>
#include <fstream> // Для роботи з файлами
#include <vector>

using namespace std;

const int n = 8; // Розмір матриці

// Функція для знаходження рядків і стовпців, де елементи співпадають
void findMatchingRowsColumns(int matrix[n][n], int matchingIndices[n], int& matchCount) {
    matchCount = 0; // Лічильник співпадінь
    for (int k = 0; k < n; ++k) { // Перебір кожного рядка та стовпця
        bool match = true;
        for (int i = 0; i < n; ++i) {
            if (matrix[k][i] != matrix[i][k]) { // Перевірка, чи рядок і стовпець однакові
                match = false;
                break;
            }
        }
        if (match) {
            matchingIndices[matchCount++] = k; // Збереження індексу рядка/стовпця
        }
    }
}

// Функція для обчислення суми елементів у рядках з негативними числами
int sumRowsWithNegative(int matrix[n][n]) {
    int sum = 0;
    for (int i = 0; i < n; ++i) {
        bool hasNegative = false; // Прапорець для перевірки наявності негативного числа
        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] < 0) { // Якщо знайдено негативне число
                hasNegative = true;
                break;
            }
        }
        if (hasNegative) { // Якщо в рядку є негативні числа
            for (int j = 0; j < n; ++j) {
                sum += matrix[i][j]; // Додаємо всі елементи рядка до суми
            }
        }
    }
    return sum;
}

int main() {
    ifstream inputFile("matrix.txt"); // Вхідний файл
    ofstream outputFile("output.txt"); // Вихідний файл

    if (!inputFile.is_open() || !outputFile.is_open()) { // Перевірка відкриття файлів
        cerr << "Error with file openning!" << endl;
        return 1;
    }

    int matrix[n][n]; // Матриця 8x8
    int matchingIndices[n]; // Масив для збереження індексів співпадаючих рядків/стовпців
    int matchCount = 0; // Лічильник кількості співпадаючих рядків/стовпців

    // Зчитування матриці з файлу
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inputFile >> matrix[i][j];
        }
    }

    // Вивід матриці на екран
    cout << "Matrix:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << " ";
        }
        cout << endl;
    }

    // Знаходження співпадаючих рядків і стовпців
    findMatchingRowsColumns(matrix, matchingIndices, matchCount);

    // Вивід співпадаючих рядків і стовпців
    cout << "\nMatching rows and columns: ";
    outputFile << "Matching rows and columns: ";
    for (int i = 0; i < matchCount; ++i) {
        cout << matchingIndices[i] << " ";
        outputFile << matchingIndices[i] << " ";
    }
    cout << endl;

    // Обчислення суми елементів у рядках із негативними числами
    int sum = sumRowsWithNegative(matrix);
    cout << "Sum of elements in rows with negative elements: " << sum << endl;
    outputFile << "\nSum of elements in rows with negative elements: " << sum << endl;

    // Закриття файлів
    inputFile.close();
    outputFile.close();

    return 0;
}
