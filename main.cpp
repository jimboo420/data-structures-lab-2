#include <iostream>
#include <string>

using namespace std;

// -----------------------------
// Data Model
// -----------------------------
struct User {
    string username;
    string password;
    User* next;

    User(string u, string p) {
        username = u;
        password = p;
        next = nullptr;
    }
};

// -----------------------------
// Core API — implement these
// -----------------------------

User* findUser(User* head, const string& username) {
    User* current = head;
    while (current != nullptr) {
        if (current->username == username) {
            return current;
        }
        current = current->next;
    }
    return nullptr;
}

bool insertUser(User*& head, const string& username, const string& password) {
    if (findUser(head, username) != nullptr) {
        return false;
    }
    User* newUser = new User(username, password);
    if (head == nullptr) {
        head = newUser;
        return true;
    }
    User* current = head;
    while (current->next != nullptr) {
        current = current->next;
    }
    current->next = newUser;
    return true;
}

bool authenticate(User* head, const string& username, const string& password) {
    User* user = findUser(head, username);
    return (user != nullptr && user->password == password);
}

bool removeFront(User*& head) {
    if (head == nullptr) {
        return false;
    }
    User* temp = head;
    head = head->next;
    delete temp;
    return true;
}

bool removeByUsername(User*& head, const string& username) {
    if (head == nullptr) {
        return false;
    }
    if (head->username == username) {
        return removeFront(head);
    }
    User* current = head;
    while (current->next != nullptr && current->next->username != username) {
        current = current->next;
    }
    if (current->next == nullptr) {
        return false;
    }
    User* temp = current->next;
    current->next = temp->next;
    delete temp;
    return true;
}

void clearList(User*& head) {
    while (head != nullptr) {
        removeFront(head);
    }
}

// Returns number of nodes.
size_t size(User* head) {
    size_t count = 0;
    User* current = head;
    while (current != nullptr) {
        count++;
        current = current->next;
    }
    return count;
}

// Prints usernames in order, separated by " -> " then " -> NULL".
void printUsers(User* head) {
    User* current = head;
    while (current != nullptr) {
        cout << current->username;
        if (current->next != nullptr) {
            cout << " -> ";
        }
        current = current->next;
    }
    cout << " -> NULL" << endl;
}

int main() {
    User* head = nullptr;

    // Check size of an empty list
    cout << "Initial size of list: " << size(head) << endl;

    insertUser(head, "alice", "pass123");
    insertUser(head, "bob", "password");
    insertUser(head, "charlie", "cpass");

    // Check size after insertions
    cout << "List after insertions: ";
    printUsers(head);
    cout << "Current size: " << size(head) << endl;

    // Remove a node and check the size again
    removeByUsername(head, "bob");
    cout << "List after removing 'bob': ";
    printUsers(head);
    cout << "Current size: " << size(head) << endl;

    // Clear the list and check the size one last time
    clearList(head);
    cout << "List after clearing: ";
    printUsers(head);
    cout << "Final size: " << size(head) << endl;

    return 0;
}
