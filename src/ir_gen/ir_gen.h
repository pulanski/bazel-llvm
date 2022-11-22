#pragma once

#include <map>
#include <string>

#include "llvm/IR/Function.h"
#include "src/ast/prototype_ast.h"

using namespace std;
using namespace llvm;

extern map<string, unique_ptr<PrototypeAST>> functionProtos;

Function* getFunction(string name);
