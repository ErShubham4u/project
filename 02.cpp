#include <iostream> 
#include <vector> 
#include <ctime> 
#include <omp.h> 
 
using namespace std; 
 
// Parallel Odd-Even Transposition Sort (better than naive parallel Bubble Sort) 
void bubbleSortParallel(vector<int>& arr) { 
    int n = arr.size(); 
    for (int i = 0; i < n; i++) { 
        #pragma omp parallel for 
        for (int j = i % 2; j < n - 1; j += 2) { 
            if (arr[j] > arr[j + 1]) { 
                swap(arr[j], arr[j + 1]); 
            } 
        } 
    } 
} 
 
// Merge function 
void merge(vector<int>& arr, int l, int m, int r) { 
    vector<int> temp; 
    int i = l, j = m + 1; 
    while (i <= m && j <= r) { 
        if (arr[i] <= arr[j]) 
            temp.push_back(arr[i++]); 
        else 
            temp.push_back(arr[j++]); 
    } 
    while (i <= m) temp.push_back(arr[i++]); 
    while (j <= r) temp.push_back(arr[j++]); 
    for (int k = l; k <= r; k++) 
        arr[k] = temp[k - l]; 
} 
 
// Parallel Merge Sort 
void mergeSortParallel(vector<int>& arr, int l, int r) { 
    if (l < r) { 
        int m = (l + r) / 2; 
        #pragma omp parallel sections 
        { 
            #pragma omp section 
            mergeSortParallel(arr, l, m); 
            #pragma omp section 
            mergeSortParallel(arr, m + 1, r); 
        } 
        merge(arr, l, m, r); 
    } 
} 
 
int main() { 
    int n; 
    cout << "Enter the number of elements: "; 
    cin >> n; 
 
    vector<int> arr(n); 
    cout << "Enter the elements: "; 
    for (int i = 0; i < n; i++) 
        cin >> arr[i]; 
 
    // Bubble Sort 
    vector<int> arr1 = arr; 
    clock_t bubbleStart = clock(); 
    bubbleSortParallel(arr1); 
    clock_t bubbleEnd = clock(); 
 
    cout << "Sorted array using Bubble Sort (Parallel): "; 
    for (int num : arr1) 
        cout << num << " "; 
    cout << endl; 
 
    // Merge Sort 
    vector<int> arr2 = arr; 
    clock_t mergeStart = clock(); 
    mergeSortParallel(arr2, 0, n - 1); 
    clock_t mergeEnd = clock(); 
 
    cout << "Sorted array using Merge Sort (Parallel): "; 
    for (int num : arr2) 
        cout << num << " "; 
    cout << endl; 
 
    
    double bubbleDuration = double(bubbleEnd - bubbleStart) / CLOCKS_PER_SEC * 1000; 
    double mergeDuration = double(mergeEnd - mergeStart) / CLOCKS_PER_SEC * 1000; 
 
    cout << "Parallel Bubble sort time in milliseconds: " << bubbleDuration << " ms" << endl; 
    cout << "Parallel Merge sort time in milliseconds: " << mergeDuration << " ms" << endl; 
 
    return 0; 
}


// Enter the number of elements: 10
// Enter the elements: 9 7 3 8 2 5 4 1 6 0
// Sorted array using Bubble Sort (Parallel): 0 1 2 3 4 5 6 7 8 9 
// Sorted array using Merge Sort (Parallel): 0 1 2 3 4 5 6 7 8 9 
// Parallel Bubble sort time in milliseconds: 0 ms
// Parallel Merge sort time in milliseconds: 0 ms