#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

// Train Rearrangement Problem
class TrainRearrangement {
private:
    vector<int> initialOrder;    // Initial order of carriages
    int n;                       // Number of carriages
    int k;                       // Number of buffer tracks
    vector<queue<int>> bufferTracks; // K buffer tracks

public:
    TrainRearrangement(vector<int>& order, int bufferNum) {
        initialOrder = order;
        n = order.size();
        k = bufferNum;
        bufferTracks.resize(k);
    }

    // Rearrange carriages
    bool rearrange() {
        // Target is to arrange carriages in order from 1 to n
        int nextNeeded = 1;
        
        // Simulate the input track operation
        for (int i = 0; i < n; i++) {
            int current = initialOrder[i];
            
            // If the current carriage is the one we need, send it directly to the output track
            if (current == nextNeeded) {
                cout << "Carriage " << current << " moves directly from input to output track" << endl;
                nextNeeded++;
                
                // Check if there are any carriages in buffer tracks that can be moved out
                bool foundInBuffer = true;
                while (foundInBuffer) {
                    foundInBuffer = false;
                    for (int j = 0; j < k; j++) {
                        if (!bufferTracks[j].empty() && bufferTracks[j].front() == nextNeeded) {
                            cout << "Carriage " << nextNeeded << " moves from buffer track " << j+1 << " to output track" << endl;
                            bufferTracks[j].pop();
                            nextNeeded++;
                            foundInBuffer = true;
                            break;
                        }
                    }
                }
            } else {
                // Need to place the carriage in a buffer track
                bool placed = false;
                for (int j = 0; j < k; j++) {
                    // Try to find an empty buffer track or one where the top carriage number is greater than the current one
                    if (bufferTracks[j].empty() || bufferTracks[j].back() > current) {
                        bufferTracks[j].push(current);
                        cout << "Carriage " << current << " placed in buffer track " << j+1 << endl;
                        placed = true;
                        break;
                    }
                }
                
                // If it cannot be placed in any buffer track, rearrangement fails
                if (!placed) {
                    cout << "Cannot rearrange carriages: insufficient buffer tracks" << endl;
                    return false;
                }
            }
        }
        
        // Check if all carriages have been arranged in order
        return nextNeeded > n;
    }
};

int main() {
    int n, k;
    cout << "Enter the number of carriages: ";
    cin >> n;
    
    cout << "Enter the number of buffer tracks: ";
    cin >> k;
    
    vector<int> initialOrder(n);
    cout << "Enter the initial order of carriages (a permutation from 1 to n): ";
    for (int i = 0; i < n; i++) {
        cin >> initialOrder[i];
    }
    
    TrainRearrangement tr(initialOrder, k);
    bool success = tr.rearrange();
    
    if (success) {
        cout << "Carriage rearrangement successful!" << endl;
    } else {
        cout << "Carriage rearrangement failed, more buffer tracks needed!" << endl;
    }
    
    return 0;
}

// Time Complexity Analysis:
// 1. Iterating through all carriages takes O(n) time
// 2. For each carriage, in the worst case, we need to check all k buffer tracks, which takes O(k) time
// 3. After placing each carriage, we might need to check all buffer tracks for carriages that can be moved out, which in the worst case takes O(k*n) time
// Therefore, the overall time complexity is O(n*k)

