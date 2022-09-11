#ifndef LLVM_TRANSFORMS_BASICNEW_OPCODECOUNTER_H
#define LLVM_TRANSFORMS_BASICNEW_OPCODECOUNTER_H

#include "llvm/IR/PassManager.h"
#include "llvm/IR/SymbolTableListTraits.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IR/Function.h"

namespace llvm {

class MyBasicPass2 : public PassInfoMixin<MyBasicPass2> {
public:
  PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
};

} // namespace llvm

#endif // LLVM_TRANSFORMS_BASICNEW_OPCODECOUNTER_H
