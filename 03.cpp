#include <iostream> 
#include <vector> 
#include <omp.h> 
#include <climits> 
#include <chrono> 
 
using namespace std; 
using namespace std::chrono; 
 
void min_reduction(const vector<int>& arr) { 
    auto start = high_resolution_clock::now(); 
 
    int min_value = INT_MAX; 
    #pragma omp parallel for reduction(min: min_value) 
    for (int i = 0; i < arr.size(); i++) { 
        min_value = min(min_value, arr[i]); 
    } 
 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start); 
 
    cout << "Minimum value: " << min_value  
         << " (Time taken: " << duration.count() << " nanoseconds)" << endl; 
} 
 
void max_reduction(const vector<int>& arr) { 
    auto start = high_resolution_clock::now(); 
 
    int max_value = INT_MIN; 
    #pragma omp parallel for reduction(max: max_value) 
    for (int i = 0; i < arr.size(); i++) { 
        max_value = max(max_value, arr[i]); 
    } 
 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start); 
 
    cout << "Maximum value: " << max_value  
         << " (Time taken: " << duration.count() << " nanoseconds)" << endl; 
} 
 
void sum_reduction(const vector<int>& arr) { 
    auto start = high_resolution_clock::now(); 
 
    int sum = 0; 
    #pragma omp parallel for reduction(+: sum) 
    for (int i = 0; i < arr.size(); i++) { 
        sum += arr[i]; 
    } 
 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start); 
 
    cout << "Sum: " << sum  
         << " (Time taken: " << duration.count() << " nanoseconds)" << endl; 
} 
 
void average_reduction(const vector<int>& arr) { 
    auto start = high_resolution_clock::now(); 
 
    int sum = 0; 
    #pragma omp parallel for reduction(+: sum) 
    for (int i = 0; i < arr.size(); i++) { 
        sum += arr[i]; 
    } 
 
    auto stop = high_resolution_clock::now(); 
    auto duration = duration_cast<nanoseconds>(stop - start); 
 
    double average = static_cast<double>(sum) / arr.size(); 
    cout << "Average: " << average  
         << " (Time taken: " << duration.count() << " nanoseconds)" << endl; 
} 
 
int main() { 
    int n; 
    cout << "Enter the number of elements: "; 
    cin >> n; 
 
    if (n <= 0) { 
        cout << "Invalid input. The number of elements must be greater than zero." << endl; 
        return 1; 
    } 
 
    vector<int> arr(n); 
    cout << "Enter " << n << " elements: "; 
    for (int i = 0; i < n; i++) { 
        cin >> arr[i]; 
    } 
 
    min_reduction(arr); 
    max_reduction(arr); 
    sum_reduction(arr); 
    average_reduction(arr); 
 
    return 0; 
} 

// Enter the number of elements: 8
// Enter 8 elements: 45 12 67 23 89 4 31 10
// Minimum value: 4 (Time taken: 11154000 nanoseconds)
// Maximum value: 89 (Time taken: 0 nanoseconds)
// Sum: 281 (Time taken: 0 nanoseconds)
// Average: 35.125 (Time taken: 0 nanoseconds)