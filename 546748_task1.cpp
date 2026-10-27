#include <iostream>
using namespace std;

const int MAX = 100;

int maxInColumn(int arr[][MAX], int rows, int col) {
    int best = 0;
    for (int i = 1; i < rows; i++)
        if (arr[i][col] > arr[best][col])
            best = i;
    return best;
}

void findPeak(int arr[][MAX], int rows, int cols) {
    int low = 0, high = cols - 1;

    while (low <= high) {
        int mid = (low + high) / 2;
        int r = maxInColumn(arr, rows, mid);

        bool leftOK  = (mid == 0)        || (arr[r][mid] >= arr[r][mid - 1]);
        bool rightOK = (mid == cols - 1) || (arr[r][mid] >= arr[r][mid + 1]);
        bool upOK    = (r == 0)          || (arr[r][mid] >= arr[r - 1][mid]);
        bool downOK  = (r == rows - 1)   || (arr[r][mid] >= arr[r + 1][mid]);

        if (leftOK && rightOK && upOK && downOK) {
            cout << "Peak at (" << r << ", " << mid << ") = "
                 << arr[r][mid] << endl;
            return;
        }

        if (mid > 0 && arr[r][mid - 1] > arr[r][mid])
            high = mid - 1;
        else if (mid < cols - 1 && arr[r][mid + 1] > arr[r][mid])
            low = mid + 1;
        else
            low = mid + 1;
    }
}

int main() {
    int arr[MAX][MAX] = {
        {10, 20, 15},
        {21, 30, 14},
        { 7, 16, 32}
    };
    findPeak(arr, 3, 3);
    return 0;
}