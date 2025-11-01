#ifndef OPERATION_H
#define OPERATION_H

#include <string>
#include "LinkedList.h"
#include "Stack.h"

enum class ActionType { Insert, Delete, Replace };

struct Operation {
    ActionType type;
    size_t index;
    std::string oldValue;
    std::string newValue;
};

inline Operation inverseOf(const Operation& op) {
    Operation inv = op;
    switch (op.type) {
    case ActionType::Insert:
        inv.type = ActionType::Delete;
        inv.oldValue = op.newValue;
        inv.newValue.clear();
        break;
    case ActionType::Delete:
        inv.type = ActionType::Insert;
        inv.newValue = op.oldValue;
        inv.oldValue.clear();
        break;
    case ActionType::Replace:
        std::swap(inv.oldValue, inv.newValue);
        break;
    }
    return inv;
}

inline bool applyAction(LinkedList<std::string>& list,
                        const Operation& op,
                        Stack<Operation>& inverseStack) {
    switch (op.type) {
    case ActionType::Insert: {
        if (!list.insert(op.index, op.newValue)) return false;
        break;
    }
    case ActionType::Delete: {
        std::string removed;
        if (!list.remove(op.index, &removed)) return false;
        break;
    }
    case ActionType::Replace: {
        try { list.at(op.index) = op.newValue; }
        catch (...) { return false; }
        break;
    }
    }
    inverseStack.push(inverseOf(op));
    return true;
}

#endif // OPERATION_H
