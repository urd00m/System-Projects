#ifndef LLVM_TRANSFORMS_BASICNEW_FUNCINJECTUNARY_H
#define LLVM_TRANSFORMS_BASICNEW_FUNCINJECTUNARY_H

#include "llvm/IR/PassManager.h"
#include "llvm/Pass.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/Passes/PassPlugin.h"
#include "llvm/Passes/PassBuilder.h"

namespace llvm {
  
  class MyBasicPass5 : public PassInfoMixin<MyBasicPass5> {
  public:
    PreservedAnalyses run(Module& M, ModuleAnalysisManager &MAM);
    bool runOnModule(Module& M);
  };
  
} // namespace llvm


#endif

