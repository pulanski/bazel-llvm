#include "jit.h"

void initializeJIT() {
    // Initialize LLVM JIT components
    LLVMInitializeNativeTarget();
    LLVMInitializeNativeAsmPrinter();
    LLVMInitializeNativeAsmParser();

    // Initialize the JIT
    TheJIT = ExitOnErr(KaleidoscopeJIT::create());
}

unique_ptr<KaleidoscopeJIT> TheJIT;

ExitOnError ExitOnErr;
