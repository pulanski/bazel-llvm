#pragma once

#include "llvm/IR/LegacyPassManager.h"

using namespace std;
using namespace llvm;

// This is an object that owns LLVM optimizations
// that we wish to run
extern unique_ptr<legacy::FunctionPassManager> TheFPM;

/// Handles the initialization of an LLVM Module
/// used as a container for LLVM IR objects as well
/// as an LLVM Pass Manager
void initializeModuleAndPassManager();
