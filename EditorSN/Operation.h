#ifndef OPERATION_H
#define OPERATION_H
#include <string>

enum class opType { Insert, Delete , Replace};

struct Operation
{
    opType type;
    std::size_t pos;
    std::string oldValue;
    std::string newValue;
};

Operation inverseOf(const Operation& op){

    Operation inv = op;
    switch (op.type){

    case opType::Insert:

        inv.type = opType::Delete;
        inv.oldValue = op.newValue;
        inv.newValue.clear();

    case opType::Delete:

        inv.type = opType::Insert;
        inv.newValue = op.oldValue;

    case opType::Replace:

        std::swap(inv.oldValue,inv.newValue);
        break;
    }
    return inv;
}
#endif // OPERATION_H
