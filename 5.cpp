#include <iostream>
#include <vector>
#include <algorithm> // Для функції lower_bound

using namespace std;

// Функція для вставки числа у відсортований масив
void insertInArr(vector<int>& arr, int num, int count) {
    for (int i = 0; i < count; i++) { // Повторюємо вставку задану кількість разів
        auto it = lower_bound(arr.begin(), arr.end(), num); // Знаходимо місце для вставки, щоб зберегти сортування
        arr.insert(it, num); // Вставляємо число у вказане місце
    }
}

int main()
{
    // Ініціалізуємо початковий вектор
    vector<int> arr = { 1, 2, 4, 8, 9, 10 };
    int num, count;

    // Введення числа для вставки
    cout << "Enter number to enter: ";
    cin >> num;

    // Введення кількості вставок
    cout << "Enter count of insert: ";
    cin >> count;

    // Викликаємо функцію для вставки числа
    insertInArr(arr, num, count);

    // Вивід оновленого масиву
    for (int item : arr) {
        cout << item << " ";
    }

    cout << endl;
}

// g++ -std=c++11 "5.cpp" -o program