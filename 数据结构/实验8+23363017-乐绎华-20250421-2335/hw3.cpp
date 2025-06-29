#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Symmetric Matrix Compressed Storage Class
class SymmetricMatrix {
private:
    vector<double> data;  // One-dimensional array for compressed storage
    int n;  // Order of the matrix

public:
    // Constructor
    SymmetricMatrix(int size) : n(size) {
        // Symmetric matrix only needs to store upper or lower triangular part
        // Here we choose to store the upper triangular part, requiring n*(n+1)/2 elements
        data.resize(n * (n + 1) / 2, 0.0);
    }

    // Set matrix element
    void set(int i, int j, double value) {
        // Ensure indices are valid
        if (i < 0 || i >= n || j < 0 || j >= n) {
            cout << "Index out of bounds!" << endl;
            return;
        }
        
        // Due to symmetry, only store the upper triangular part
        if (i <= j) {
            // Calculate one-dimensional array index for upper triangular part
            int index = i * n - (i * (i + 1)) / 2 + j;
            data[index] = value;
        } else {
            // If it's lower triangular part, convert to corresponding upper triangular position
            int index = j * n - (j * (j + 1)) / 2 + i;
            data[index] = value;
        }
    }

    // Get matrix element
    double get(int i, int j) const {
        // Ensure indices are valid
        if (i < 0 || i >= n || j < 0 || j >= n) {
            cout << "Index out of bounds!" << endl;
            return 0.0;
        }
        
        // Due to symmetry, only need to access the upper triangular part
        if (i <= j) {
            int index = i * n - (i * (i + 1)) / 2 + j;
            return data[index];
        } else {
            int index = j * n - (j * (j + 1)) / 2 + i;
            return data[index];
        }
    }

    // Get matrix order
    int size() const {
        return n;
    }

    // Print matrix
    void print() const {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << get(i, j) << " ";
            }
            cout << endl;
        }
    }
};

// Multiply symmetric matrices
SymmetricMatrix multiply(const SymmetricMatrix& A, const SymmetricMatrix& B) {
    int n = A.size();
    
    // Ensure matrices can be multiplied
    if (n != B.size()) {
        cout << "Matrix dimensions don't match, cannot multiply!" << endl;
        return SymmetricMatrix(0);
    }
    
    SymmetricMatrix C(n);
    
    // Calculate matrix product
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {  // Only calculate upper triangular part
            double sum = 0.0;
            for (int k = 0; k < n; k++) {
                sum += A.get(i, k) * B.get(k, j);
            }
            C.set(i, j, sum);
        }
    }
    
    return C;
}

int main() {
    int n;
    cout << "Please enter the order of the symmetric matrix: ";
    cin >> n;
    
    SymmetricMatrix A(n), B(n);
    
    cout << "Please enter the upper triangular elements of the first symmetric matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double value;
            cin >> value;
            A.set(i, j, value);
        }
    }
    
    cout << "Please enter the upper triangular elements of the second symmetric matrix:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = i; j < n; j++) {
            double value;
            cin >> value;
            B.set(i, j, value);
        }
    }
    
    cout << "First symmetric matrix:" << endl;
    A.print();
    
    cout << "Second symmetric matrix:" << endl;
    B.print();
    
    SymmetricMatrix C = multiply(A, B);
    
    cout << "Result of matrix multiplication:" << endl;
    C.print();
    
    return 0;
}
