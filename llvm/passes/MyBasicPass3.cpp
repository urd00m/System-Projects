#include "llvm/Transforms/Utils/MyBasicPass3.h"

using namespace llvm;

PreservedAnalyses MyBasicPass3::run(Function &F,
                                      FunctionAnalysisManager &AM) {
  errs() << F.getName() << "\n";

  int block_counter = 0;
  for (Function::iterator bb = F.begin(), e = F.end(); bb != e; ++bb) {
    errs() << "Is this an ertry block: " << bb->isEntryBlock() << "\n";
    block_counter++;
  }
  errs() << "number of blocks " << block_counter << "\n";
        
  return PreservedAnalyses::all();
}


