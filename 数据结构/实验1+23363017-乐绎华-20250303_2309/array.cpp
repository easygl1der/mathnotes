#include <iostream>
using namespace std;

class Array {
private:
    int* data;
    size_t size;
public:
    Array(size_t size) : size(size) {
        data = new int[size];
    }
    ~Array() {
        delete[] data;
    }
    size_t getSize() const {
        return size;
    }
    int& operator[](size_t index) {
        return data[index];
    }
    void display() const {
        for (size_t i = 0; i < size; ++i) {
            cout << data[i] << " ";
        }
        cout << endl;
    }
};

int main() {
    Array arr(5);
    for (size_t i = 0; i < arr.getSize(); ++i) {
        arr[i] = i;
    }

    cout << "数组元素: ";
    arr.display();

    return 0;
}
