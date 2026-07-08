#include <iostream>

// Define a Node structure for the doubly linked list
struct Node {
    int data;
    Node* prev; // Pointer to the previous node
    Node* next; // Pointer to the next node

    // Constructor to initialize a node
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};

// Doubly linked list class
class DoublyLinkedList {
private:
    Node* head; // Pointer to the first node of the list

public:
    // Constructor to initialize the list
    DoublyLinkedList() : head(nullptr) {}

    // Function to add a node to the front of the list
    void pushFront(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode; // List is empty, so new node becomes the head
        } else {
            newNode->next = head; // Make new node point to current head
            head->prev = newNode; // Update current head's prev to point to new node
            head = newNode;       // Move head to point to new node
        }
    }

    // Function to add a node to the back of the list
    void pushBack(int value) {
        Node* newNode = new Node(value);

        if (head == nullptr) {
            head = newNode; // List is empty, so new node becomes the head
        } else {
            Node* temp = head;

            // Traverse to the end of the list
            while (temp->next != nullptr) {
                temp = temp->next;
            }

            // Link the last node with the new node
            temp->next = newNode;
            newNode->prev = temp;
        }
    }

    // Function to print the list from the beginning
    void printForward() const {
        Node* temp = head;
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->next;
        }
        std::cout << std::endl;
    }

    // Function to print the list from the end
    void printBackward() const {
        if (head == nullptr) return;

        Node* temp = head;

        // Traverse to the last node
        while (temp->next != nullptr) {
            temp = temp->next;
        }

        // Traverse backward from the last node
        while (temp != nullptr) {
            std::cout << temp->data << " ";
            temp = temp->prev;
        }
        std::cout << std::endl;
    }

    // Function to delete a node from the list
    void deleteNode(int value) {
        if (head == nullptr) return; // List is empty

        Node* temp = head;

        // Search for the node with the given value
        while (temp != nullptr && temp->data != value) {
            temp = temp->next;
        }

        // If node is not found, do nothing
        if (temp == nullptr) return;

        // Update links to remove the node
        if (temp->prev != nullptr) {
            temp->prev->next = temp->next;
        } else {
            // If temp is head, move the head to next node
            head = temp->next;
        }

        if (temp->next != nullptr) {
            temp->next->prev = temp->prev;
        }

        delete temp; // Free memory of the node
    }

    // Destructor to free memory when the list is destroyed
    ~DoublyLinkedList() {
        Node* temp = head;
        while (temp != nullptr) {
            Node* nextNode = temp->next;
            delete temp;
            temp = nextNode;
        }
    }
};

int main() {
    DoublyLinkedList dll;

    // Adding elements to the front and back
    dll.pushFront(10);
    dll.pushFront(20);
    dll.pushBack(30);
    dll.pushBack(40);

    // Print the list forward and backward
    std::cout << "Forward: ";
    dll.printForward();

    std::cout << "Backward: ";
    dll.printBackward();

    // Delete a node
    dll.deleteNode(20);

    // Print after deletion
    std::cout << "After deletion: ";
    dll.printForward();

    return 0;
}
