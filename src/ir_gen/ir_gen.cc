#include "ir_gen.h"

#include "src/globals/globals.h"

map<string, unique_ptr<PrototypeAST>> functionProtos;

Function* getFunction(string name) {
    // First, see if the function has already been added to the current module.
    if (auto* fn = TheModule->getFunction(name)) {
        return fn;
    }

    // If not, check whether we can codegen the declaration from some existing
    // prototype.
    auto fi = functionProtos.find(name);

    if (fi != functionProtos.end()) {
        return fi->second->codegen();
    }

    // If no existing prototype exists, return null.
    return nullptr;
}
