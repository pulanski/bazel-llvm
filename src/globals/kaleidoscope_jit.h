#pragma once

#include <memory>

#include "llvm/ADT/StringRef.h"
#include "llvm/ExecutionEngine/JITSymbol.h"
#include "llvm/ExecutionEngine/Orc/CompileUtils.h"
#include "llvm/ExecutionEngine/Orc/Core.h"
#include "llvm/ExecutionEngine/Orc/ExecutionUtils.h"
#include "llvm/ExecutionEngine/Orc/ExecutorProcessControl.h"
#include "llvm/ExecutionEngine/Orc/IRCompileLayer.h"
#include "llvm/ExecutionEngine/Orc/JITTargetMachineBuilder.h"
#include "llvm/ExecutionEngine/Orc/RTDyldObjectLinkingLayer.h"
#include "llvm/ExecutionEngine/SectionMemoryManager.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/IR/LLVMContext.h"

using namespace std;
using namespace llvm;
using namespace llvm::orc;

namespace llvm {
namespace orc {

class KaleidoscopeJIT {
   private:
    unique_ptr<ExecutionSession> es_;

    DataLayout dl_;
    MangleAndInterner mangle_;

    RTDyldObjectLinkingLayer object_layer_;
    IRCompileLayer compile_layer_;

    JITDylib& main_jd_;

   public:
    KaleidoscopeJIT(unique_ptr<ExecutionSession> es,
                    JITTargetMachineBuilder jtmb, DataLayout dl)
        : es_(std::move(es)),
          dl_(std::move(dl)),
          mangle_(*this->es_, this->dl_),
          object_layer_(*this->es_,
                        []() { return make_unique<SectionMemoryManager>(); }),
          compile_layer_(*this->es_, object_layer_,
                         make_unique<ConcurrentIRCompiler>(std::move(jtmb))),
          main_jd_(this->es_->createBareJITDylib("<main>")) {
        main_jd_.addGenerator(
            cantFail(DynamicLibrarySearchGenerator::GetForCurrentProcess(
                dl.getGlobalPrefix())));
        if (jtmb.getTargetTriple().isOSBinFormatCOFF()) {
            object_layer_.setOverrideObjectFlagsWithResponsibilityFlags(true);
            object_layer_.setAutoClaimResponsibilityForObjectSymbols(true);
        }
    }

    ~KaleidoscopeJIT() {
        if (auto Err = es_->endSession()) {
            es_->reportError(std::move(Err));
        }
    }

    static Expected<std::unique_ptr<KaleidoscopeJIT>> create() {
        auto EPC = SelfExecutorProcessControl::Create();
        if (!EPC) {
            return EPC.takeError();
        }

        auto es_ = std::make_unique<ExecutionSession>(std::move(*EPC));

        JITTargetMachineBuilder JTMB(
            es_->getExecutorProcessControl().getTargetTriple());

        auto DL = JTMB.getDefaultDataLayoutForTarget();
        if (!DL) {
            return DL.takeError();
        }

        return std::make_unique<KaleidoscopeJIT>(
            std::move(es_), std::move(JTMB), std::move(*DL));
    }

    const DataLayout& getDataLayout() const { return dl_; }

    JITDylib& getMainJITDylib() { return main_jd_; }

    Error addModule(ThreadSafeModule tsm, ResourceTrackerSP rt = nullptr) {
        if (!rt) {
            rt = main_jd_.getDefaultResourceTracker();
        }
        return compile_layer_.add(rt, std::move(tsm));
    }

    Expected<JITEvaluatedSymbol> lookup(StringRef name) {
        return es_->lookup({&main_jd_}, mangle_(name.str()));
    }
};
}  // namespace orc
}  // namespace llvm
