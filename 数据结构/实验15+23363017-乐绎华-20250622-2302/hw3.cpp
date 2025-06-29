#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cstring> // For memcpy

using namespace std;

// Structure to hold sorting statistics
struct SortStats {
    string name;
    long long comparisons = 0;
    long long movements = 0;
};

// --- Prototypes for Sorting Algorithms ---
void selectSort(int r[], int n, long long& comparisons, long long& movements);
void insertSort(int r[], int n, long long& comparisons, long long& movements);
void bubbleSort(int r[], int n, long long& comparisons, long long& movements);
void heapSort(int arr[], int n, long long& comparisons, long long& movements);
void quickSort(int r[], int n, long long& comparisons, long long& movements);
void quickSortRecursive(int r[], int low, int high, long long& comparisons, long long& movements);

// --- Main Program ---
int main() {
    srand(time(nullptr));

    const int N = 20000;
    int* original_data = new int[N];
    int* temp_data = new int[N];

    cout << "Generating " << N << " random integers for sorting comparison..." << endl;
    for (int i = 0; i < N; ++i) {
        original_data[i] = rand() % 100000;
    }

    vector<pair<string, void (*)(int[], int, long long&, long long&)>> sorts = {
        {"Bubble Sort", bubbleSort},
        {"Insert Sort", insertSort},
        {"Select Sort", selectSort},
        {"Heap Sort", heapSort},
        {"Quick Sort", quickSort}
    };
    
    vector<SortStats> all_stats;

    for (const auto& sort_pair : sorts) {
        memcpy(temp_data, original_data, N * sizeof(int));
        
        SortStats current_stats;
        current_stats.name = sort_pair.first;
        
        cout << "Running " << current_stats.name << "..." << endl;
        sort_pair.second(temp_data, N, current_stats.comparisons, current_stats.movements);
        all_stats.push_back(current_stats);
    }

    cout << "\n--- Sorting Algorithm Comparison (N = " << N << ") ---" << endl;
    cout << setfill('-') << setw(55) << "" << setfill(' ') << endl;
    cout << left << setw(18) << "Algorithm"
         << right << setw(18) << "Comparisons"
         << right << setw(18) << "Movements" << endl;
    cout << setfill('-') << setw(55) << "" << setfill(' ') << endl;

    for (const auto& stats : all_stats) {
        cout << left << setw(18) << stats.name
             << right << setw(18) << stats.comparisons
             << right << setw(18) << stats.movements << endl;
    }
    cout << setfill('-') << setw(55) << "" << setfill(' ') << endl;

    delete[] original_data;
    delete[] temp_data;

    return 0;
}

// --- Implementations of Sorting Algorithms ---

void insertSort(int r[], int n, long long& comparisons, long long& movements) {
    for (int i = 1; i < n; i++) {
        int key = r[i];
        movements++; 
        int j = i - 1;
        while (j >= 0 && (comparisons++, r[j] > key)) {
            r[j + 1] = r[j];
            movements++;
            j--;
        }
        r[j + 1] = key;
        movements++;
    }
}

void selectSort(int r[], int n, long long& comparisons, long long& movements) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++) {
            comparisons++;
            if (r[j] < r[min_idx]) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swap(r[i], r[min_idx]);
            movements += 3;
        }
    }
}

void bubbleSort(int r[], int n, long long& comparisons, long long& movements) {
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            comparisons++;
            if (r[j] > r[j + 1]) {
                swap(r[j], r[j + 1]);
                movements += 3;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

int partition(int r[], int low, int high, long long& comparisons, long long& movements) {
    int pivot_val = r[low];
    movements++;
    while (low < high) {
        while (low < high && (comparisons++, r[high] >= pivot_val)) high--;
        if(low < high) { r[low++] = r[high]; movements++; }
        while (low < high && (comparisons++, r[low] < pivot_val)) low++;
        if(low < high) { r[high--] = r[low]; movements++; }
    }
    r[low] = pivot_val;
    movements++;
    return low;
}

void quickSortRecursive(int r[], int low, int high, long long& comparisons, long long& movements) {
    if (low < high) {
        int pivot_pos = partition(r, low, high, comparisons, movements);
        quickSortRecursive(r, low, pivot_pos - 1, comparisons, movements);
        quickSortRecursive(r, pivot_pos + 1, high, comparisons, movements);
    }
}

void quickSort(int r[], int n, long long& comparisons, long long& movements) {
    quickSortRecursive(r, 0, n - 1, comparisons, movements);
}

void heapify(int arr[], int n, int i, long long& comparisons, long long& movements) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && (comparisons++, arr[left] > arr[largest])) {
        largest = left;
    }
    if (right < n && (comparisons++, arr[right] > arr[largest])) {
        largest = right;
    }
    if (largest != i) {
        swap(arr[i], arr[largest]);
        movements += 3;
        heapify(arr, n, largest, comparisons, movements);
    }
}

void heapSort(int arr[], int n, long long& comparisons, long long& movements) {
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, comparisons, movements);
    }
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        movements += 3;
        heapify(arr, i, 0, comparisons, movements);
    }
}
