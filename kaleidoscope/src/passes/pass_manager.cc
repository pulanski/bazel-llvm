#include "pass_manager.h"

#include <memory>

#include "kaleidoscope/src/globals/globals.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/InstCombine/InstCombine.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Scalar/GVN.h"

using namespace llvm;

unique_ptr<legacy::FunctionPassManager> TheFPM;

void initializeModuleAndPassManager() {
    // Open a new context and module
    TheContext = make_unique<LLVMContext>();
    TheModule =
        make_unique<Module>("JIT Adventures with Bazel and LLVM", *TheContext);
    TheModule->setDataLayout(TheJIT->getDataLayout());

    // Create a new builder for the module
    Builder = make_unique<IRBuilder<>>(*TheContext);

    // Create a new pass manager attached to the module
    TheFPM = make_unique<legacy::FunctionPassManager>(TheModule.get());

    // Do simple "peephole" optimizations and bit-twiddling optimizations.
    // TheFPM->add(createInstructionCombiningPass());
    // Create reassociate pass.
    TheFPM->add(createReassociatePass());
    // Eliminate common subexpressions.
    TheFPM->add(createGVNPass());
    // Simplify the control flow graph (deleting unreachable blocks, etc).
    TheFPM->add(createCFGSimplificationPass());

    TheFPM->doInitialization();
}
