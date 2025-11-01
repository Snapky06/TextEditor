#include <iostream>
#include <string>
#include <limits>
#include "LinkedList.h"
#include "Operation.h"

using namespace std;

static void printList(const LinkedList<string>& list) {
    if (list.size() == 0) {
        cout << "List is empty." << endl;
        return;
    }
    for (size_t i = 0; i < list.size(); ++i)
        cout << i << ": " << list.at(i) << endl;
}

static void resetInput() {
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    LinkedList<string> list;
    Stack<Operation> undoStack;
    Stack<Operation> redoStack;

    cout << "Word List Editor" << endl;

    int choice;
    while (true) {
        cout << endl;
        cout << "1) Add word" << endl;
        cout << "2) Remove word" << endl;
        cout << "3) Replace word" << endl;
        cout << "4) Show list" << endl;
        cout << "5) Undo" << endl;
        cout << "6) Redo" << endl;
        cout << "0) Exit" << endl;
        cout << "Enter option: ";

        if (!(cin >> choice)) { resetInput(); continue; }
        if (choice == 0) break;

        size_t index;
        string word;

        switch (choice) {
        case 1: {
            cout << "Index to insert at: ";
            if (!(cin >> index)) { resetInput(); break; }
            cout << "Word: ";
            if (!(cin >> word)) { resetInput(); break; }

            Operation op{ActionType::Insert, index, "", word};
            if (applyAction(list, op, undoStack)) {
                redoStack.clear();
                cout << "Added." << endl;
            } else {
                cout << "Could not add at that index." << endl;
            }
            break;
        }

        case 2: {
            cout << "Index to remove: ";
            if (!(cin >> index)) { resetInput(); break; }
            try {
                string oldWord = list.at(index);
                Operation op{ActionType::Delete, index, oldWord, ""};
                if (applyAction(list, op, undoStack)) {
                    redoStack.clear();
                    cout << "Removed." << endl;
                } else {
                    cout << "Could not remove." << endl;
                }
            } catch (...) {
                cout << "Invalid index." << endl;
            }
            break;
        }

        case 3: {
            cout << "Index to replace: ";
            if (!(cin >> index)) { resetInput(); break; }
            cout << "New word: ";
            if (!(cin >> word)) { resetInput(); break; }
            try {
                string oldWord = list.at(index);
                Operation op{ActionType::Replace, index, oldWord, word};
                if (applyAction(list, op, undoStack)) {
                    redoStack.clear();
                    cout << "Replaced." << endl;
                } else {
                    cout << "Could not replace." << endl;
                }
            } catch (...) {
                cout << "Invalid index." << endl;
            }
            break;
        }

        case 4:
            printList(list);
            break;

        case 5: {
            if (!undoStack.empty()) {
                Operation inv = undoStack.top();
                undoStack.pop();
                if (applyAction(list, inv, redoStack))
                    cout << "Undone." << endl;
            } else {
                cout << "Nothing to undo." << endl;
            }
            break;
        }

        case 6: {
            if (!redoStack.empty()) {
                Operation inv = redoStack.top();
                redoStack.pop();
                if (applyAction(list, inv, undoStack))
                    cout << "Redone." << endl;
            } else {
                cout << "Nothing to redo." << endl;
            }
            break;
        }

        default:
            cout << "Invalid option." << endl;
        }
    }

    cout << endl << "Cleaning up..." << endl;
    list.clear();
    undoStack.clear();
    redoStack.clear();
    cout << "Done." << endl;
    return 0;
}
