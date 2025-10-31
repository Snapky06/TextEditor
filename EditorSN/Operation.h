#ifndef OPERATION_H
#define OPERATION_H
#include "LinkedList.h"
#include "Stack.h"
#include <string>

enum class opType { Insert, Delete , Replace};

struct Operation
{
    opType type;
    std::size_t pos;
    std::string oldValue;
    std::string newValue;
};

Operation inverseOf(const Operation& op) {
    Operation inv = op;
    switch (op.type) {
    case opType::Insert:
        inv.type = opType::Delete;
        inv.oldValue = op.newValue;
        inv.newValue.clear();
        break;
    case opType::Delete:
        inv.type = opType::Insert;
        inv.newValue = op.oldValue;
        inv.oldValue.clear();
        break;
    case opType::Replace:
        std::swap(inv.oldValue, inv.newValue);
        break;
    }
    return inv;
}


bool applyOperation(LinkedList<std::string>& doc,const Operation& op,Stack<Operation>& pushHere) {
    switch (op.type) {
    case opType::Insert: {
        if (!doc.insert(op.pos, op.newValue)) return false;
        break;
    }
    case opType::Delete: {
        std::string removed;
        if (!doc.erase(op.pos, &removed)) return false;
        break;
    }
    case opType::Replace: {
        try { doc.at(op.pos) = op.newValue; }
        catch (...) { return false; }
        break;
    }
    }

    pushHere.push(inverseOf(op));
    return true;
}


#endif // OPERATION_H
