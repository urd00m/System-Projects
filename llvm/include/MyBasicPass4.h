#ifndef LLVM_TRANSFORMS_BASICNEW_FUNCINJECT_H
#define LLVM_TRANSFORMS_BASICNEW_FUNCINJECT_H

#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

namespace llvm {
  
  class MyBasicPass4 : public PassInfoMixin<MyBasicPass4> {
  public:
    PreservedAnalyses run(Module& M, ModuleAnalysisManager &MAM);
    bool runOnModule(Module& M);
  };
  
} // namespace llvm


#endif

