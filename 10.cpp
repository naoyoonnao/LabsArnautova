#include <iostream>
#include <vector>
using namespace std;

int main() {
    int n;
    cout << "Enter mas size (n x n): ";
    cin >> n;

    vector<vector<int>> matrix(n, vector<int>(n));
    cout << "Enter mas elements:" << endl;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << "matrix[" << i << "][" << j << "] = ";
            cin >> matrix[i][j];
        }
    }

    for (int i = 0; i < n; ++i) {
        int positiveCount = 0;
        int maxElement = matrix[i][0];

        for (int j = 0; j < n; ++j) {
            if (matrix[i][j] > 0) ++positiveCount;
            if (matrix[i][j] > maxElement) maxElement = matrix[i][j];
        }

        if (positiveCount > 0) {
            matrix[i][i] = positiveCount;
        }
        else {
            matrix[i][i] = maxElement;
        }
    }

    cout << "Output mas:" << endl;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }

    return 0;
}
