#include <iostream>

using namespace std;

int countElements(int**& arr, int rows, int cols) {
    int min = 1, max = 0, count = 0;

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] < min)
                min = arr[i][j];
            if (arr[i][j] > max)
                max = arr[i][j];
        }

    double res = (max / min);

    for (int i = 0; i < rows; i+=2)
        for (int j = 0; j < cols; j++)
        {
            if (arr[i][j] > res)
                count++;
        }

    return count;
}


int main()
{
    int n = 5;
    int** arr = new int* [n];

    for (int i = 0; i < n; i++)
        arr[i] = new int[n];

    int randNum;
    for (int i = 0; i < n; i++, cout << endl)
        for (int j = 0; j < n; j++)
        {
            arr[i][j] = rand() % 21 - 10;
            cout << arr[i][j] << "\t";
        }
    cout << endl;

    int result = countElements(arr, n, n);
    cout << "Result: " << result << endl;

    return 0;
}