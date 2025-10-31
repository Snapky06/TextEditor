#include <iostream>
#include <string>
#include <limits>
#include "LinkedList.h"
#include "Stack.h"
#include "Operation.h"

using std::cout;
using std::cin;
using std::string;

void mostrarLista(const LinkedList<string>& lista) {
    if (lista.size() == 0) {
        cout << "(Lista vacia)\n";
        return;
    }
    for (size_t i = 0; i < lista.size(); ++i)
        cout << i << ": " << lista.at(i) << "\n";
}

void limpiarEntrada() {
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    LinkedList<string> lista;
    Stack<Operation> undoStack, redoStack;

    cout << "=== Mini Editor ===\n";

    int opt;
    while (true) {
        cout << "\n1) Insertar palabra\n"
                "2) Eliminar palabra\n"
                "3) Reemplazar palabra\n"
                "4) Mostrar lista\n"
                "5) Deshacer (Undo)\n"
                "6) Rehacer (Redo)\n"
                "0) Salir\n> ";

        if (!(cin >> opt)) { limpiarEntrada(); continue; }
        if (opt == 0) break;

        size_t pos;
        string palabra;

        switch (opt) {
        case 1: {
            cout << "Posicion: ";
            if (!(cin >> pos)) { limpiarEntrada(); break; }
            cout << "Palabra: ";
            if (!(cin >> palabra)) { limpiarEntrada(); break; }
            Operation op{opType::Insert, pos, "", palabra};
            if (applyOperation(lista, op, undoStack)) {
                redoStack.clear();
                cout << "Insertado.\n";
            } else cout << "No se pudo insertar.\n";
            break;
        }
        case 2: {
            cout << "Posicion: ";
            if (!(cin >> pos)) { limpiarEntrada(); break; }
            try {
                string old = lista.at(pos);
                Operation op{opType::Delete, pos, old, ""};
                if (applyOperation(lista, op, undoStack)) {
                    redoStack.clear();
                    cout << "Eliminado.\n";
                } else cout << "No se pudo eliminar.\n";
            } catch (...) { cout << "Posicion invalida.\n"; }
            break;
        }
        case 3: {
            cout << "Posicion: ";
            if (!(cin >> pos)) { limpiarEntrada(); break; }
            cout << "Nueva palabra: ";
            if (!(cin >> palabra)) { limpiarEntrada(); break; }
            try {
                string old = lista.at(pos);
                Operation op{opType::Replace, pos, old, palabra};
                if (applyOperation(lista, op, undoStack)) {
                    redoStack.clear();
                    cout << "Reemplazado.\n";
                } else cout << "No se pudo reemplazar.\n";
            } catch (...) { cout << "Posicion invalida.\n"; }
            break;
        }
        case 4:
            mostrarLista(lista);
            break;
        case 5: {
            if (!undoStack.empty()) {
                Operation inv = undoStack.top();
                undoStack.pop();
                if (applyOperation(lista, inv, redoStack)) {
                    cout << "Undo ejecutado.\n";
                }
            } else {
                cout << "Nada que deshacer.\n";
            }
            break;
        }
        case 6: {
            if (!redoStack.empty()) {
                Operation inv = redoStack.top();
                redoStack.pop();
                if (applyOperation(lista, inv, undoStack)) {
                    cout << "Redo ejecutado.\n";
                }
            } else {
                cout << "Nada que rehacer.\n";
            }
            break;
        }

        default:
            cout << "Opcion invalida.\n";
        }
    }

    cout << "Saliendo...\n";
    return 0;
}
