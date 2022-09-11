#include "llvm/Transforms/Utils/MyBasicPass.h"

using namespace llvm;

PreservedAnalyses MyBasicPass::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";
  return PreservedAnalyses::all();
}


