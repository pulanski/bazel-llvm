#pragma once

#include <map>
#include <string>

#include "kaleidoscope/src/ast/prototype_ast.h"
#include "llvm/IR/Function.h"

using namespace std;
using namespace llvm;

extern map<string, unique_ptr<PrototypeAST>> functionProtos;

Function* getFunction(string name);
