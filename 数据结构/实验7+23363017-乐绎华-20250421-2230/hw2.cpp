#include <iostream>
#include <string>
using namespace std;

// BF(Brute Force) algorithm implementation
int BF(const string& mainStr, const string& pattern) {
    int mainLen = mainStr.length();
    int patternLen = pattern.length();
    
    if (patternLen > mainLen) return -1;  // Pattern is longer than main string, no match possible
    
    for (int i = 0; i <= mainLen - patternLen; i++) {
        int j;
        for (j = 0; j < patternLen; j++) {
            if (mainStr[i + j] != pattern[j])
                break;  // Character mismatch, exit inner loop
        }
        
        if (j == patternLen)
            return i;  // Match found, return starting position
    }
    
    return -1;  // No match found
}

int main() {
    // Test cases
    string mainStr1 = "ABABCABCACBAB";
    string pattern1 = "ABCAC";
    
    string mainStr2 = "This is a string matching algorithm test";
    string pattern2 = "matching algorithm";
    
    string mainStr3 = "hello world";
    string pattern3 = "world";
    
    string mainStr4 = "aaaaaaaaaaaaaaaaaaab";
    string pattern4 = "aaaab";
    
    // Test and output results
    cout << "Test 1: Find \"" << pattern1 << "\" in \"" << mainStr1 << "\"" << endl;
    int pos1 = BF(mainStr1, pattern1);
    if (pos1 != -1)
        cout << "Match found, starting position: " << pos1 << endl;
    else
        cout << "No match found" << endl;
    
    cout << "\nTest 2: Find \"" << pattern2 << "\" in \"" << mainStr2 << "\"" << endl;
    int pos2 = BF(mainStr2, pattern2);
    if (pos2 != -1)
        cout << "Match found, starting position: " << pos2 << endl;
    else
        cout << "No match found" << endl;
    
    cout << "\nTest 3: Find \"" << pattern3 << "\" in \"" << mainStr3 << "\"" << endl;
    int pos3 = BF(mainStr3, pattern3);
    if (pos3 != -1)
        cout << "Match found, starting position: " << pos3 << endl;
    else
        cout << "No match found" << endl;
    
    cout << "\nTest 4: Find \"" << pattern4 << "\" in \"" << mainStr4 << "\"" << endl;
    int pos4 = BF(mainStr4, pattern4);
    if (pos4 != -1)
        cout << "Match found, starting position: " << pos4 << endl;
    else
        cout << "No match found" << endl;
    
    // Custom test
    string customMain, customPattern;
    cout << "\nEnter main string: ";
    cin >> customMain;
    cout << "Enter pattern string: ";
    cin >> customPattern;
    
    int customPos = BF(customMain, customPattern);
    cout << "Finding \"" << customPattern << "\" in \"" << customMain << "\"" << endl;
    if (customPos != -1)
        cout << "Match found, starting position: " << customPos << endl;
    else
        cout << "No match found" << endl;
    
    return 0;
}

