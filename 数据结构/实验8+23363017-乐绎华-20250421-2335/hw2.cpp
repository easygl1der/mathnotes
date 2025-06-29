#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Caesar encryption function
string caesarEncrypt(const string& plaintext, int key) {
    string ciphertext = plaintext;
    for (char& c : ciphertext) {
        if (isalpha(c)) {
            char base = islower(c) ? 'a' : 'A';
            c = base + (c - base + key) % 26;
        }
    }
    return ciphertext;
}

// Caesar decryption function
string caesarDecrypt(const string& ciphertext, int key) {
    // Decryption is moving in the opposite direction, equivalent to encrypting with 26-key
    return caesarEncrypt(ciphertext, 26 - key);
}

int main() {
    const int key = 3; // Set key to 3 (can be modified as needed)
    
    // Encryption process
    ifstream inFile("sysu.txt");
    ofstream outFile("sysu_en.txt");
    
    if (!inFile.is_open()) {
        cerr << "Unable to open input file sysu.txt" << endl;
        return 1;
    }
    
    if (!outFile.is_open()) {
        cerr << "Unable to open output file sysu_en.txt" << endl;
        inFile.close();
        return 1;
    }
    
    string line;
    while (getline(inFile, line)) {
        outFile << caesarEncrypt(line, key) << endl;
    }
    
    inFile.close();
    outFile.close();
    
    // Decryption process
    ifstream encodeFile("sysu_encode.txt");
    ofstream decodeFile("sysu_decode.txt");
    
    if (!encodeFile.is_open()) {
        cerr << "Unable to open input file sysu_encode.txt" << endl;
        return 1;
    }
    
    if (!decodeFile.is_open()) {
        cerr << "Unable to open output file sysu_decode.txt" << endl;
        encodeFile.close();
        return 1;
    }
    
    while (getline(encodeFile, line)) {
        decodeFile << caesarDecrypt(line, key) << endl;
    }
    
    encodeFile.close();
    decodeFile.close();
    
    cout << "Encryption and decryption completed!" << endl;
    return 0;
}
