#include <iostream>
#include <string>
using namespace std;

int countWords(const string& text) {
    int count = 0;  // Initialize counter
    int state = 1;  // Initialize character reading state, 1 means outside a word
    
    for (char c : text) {
        if (isspace(c)) {  // If the character is a space
            state = 1;     // Set state to outside a word
        } else if (state == 1) {  // If not a space and state is outside a word
            state = 0;     // Set state to inside a word
            count++;       // Increment counter
        }
    }
    
    return count;
}

int main() {
    string text;
    
    cout << "Please enter text (can include English, Chinese, etc. Press Enter then Ctrl+Z to finish input):" << endl;
    
    // Read entire lines of text, including spaces
    string line;
    while (getline(cin, line)) {
        if (!text.empty()) {
            text += "\n" + line;  // Add newline and new line
        } else {
            text = line;
        }
    }
    
    int wordCount = countWords(text);
    cout << "Number of words in the text: " << wordCount << endl;
    
    // Time complexity analysis: O(n), where n is the number of characters in the text
    // Space complexity analysis: O(n), used to store the input text
    
    return 0;
}

