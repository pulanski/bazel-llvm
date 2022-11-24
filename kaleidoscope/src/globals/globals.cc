#include "globals.h"

#include <memory>

unique_ptr<LLVMContext> TheContext;

unique_ptr<IRBuilder<>> Builder;

unique_ptr<Module> TheModule;

map<string, Value*> symbolTable;
