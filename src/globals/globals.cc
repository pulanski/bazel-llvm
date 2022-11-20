#include "globals.h"

#include <memory>

// This is an object that owns LLVM core data structures

unique_ptr<LLVMContext> TheContext;

// This is a helper object that makes easy to generate LLVM instructions
unique_ptr<IRBuilder<>> Builder;

// This is an LLVM construct that contains functions and global variables
unique_ptr<Module> TheModule;

// This map keeps track of which values are defined in the current scope
map<string, Value*> symbolTable;
