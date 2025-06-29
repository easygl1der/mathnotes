#include <iostream>
#include <vector>
using namespace std;

// Triple structure to represent non-zero elements
struct Triple {
    int row, col, value;
};

// Sparse Matrix class
class SparseMatrix {
private:
    int rows, cols;
    vector<Triple> data;

public:
    // Constructor
    SparseMatrix(int r, int c) : rows(r), cols(c) {}

    // Add a non-zero element
    void addElement(int r, int c, int val) {
        if (val != 0) {
            data.push_back({r, c, val});
        }
    }

    // Read matrix from user input
    void readFromInput() {
        cout << "Enter the number of rows and columns: ";
        cin >> rows >> cols;
        
        cout << "Enter the matrix elements:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                int val;
                cin >> val;
                if (val != 0) {
                    addElement(i, j, val);
                }
            }
        }
    }

    // Print the sparse matrix (full form)
    void print() const {
        vector<vector<int>> fullMatrix(rows, vector<int>(cols, 0));
        
        // Fill in non-zero elements
        for (const auto& t : data) {
            fullMatrix[t.row][t.col] = t.value;
        }
        
        // Print the complete matrix
        cout << "Matrix (" << rows << "x" << cols << "):" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << fullMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    // Print compressed storage form
    void printCompressed() const {
        cout << "Compressed storage form (row,col,value):" << endl;
        for (const auto& t : data) {
            cout << "(" << t.row << "," << t.col << "," << t.value << ")" << endl;
        }
    }

    // Matrix addition
    SparseMatrix add(const SparseMatrix& other) const {
        if (rows != other.rows || cols != other.cols) {
            cerr << "Matrix dimensions don't match, cannot add!" << endl;
            return SparseMatrix(0, 0);
        }

        SparseMatrix result(rows, cols);
        
        // Create full representation of result matrix
        vector<vector<int>> resultMatrix(rows, vector<int>(cols, 0));
        
        // Add elements from first matrix
        for (const auto& t : data) {
            resultMatrix[t.row][t.col] += t.value;
        }
        
        // Add elements from second matrix
        for (const auto& t : other.data) {
            resultMatrix[t.row][t.col] += t.value;
        }
        
        // Add non-zero elements to result matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (resultMatrix[i][j] != 0) {
                    result.addElement(i, j, resultMatrix[i][j]);
                }
            }
        }
        
        return result;
    }
    
    // Matrix multiplication
    SparseMatrix multiply(const SparseMatrix& other) const {
        if (cols != other.rows) {
            cerr << "Matrix dimensions don't match, cannot multiply!" << endl;
            return SparseMatrix(0, 0);
        }
        
        SparseMatrix result(rows, other.cols);
        
        // Create full representation of result matrix
        vector<vector<int>> resultMatrix(rows, vector<int>(other.cols, 0));
        
        // Convert sparse matrices to full matrices for multiplication
        vector<vector<int>> mat1(rows, vector<int>(cols, 0));
        vector<vector<int>> mat2(other.rows, vector<int>(other.cols, 0));
        
        for (const auto& t : data) {
            mat1[t.row][t.col] = t.value;
        }
        
        for (const auto& t : other.data) {
            mat2[t.row][t.col] = t.value;
        }
        
        // Perform matrix multiplication
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < other.cols; j++) {
                for (int k = 0; k < cols; k++) {
                    resultMatrix[i][j] += mat1[i][k] * mat2[k][j];
                }
                if (resultMatrix[i][j] != 0) {
                    result.addElement(i, j, resultMatrix[i][j]);
                }
            }
        }
        
        return result;
    }
};

int main() {
    // Create two sparse matrices
    SparseMatrix matrix1(0, 0);
    SparseMatrix matrix2(0, 0);
    
    cout << "Input the first matrix:" << endl;
    matrix1.readFromInput();
    
    cout << "Input the second matrix:" << endl;
    matrix2.readFromInput();
    
    cout << "\nCompressed storage of first matrix:" << endl;
    matrix1.printCompressed();
    
    cout << "\nCompressed storage of second matrix:" << endl;
    matrix2.printCompressed();
    
    // Add matrices
    SparseMatrix addResult = matrix1.add(matrix2);
    
    cout << "\nAddition result:" << endl;
    addResult.print();
    
    cout << "\nCompressed storage of addition result matrix:" << endl;
    addResult.printCompressed();
    
    // Multiply matrices
    SparseMatrix multResult = matrix1.multiply(matrix2);
    
    cout << "\nMultiplication result:" << endl;
    multResult.print();
    
    cout << "\nCompressed storage of multiplication result matrix:" << endl;
    multResult.printCompressed();
    
    return 0;
}
