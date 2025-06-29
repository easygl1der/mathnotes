#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Calculate the next array for the pattern string
void getNext(const string& pattern, vector<int>& next) {
    int j = 0;
    int k = -1;
    next[0] = -1;
    
    while (j < pattern.length() - 1) {
        if (k == -1 || pattern[j] == pattern[k]) {
            j++;
            k++;
            next[j] = k;
        } else {
            k = next[k];
        }
    }
}

// KMP algorithm to find all matching positions
vector<int> KMP(const string& mainStr, const string& pattern) {
    vector<int> positions;
    int mainLen = mainStr.length();
    int patternLen = pattern.length();
    
    if (patternLen > mainLen) return positions;  // Pattern is longer than main string, no match possible
    
    // Calculate next array
    vector<int> next(patternLen);
    getNext(pattern, next);
    
    // KMP matching process
    int i = 0;  // Main string pointer
    int j = 0;  // Pattern string pointer
    
    while (i < mainLen) {
        if (j == -1 || mainStr[i] == pattern[j]) {
            i++;
            j++;
        } else {
            j = next[j];
        }
        
        if (j == patternLen) {  // Found a match
            positions.push_back(i - j);  // Record the starting position of the match
            j = next[j-1];  // Continue to find the next match
            i--;  // Go back one position, as i was already incremented
        }
    }
    
    return positions;
}

int main() {
    // Test cases
    string mainStr1 = "ABABCABCACBAB";
    string pattern1 = "AB";
    
    string mainStr2 = "This is a string matching algorithm test";
    string pattern2 = "ing";
    
    string mainStr3 = "aaaaaaaaaaaaaaaaaaab";
    string pattern3 = "aaa";
    
    // Test and output results
    cout << "Test 1: Find \"" << pattern1 << "\" in \"" << mainStr1 << "\"" << endl;
    vector<int> pos1 = KMP(mainStr1, pattern1);
    if (!pos1.empty()) {
        cout << "Found " << pos1.size() << " matches, positions: ";
        for (int p : pos1) {
            cout << p << " ";
        }
        cout << endl;
    } else {
        cout << "No match found" << endl;
    }
    
    cout << "\nTest 2: Find \"" << pattern2 << "\" in \"" << mainStr2 << "\"" << endl;
    vector<int> pos2 = KMP(mainStr2, pattern2);
    if (!pos2.empty()) {
        cout << "Found " << pos2.size() << " matches, positions: ";
        for (int p : pos2) {
            cout << p << " ";
        }
        cout << endl;
    } else {
        cout << "No match found" << endl;
    }
    
    cout << "\nTest 3: Find \"" << pattern3 << "\" in \"" << mainStr3 << "\"" << endl;
    vector<int> pos3 = KMP(mainStr3, pattern3);
    if (!pos3.empty()) {
        cout << "Found " << pos3.size() << " matches, positions: ";
        for (int p : pos3) {
            cout << p << " ";
        }
        cout << endl;
    } else {
        cout << "No match found" << endl;
    }
    
    // Custom test
    string customMain, customPattern;
    cout << "\nEnter main string: ";
    cin >> customMain;
    cout << "Enter pattern string: ";
    cin >> customPattern;
    
    vector<int> customPos = KMP(customMain, customPattern);
    cout << "Finding \"" << customPattern << "\" in \"" << customMain << "\"" << endl;
    if (!customPos.empty()) {
        cout << "Found " << customPos.size() << " matches, positions: ";
        for (int p : customPos) {
            cout << p << " ";
        }
        cout << endl;
    } else {
        cout << "No match found" << endl;
    }
    
    return 0;
}
