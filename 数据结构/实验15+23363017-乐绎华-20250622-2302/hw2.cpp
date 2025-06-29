#include <iostream>
#include <vector>
#include <algorithm> // For std::sort to verify
#include <ctime>

// Partition function using 1-based indexing (low and high are inclusive)
int partition(int r[], int low, int high) {
    int pivot = r[low];
    while (low < high) {
        while (low < high && r[high] >= pivot) high--;
        if (low < high) r[low++] = r[high];
        while (low < high && r[low] <= pivot) low++;
        if (low < high) r[high--] = r[low];
    }
    r[low] = pivot;
    return low;
}

// Search for k-th smallest element using 1-based indexing
// Finds the k-th smallest element in array r (from index 1 to n)
int findKthSmallest(int r[], int n, int k) {
    if (k < 1 || k > n) {
        std::cerr << "Error: k is out of bounds." << std::endl;
        return -1;
    }

    int low = 1;
    int high = n;
    int pivot_idx = partition(r, low, high);

    while (pivot_idx != k) {
        if (pivot_idx < k) {
            low = pivot_idx + 1;
        } else {
            high = pivot_idx - 1;
        }
        pivot_idx = partition(r, low, high);
    }
    return r[k];
}

void printVector(const std::vector<int>& arr) {
    std::cout << "[";
    for (size_t i = 0; i < arr.size(); ++i) {
        std::cout << arr[i] << (i == arr.size() - 1 ? "" : ", ");
    }
    std::cout << "]" << std::endl;
}

// --- Main Function ---
int main() {
    std::cout << "--- Find K-th Smallest Element (Quickselect, 1-based index) ---" << std::endl;

    std::vector<int> data = {45, 23, 78, 12, 67, 34, 89, 56};
    int k = 4; // Find the 4th smallest element
    int n = data.size();

    std::cout << "Original data: ";
    printVector(data);
    std::cout << "Finding the " << k << "-th smallest element..." << std::endl;

    // Create a 1-indexed array for the algorithm
    int* work_array = new int[n + 1];
    for(int i = 0; i < n; ++i) {
        work_array[i + 1] = data[i];
    }

    int result = findKthSmallest(work_array, n, k);

    std::cout << "\nResult: The " << k << "-th smallest element is " << result << std::endl;

    // Verification
    std::sort(data.begin(), data.end());
    std::cout << "Verification (sorted data): ";
    printVector(data);
    std::cout << "The " << k << "-th smallest element should be " << data[k-1] << std::endl;

    if (result == data[k-1]) {
        std::cout << "Result is correct." << std::endl;
    } else {
        std::cout << "Result is incorrect." << std::endl;
    }

    delete[] work_array;
    return 0;
}

