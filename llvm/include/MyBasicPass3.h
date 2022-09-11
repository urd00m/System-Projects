#ifndef LLVM_TRANSFORMS_BASICNEW_BLOCKCOUNTER_H
#define LLVM_TRANSFORMS_BASICNEW_BLOCKCOUNTER_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/SymbolTableListTraits.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Function.h"

namespace llvm {

  class MyBasicPass3 : public PassInfoMixin<MyBasicPass3> {
  public:
    PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
  };
} // namespace llvm

#endif 
