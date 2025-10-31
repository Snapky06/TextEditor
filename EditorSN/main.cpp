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
                "0) Salir\n> " << std::endl;

        if (!(cin >> opt)) { limpiarEntrada(); continue; }
        if (opt == 0) break;

        size_t pos;
        string palabra;

        switch (opt) {
        case 1: {
            cout << "Posicion: " << std::endl;
            if (!(cin >> pos)) { limpiarEntrada(); break; }
            cout << "Palabra: " << std::endl ;
            if (!(cin >> palabra)) { limpiarEntrada(); break; }
            Operation op{opType::Insert, pos, "", palabra};
            if (applyOperation(lista, op, undoStack)) {
                redoStack.clear();
                cout << "Insertado.\n" << std::endl ;
            } else cout << "No se pudo insertar.\n" << std::endl;
            break;
        }
        case 2: {
            cout << "Posicion: " << std::endl ;
            if (!(cin >> pos)) { limpiarEntrada(); break; }
            try {
                string old = lista.at(pos);
                Operation op{opType::Delete, pos, old, ""};
                if (applyOperation(lista, op, undoStack)) {
                    redoStack.clear();
                    cout << "Eliminado.\n" << std::endl;
                } else cout << "No se pudo eliminar.\n" << std::endl;
            } catch (...) { cout << "Posicion invalida.\n" << std::endl; }
            break;
        }
        case 3: {
            cout << "Posicion: " << std::endl;
            if (!(cin >> pos)) { limpiarEntrada(); break; }
            cout << "Nueva palabra: " << std::endl;
            if (!(cin >> palabra)) { limpiarEntrada(); break; }
            try {
                string old = lista.at(pos);
                Operation op{opType::Replace, pos, old, palabra};
                if (applyOperation(lista, op, undoStack)) {
                    redoStack.clear();
                    cout << "Reemplazado.\n" << std::endl;
                } else cout << "No se pudo reemplazar.\n" << std::endl;
            } catch (...) { cout << "Posicion invalida.\n" << std::endl; }
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
                    cout << "Undo ejecutado.\n" << std::endl;
                }
            } else {
                cout << "Nada que deshacer.\n" << std::endl;
            }
            break;
        }
        case 6: {
            if (!redoStack.empty()) {
                Operation inv = redoStack.top();
                redoStack.pop();
                if (applyOperation(lista, inv, undoStack)) {
                    cout << "Redo ejecutado.\n" << std::endl;
                }
            } else {
                cout << "Nada que rehacer.\n"<< std::endl;
            }
            break;
        }

        default:
            cout << "Opcion invalida.\n"<< std::endl;
        }
    }

    cout << "Saliendo\n"<< std::endl;

    lista.clear();
    undoStack.clear();
    redoStack.clear();
    return 0;
}
