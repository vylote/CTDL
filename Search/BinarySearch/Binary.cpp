#include <iostream>
#include <algorithm>
using namespace std;

int binarySearch(int arr[], int size, int x) {
    int left = 0;
    int right = size-1;
    while (left <= right) {
        int mid = (left + right) / 2;

        if (arr[mid] == x) {
            return 1; // Tìm thấy
        } else if (arr[mid] > x) {
            right = mid - 1; 
        } else {
            left = mid + 1; 
        }
    }
    return 0;
}

int main() {
    int arr[] = {2, 45, -56, 4, 17, 34, 20};
    int size = sizeof(arr)/sizeof(arr[0]);
    sort(arr, arr+size);
    if (binarySearch(arr, size, 40)) {
        cout << "tim thay";
    } else {
        cout << "chiu chet";
    }
}