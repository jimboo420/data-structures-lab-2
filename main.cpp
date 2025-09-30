#include <iostream>
#include <string>
#include <vector>

using namespace std;

// -----------------------------
// Data Model
// -----------------------------
struct User {
    string username;
    string password;
    vector<string> permissions;      // Permissions for fine-grained control
    User* next;

    User(const string& u, const string& p, const vector<string>& perm = {"view"}) {
        username = u;
        password = p;
        permissions = perm;
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

bool insertUser(User*& head, const string& username, const string& password, const vector<string>& perm = {"view"}) {
    if (findUser(head, username) != nullptr) {
        return false;
    }
    User* newUser = new User(username, password, perm);
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

bool authorize(User* head, const string& username, const string& action) {
    User* user = findUser(head, username);
    if (user == nullptr) {
        return false;
    }
    if (user->permissions.empty()) {
        return false;
    }
    for (const auto& perm : user->permissions) {
        if (perm == action) {
            return true;
        }
    }
    return false;
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

    insertUser(head, "alice", "pass123", {"view"});
    insertUser(head, "bob", "password", {"view", "edit"});
    insertUser(head, "charlie", "cpass", {"view", "edit", "create", "delete"});

    // Check size after insertions
    cout << "List after insertions: ";
    printUsers(head);
    cout << "Current size: " << size(head) << endl;

    // Authorization tests
    cout << "Authorization: alice 'view': " << (authorize(head, "alice", "view") ? "Allowed" : "Denied") << endl;
    cout << "Authorization: alice 'edit': " << (authorize(head, "alice", "edit") ? "Allowed" : "Denied") << endl;
    cout << "Authorization: bob 'edit': " << (authorize(head, "bob", "edit") ? "Allowed" : "Denied") << endl;
    cout << "Authorization: bob 'create': " << (authorize(head, "bob", "create") ? "Allowed" : "Denied") << endl;
    cout << "Authorization: charlie 'delete': " << (authorize(head, "charlie", "delete") ? "Allowed" : "Denied") << endl;

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