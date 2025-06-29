#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

// Node definition for the linked list
struct Node {
    int data;
    Node* next;
    Node(int val) : data(val), next(nullptr) {}
};

// --- Linked List Helper Functions ---

// Creates a linked list from a vector (with a dummy head node)
Node* createList(const std::vector<int>& vals) {
    Node* head = new Node(0); // Dummy head node
    Node* current = head;
    for (int val : vals) {
        current->next = new Node(val);
        current = current->next;
    }
    return head;
}

// Prints the linked list (skips dummy head)
void printList(Node* head) {
    Node* current = head->next;
    while (current != nullptr) {
        std::cout << current->data << " -> ";
        current = current->next;
    }
    std::cout << "nullptr" << std::endl;
}

// Deletes the entire linked list
void deleteList(Node* head) {
    Node* current = head;
    while (current != nullptr) {
        Node* temp = current;
        current = current->next;
        delete temp;
    }
}

// --- Simple Selection Sort (using pointer manipulation) ---
// Sorts a linked list with a dummy head node in place.
void selectSort(Node* head) {
    if (head == nullptr || head->next == nullptr) {
        return; // Nothing to sort
    }

    Node* sorted_tail = head; // The last node of the sorted part
    while (sorted_tail->next != nullptr) {
        // Find the minimum node in the unsorted part
        Node* min_prev = sorted_tail;
        Node* min_node = sorted_tail->next;
        Node* current_prev = sorted_tail->next;
        Node* current = current_prev->next;

        while (current != nullptr) {
            if (current->data < min_node->data) {
                min_prev = current_prev;
                min_node = current;
            }
            current_prev = current;
            current = current->next;
        }

        // Relink the minimum node to the end of the sorted list
        if (min_node != sorted_tail->next) {
            min_prev->next = min_node->next; // Unlink min_node
            min_node->next = sorted_tail->next; // Insert after sorted_tail
            sorted_tail->next = min_node;
        }
        
        sorted_tail = sorted_tail->next; // Advance sorted_tail
    }
}

// --- Main Function ---
int main() {
    std::cout << "--- Simple Selection Sort for Linked List (Pointer Manipulation) ---" << std::endl;

    // 1. Create a list from data
    std::vector<int> data = {12, 15, 20, 9, 6, 31};
    Node* list_head = createList(data);

    // 2. Print the original list
    std::cout << "Original list: ";
    printList(list_head);

    // 3. Sort the list
    selectSort(list_head);

    // 4. Print the sorted list
    std::cout << "Sorted list:   ";
    printList(list_head);

    // 5. Clean up memory
    deleteList(list_head);

    return 0;
}
