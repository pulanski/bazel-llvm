#pragma once

#include <map>
#include <memory>

#include "kaleidoscope_jit.h"
#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"

using namespace std;
using namespace llvm;
using namespace llvm::orc;

// This is an object that owns LLVM core data structures
extern unique_ptr<LLVMContext> TheContext;

// This is a helper object that makes easy to generate LLVM instructions
extern unique_ptr<IRBuilder<>> Builder;

// This is an LLVM construct that contains functions and global variables
extern unique_ptr<Module> TheModule;

// This map keeps track of which values are defined in the current scope
extern map<string, Value*> symbolTable;

extern unique_ptr<KaleidoscopeJIT> TheJIT;
